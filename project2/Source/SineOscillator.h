#ifndef SINEOSCILLATOR_H
#define SINEOSCILLATOR_H

#include "../JuceLibraryCode/JuceHeader.h"

#include "Oscillator.h"

/**
 * A basic oscillator that generates a sine wave
 */
class SineOscillator : public Oscillator
{
public:
    SineOscillator(double sampleRate) : Oscillator(sampleRate) {}
    
    void generateValue()
    {
        value = sin(curAngle) * amplitude;
    }
};

#endif