#ifndef PLUGINPROCESSOR_H
#define PLUGINPROCESSOR_H

#include <vector>

#include "JuceHeader.h"

#include "Parameter.h"
#include "ParameterizedAudioProcessor.h"

#include "EventSequence.h"
#include "DrumGenerator.h"
#include "BassGenerator.h"
#include "ChordGenerator.h"

#include "AlgoCompoProcessorEditor.h"


class AlgoCompoAudioProcessor  : public ParameterizedAudioProcessor
{
    friend class AlgoCompoAudioProcessorEditor;
public:
    AlgoCompoAudioProcessor();
    ~AlgoCompoAudioProcessor();

    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer &buffer, MidiBuffer &midiMessages);

    
    void selectGenerator(int newChoice);
    
    
    
    void parameterValueChanged(ParameterBase* param);
    
    bool hasEditor() const { return true; }
    AudioProcessorEditor* createEditor() {
        return new AlgoCompoAudioProcessorEditor(this);
    }
    
    const String getName() const { return JucePlugin_Name; }

    
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

private:
    int bpm;
    TimeSignature timeSignature;
    
    bool playingNote;
    int64 startTime;
    
    double secondsPerSample;
    int samplesPerBlock;

    double time;
    Meter meter;
    AudioPlayHead::CurrentPositionInfo pos;
    
    EventSequence eventSequence;
    DrumGenerator drumGenerator;
    BassGenerator bassGenerator;
    ChordGenerator chordGenerator;
    
    int selectedGenerator = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgoCompoAudioProcessor)
};

#endif
