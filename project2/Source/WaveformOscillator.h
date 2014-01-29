#ifndef WAVEFORMOSCILLATOR_H
#define WAVEFORMOSCILLATOR_H

#include "../JuceLibraryCode/JuceHeader.h"

#include "Oscillator.h"

/**
 * Waveforms that WaveformOscillator can generate
 */
enum class Waveform : int {
    SINE = 0,
    SQUARE,
    SAWTOOTH,
    TRIANGLE,
    NOISE,
    
    totalNumWaveforms
};

/**
 * An oscillator that generates one type of waveform (sine, square, etc.)
 */
class WaveformOscillator : public Oscillator
{
public:
    WaveformOscillator(double sampleRate);
    
    Waveform getWaveform() const { return waveform; }
    void setWaveform(Waveform newValue) { waveform = newValue; }
    
    double generateValue();

private:
    Waveform waveform;
};

#endif