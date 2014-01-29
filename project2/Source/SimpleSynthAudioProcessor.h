#ifndef SIMPLESYNTHAUDIOPROCESSOR_H
#define SIMPLESYNTHAUDIOPROCESSOR_H

#include <memory>
#include <vector>
using namespace std;

#include "../JuceLibraryCode/JuceHeader.h"

#include "Parameter.h"
#include "SimpleSynthVoice.h"

class SimpleSynthAudioProcessorEditor;

class SimpleSynthAudioProcessor : public AudioProcessor
{
    friend SimpleSynthAudioProcessorEditor;
public:
    SimpleSynthAudioProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages);
  
    bool hasEditor() const { return true; }
    AudioProcessorEditor* createEditor();

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
    bool needsUIUpdate;
    
    Synthesiser synth;
    MidiKeyboardState keyboardState;

    vector<shared_ptr<SimpleSynthVoice>> voices;
    
    vector<String> parameterIds;
    shared_ptr<Parameters> parameters;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessor)
};

#endif