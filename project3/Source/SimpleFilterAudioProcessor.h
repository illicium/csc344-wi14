#ifndef SIMPLEFILTERAUDIOPROCESSOR_H
#define SIMPLEFILTERAUDIOPROCESSOR_H

#include <memory>
#include <vector>
#include <complex>
using namespace std;

#include "../JuceLibraryCode/JuceHeader.h"

#include "Parameter.h"
#include "ChebyshevFilter.h"

class SimpleFilterAudioProcessor : public AudioProcessor,
                                   public Parameterized,
                                   public ParameterBase::Listener
{
public:
    SimpleFilterAudioProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
    
    void parameterValueChanged(ParameterBase* param);
    
    bool hasEditor() const { return false; }
    AudioProcessorEditor* createEditor() {
        return nullptr;
    }

    const String getName() const { return JucePlugin_Name; }

    int getNumParameters();
    float getParameter(int index);
    void setParameter(int index, float newValue);

    const String getParameterName(int index);
    const String getParameterText(int index);

    const String getInputChannelName(int channelIndex) const
    {
        return String (channelIndex + 1);
    }
    const String getOutputChannelName(int channelIndex) const
    {
        return String (channelIndex + 1);
    }
    bool isInputChannelStereoPair(int index) const { return true; }
    bool isOutputChannelStereoPair(int index) const { return true; }

    bool acceptsMidi() const
    {
        #if JucePlugin_WantsMidiInput
            return true;
        #else
            return false;
        #endif
    }

    bool producesMidi() const
    {
        #if JucePlugin_ProducesMidiOutput
            return true;
        #else
            return false;
        #endif
    }

    bool silenceInProducesSilenceOut() const { return false; }

    double getTailLengthSeconds() const { return 0.0; }
    
    int getNumPrograms() { return 0; }
    int getCurrentProgram() { return 0; }
    void setCurrentProgram(int index) {}
    const String getProgramName(int index) { return String::empty; }
    void changeProgramName(int index, const String& newName) {}

    void getStateInformation(MemoryBlock& destData);
    void setStateInformation(const void* data, int sizeInBytes);  

private:
    void updateFilterTheta();
    double calculateFilterTheta(double sampleRate);
    
    vector<String> parameterIds;
    
    ChebyshevFilter filter;
    AudioSampleBuffer filterDelayBuffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFilterAudioProcessor)
};

#endif