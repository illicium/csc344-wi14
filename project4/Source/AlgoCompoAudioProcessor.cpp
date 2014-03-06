#include <iostream>

#include "AlgoCompoAudioProcessor.h"

#include "Meter.h"


AlgoCompoAudioProcessor::AlgoCompoAudioProcessor()
    : bpm(120),
    timeSignature(TimeSignature::COMMON_TIME),
    drumGenerator(DrumGenerator()),
    bassGenerator(BassGenerator()),
    selectedGenerator(1)
{
}

AlgoCompoAudioProcessor::~AlgoCompoAudioProcessor()
{
}

void AlgoCompoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock_)
{
    time = 0;
    
    secondsPerSample = 1.0 / sampleRate;
    samplesPerBlock = samplesPerBlock_;
}

void AlgoCompoAudioProcessor::releaseResources()
{
}

void AlgoCompoAudioProcessor::processBlock (AudioSampleBuffer &buffer, MidiBuffer &midiMessages)
{
    AudioPlayHead *playhead = nullptr; // getPlayHead();
    if (playhead != nullptr) {
        playhead->getCurrentPosition(pos);
        
        bpm = pos.bpm;
        timeSignature = TimeSignature(pos.timeSigNumerator,
                                      pos.timeSigDenominator);

        if (pos.isPlaying || pos.isRecording) {
            time = pos.timeInSeconds;
        } else {
            return;
        }
    } else {
        pos.resetToDefault();
    }

    meter = Meter::fromSeconds(time, bpm, timeSignature);

    if (eventSequence.size() == 0 || time == 0) {
        eventSequence.clear();
        
        if (selectedGenerator == 0) {
            drumGenerator.generate(meter, eventSequence);
        } else if (selectedGenerator == 1) {
            bassGenerator.generate(meter, eventSequence);
        } else if (selectedGenerator == 2) {
            chordGenerator.generate(meter, eventSequence);
        }
    }
    
    eventSequence.process(meter, midiMessages,
                          bpm, buffer.getNumSamples(), getSampleRate());

    if (playhead == nullptr) {
        time += secondsPerSample * samplesPerBlock;
    }

}

void AlgoCompoAudioProcessor::selectGenerator(int newChoice)
{
    selectedGenerator = newChoice;
    eventSequence.clear();
}


AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlgoCompoAudioProcessor();
}