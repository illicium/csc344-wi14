#include "SimpleFilterAudioProcessor.h"

#include <ostream>
using namespace std;

SimpleFilterAudioProcessor::SimpleFilterAudioProcessor()
    :
    Parameterized({
        {"gain_in", make_shared<Parameter<double>>("Input Gain (dB)", 0.0, -24.0, 24.0)},
        {"freq", make_shared<WarpedParameter<double>>("Filter Frequency", 500, 100.0, 20000.0, 700.0)},
        {"ripple", make_shared<WarpedParameter<double>>("Filter Ripple", 1.0, 0.01, 6.0, 1.0)},
        {"dist", make_shared<WarpedParameter<double>>("Distortion", 1.0, 1.0, 1000.0, 10.0)}
    }),
    filter(),
    filterDelayBuffer(2, 5)
{
    for (auto &param : *parameters) {
        parameterIds.push_back(param.first);
        param.second->addListener(this);
    }
    
    filter.setRipple(1.0);
}

/**
 * Update filter internal state (ripple) with current parameters
 */
void SimpleFilterAudioProcessor::updateFilterRipple()
{
    double ripple = Parameterized::getParameter<double>("ripple")->getValue();
    filter.setRipple(ripple);
}

/**
 * Update filter internal state (theta) with current parameters
 */
void SimpleFilterAudioProcessor::updateFilterTheta()
{
    filter.setTheta(calculateFilterTheta(getSampleRate()));
}

/**
 * Given the sample rate in Hz, return the filter angle theta for the current filter frequency
 */
double SimpleFilterAudioProcessor::calculateFilterTheta(double sampleRate)
{
    double freq = Parameterized::getParameter<double>("freq")->getValue();
    return (freq / (sampleRate / 2)) * double_Pi;
}


void SimpleFilterAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    filterDelayBuffer.clear();
    updateFilterTheta();
}

void SimpleFilterAudioProcessor::releaseResources()
{
    filterDelayBuffer.clear();
}


void SimpleFilterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    
    float gain_in = Decibels::decibelsToGain(Parameterized::getParameter<double>("gain_in")->getValue());
    double dist = Parameterized::getParameter<double>("dist")->getValue();
    
    // apply input gain/dist
    for (int channel = 0; channel < getNumInputChannels(); channel++) {
        float* channelData = buffer.getSampleData(channel);
        
        for (int i = 0; i < numSamples; i++) {
            // apply gain
            channelData[i] *= gain_in;

            // apply dist
            if (dist >= 1.0 + numeric_limits<double>::epsilon()) {
                channelData[i] = 2.0 / (1.0 + pow(dist, -channelData[i])) - 1.0;
            }
        }
    }

    shared_ptr<vector<double>> coefficientsB = filter.getCoefficientsB();
    double filterDCGain = filter.getDCGain();
    
    for (int channel = 0; channel < getNumInputChannels(); channel++) {
        float* channelData = buffer.getSampleData(channel);

        float* filterDelayData = filterDelayBuffer.getSampleData(
                jmin(channel, filterDelayBuffer.getNumChannels() - 1));
     
        for (int i = 0; i < numSamples; i++) {
            for (int j = filterDelayBuffer.getNumSamples() - 1; j > 0; j--) {
                filterDelayData[j] = filterDelayData[j - 1];
            }

            float out = channelData[i] / filterDCGain;
            
            for (vector<double>::size_type i = 1; i < coefficientsB->size(); i++) {
                // start at 1 for filterDelayData coefficients because index 0 is the one
                // we are currently calculating (and after shift it's the same
                // as the one at index 1), so it's impossible to have a value for it

                out -= filterDelayData[i] * coefficientsB->at(i);
            }
            
            filterDelayData[0] = out;
        
            channelData[i] = filterDelayData[0];
        }
    }

    // clear extra channels
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); i++) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}

void SimpleFilterAudioProcessor::parameterValueChanged(ParameterBase* param)
{
    if (param == Parameterized::getParameter("freq").get()) {
        updateFilterTheta();
    } else if (param == Parameterized::getParameter("ripple").get()) {
        updateFilterRipple();
    }
}

int SimpleFilterAudioProcessor::getNumParameters()
{
    return parameterIds.size();
}

float SimpleFilterAudioProcessor::getParameter(int index)
{
    if (index < 0 || index >= parameterIds.size()) {
        return 0.0f;
    }
    
    return (*parameters)[parameterIds[index]]->getFloatValueLinear();
}

void SimpleFilterAudioProcessor::setParameter(int index, float newValue)
{
    if (index < 0 || index >= parameterIds.size()) {
        return;
    }

    (*parameters)[parameterIds[index]]->setFloatValueLinear(newValue);
}

const String SimpleFilterAudioProcessor::getParameterName(int index)
{
    if (index < 0 || index >= parameterIds.size()) {
        return String::empty;
    }
    
    return String(parameterIds[index] +
                  + " (" + (*parameters)[parameterIds[index]]->getName() + ')');
}

const String SimpleFilterAudioProcessor::getParameterText(int index)
{
    if (index < 0 && index > parameterIds.size()) {
        return String::empty;
    }
    
    return (*parameters)[parameterIds[index]]->getValueText();
}


void SimpleFilterAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    XmlElement xml(JucePlugin_Name "_settings");
    
    for (const String& paramId : parameterIds) {
        xml.setAttribute(paramId, (*parameters)[paramId]->getFloatValueLinear());
    }
    
    copyXmlToBinary(xml, destData);
}

void SimpleFilterAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName(JucePlugin_Name "_settings"))
        {
            for (const String& paramId : parameterIds) {
                float prevValue = (*parameters)[paramId]->getFloatValueLinear();
                float newValue = (float) xmlState->getDoubleAttribute(paramId, prevValue);
                (*parameters)[paramId]->setFloatValueLinear(newValue);
            }
        }
    }
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleFilterAudioProcessor();
}
