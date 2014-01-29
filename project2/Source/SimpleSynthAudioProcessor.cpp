#include "SimpleSynthAudioProcessor.h"
#include "SimpleSynthAudioProcessorEditor.h"
#include "SimpleSynthVoice.h"
#include "SimpleSynthSound.h"

SimpleSynthAudioProcessor::SimpleSynthAudioProcessor()
    : needsUIUpdate(false)
{
    synth.addVoice(new SimpleSynthVoice());
    synth.addSound(new SimpleSynthSound());

    // copy parameters from the voice
    // FIXME: have voices share parameters somehow so we can have multiple voices
    
    SimpleSynthVoice* firstVoice = static_cast<SimpleSynthVoice*>(synth.getVoice(0));
    parameters = firstVoice->getParameters();

    // get a list of all parameter ids so we can surface them as plugin parameters
    // in a known order

    for (auto& param : *parameters) {
        parameterIds.push_back(param.first);
    }

}

void SimpleSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    keyboardState.reset();
}

void SimpleSynthAudioProcessor::releaseResources()
{
    keyboardState.reset();
}


void SimpleSynthAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();
    
    // clear input and output
    for (int i = 0; i < getNumOutputChannels(); ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
    keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);

    synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
    
    // apply gain (volume parameter)
    /*
    for (int i = 0; i < getNumOutputChannels(); ++i) {
        buffer.applyGain(i, 0, buffer.getNumSamples(), params[volumeParam]);
    }
    */
}

AudioProcessorEditor* SimpleSynthAudioProcessor::createEditor() {
    return new SimpleSynthAudioProcessorEditor(this);
}


int SimpleSynthAudioProcessor::getNumParameters()
{
    return parameterIds.size();
}

float SimpleSynthAudioProcessor::getParameter(int index)
{
    if (index < 0 || index >= parameterIds.size()) {
        return 0.0f;
    }
    
    return (*parameters)[parameterIds[index]]->getFloatValueLinear();
}

void SimpleSynthAudioProcessor::setParameter(int index, float newValue)
{
    if (index < 0 || index >= parameterIds.size()) {
        return;
    }

    (*parameters)[parameterIds[index]]->setFloatValueLinear(newValue);
    
    // needsUIUpdate = true;
}

const String SimpleSynthAudioProcessor::getParameterName(int index)
{
    if (index < 0 || index >= parameterIds.size()) {
        return String::empty;
    }
    
    return String(parameterIds[index] +
                  + " (" + (*parameters)[parameterIds[index]]->getName() + ')');
}

const String SimpleSynthAudioProcessor::getParameterText(int index)
{
    if (index < 0 && index > parameterIds.size()) {
        return String::empty;
    }
    
    return (*parameters)[parameterIds[index]]->getValueText();
}


void SimpleSynthAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    XmlElement xml(JucePlugin_Name "_settings");
    
    for (const String& paramId : parameterIds) {
        xml.setAttribute(paramId, (*parameters)[paramId]->getFloatValueLinear());
    }
    
    copyXmlToBinary(xml, destData);
}

void SimpleSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
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
            
            needsUIUpdate = true;
        }
    }
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleSynthAudioProcessor();
}
