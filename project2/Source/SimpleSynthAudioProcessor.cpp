#include "SimpleSynthAudioProcessor.h"
#include "SimpleSynthAudioProcessorEditor.h"
#include "SimpleSynthVoice.h"
#include "SimpleSynthSound.h"

const float defaultGain = 1.0f;

SimpleSynthAudioProcessor::SimpleSynthAudioProcessor()
    : lastUIWidth(400),
    lastUIHeight(200),
    gain(defaultGain)
{
    for (int i = 0; i < 4; i++) {
        synth.addVoice(new SimpleSynthVoice());
    }
    
    synth.addSound(new SimpleSynthSound());
}

SimpleSynthAudioProcessor::~SimpleSynthAudioProcessor()
{
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
    
    // Go through the incoming data, and apply our gain to it...
    /*
     for (int channel = 0; channel < getNumInputChannels(); channel++) {
        buffer.applyGain(channel, 0, buffer.getNumSamples(), gain);
    }
     */
    
    // clear input and output
    for (int i = 0; i < getNumOutputChannels(); ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    
    keyboardState.processNextMidiBuffer(midiMessages, 0, numSamples, true);

    synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
    
    /*/
    for (int channel = 0; channel < getNumOutputChannels(); ++channel)
    {
        float* channelData = buffer.getSampleData(channel);
        
        for (int i = 0; i < numSamples; ++i)
        {
            channelData[i] = r.nextFloat();
        }
    }*/

}


AudioProcessorEditor* SimpleSynthAudioProcessor::createEditor()
{
    return new SimpleSynthAudioProcessorEditor(this);
}

bool SimpleSynthAudioProcessor::hasEditor() const
{
    return true;
}


const String SimpleSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}


int SimpleSynthAudioProcessor::getNumParameters()
{
    return 0;
}

float SimpleSynthAudioProcessor::getParameter(int index)
{
    return 0.0f;
}

void SimpleSynthAudioProcessor::setParameter(int index, float newValue)
{
}

const String SimpleSynthAudioProcessor::getParameterName(int index)
{
    return String::empty;
}

const String SimpleSynthAudioProcessor::getParameterText(int index)
{
    return String::empty;
}


const String SimpleSynthAudioProcessor::getInputChannelName(int channelIndex) const
{
    return String (channelIndex + 1);
}

const String SimpleSynthAudioProcessor::getOutputChannelName(int channelIndex) const
{
    return String (channelIndex + 1);
}

bool SimpleSynthAudioProcessor::isInputChannelStereoPair(int index) const
{
    return true;
}

bool SimpleSynthAudioProcessor::isOutputChannelStereoPair(int index) const
{
    return true;
}


bool SimpleSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double SimpleSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleSynthAudioProcessor::getNumPrograms()
{
    return 0;
}


int SimpleSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleSynthAudioProcessor::setCurrentProgram(int index)
{
}

const String SimpleSynthAudioProcessor::getProgramName(int index)
{
    return String::empty;
}

void SimpleSynthAudioProcessor::changeProgramName(int index, const String& newName)
{
}


void SimpleSynthAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    XmlElement xml (JucePlugin_Name "_settings");
    
    xml.setAttribute ("uiWidth", lastUIWidth);
    xml.setAttribute ("uiHeight", lastUIHeight);
    xml.setAttribute ("gain", gain);
    
    copyXmlToBinary (xml, destData);
}

void SimpleSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName(JucePlugin_Name "_settings"))
        {
            lastUIWidth = xmlState->getIntAttribute("uiWidth", lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute("uiHeight", lastUIHeight);
            
            gain  = (float) xmlState->getDoubleAttribute("gain", gain);
        }
    }
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleSynthAudioProcessor();
}
