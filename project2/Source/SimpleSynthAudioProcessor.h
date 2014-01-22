#ifndef SIMPLESYNTHAUDIOPROCESSOR_H
#define SIMPLESYNTHAUDIOPROCESSOR_H

#include "../JuceLibraryCode/JuceHeader.h"

class SimpleSynthAudioProcessor : public AudioProcessor
{
    friend class SimpleSynthAudioProcessorEditor;
    
public:
    SimpleSynthAudioProcessor();
    ~SimpleSynthAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

private:
    Synthesiser synth;

    MidiKeyboardState keyboardState;
    
    int lastUIWidth, lastUIHeight;
    
    enum Parameters
    {
        gainParam = 0,
        
        totalNumParams
    };
    
    float gain;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessor)
};

#endif