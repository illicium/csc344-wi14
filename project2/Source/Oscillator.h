#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "../JuceLibraryCode/JuceHeader.h"

#include "Generator.h"

/**
 * Base class for oscillators, which are a type of periodic Generator with an
 * amplitude and frequency.
 */
class Oscillator : public Generator<double>
{
public:
    Oscillator(double sampleRate);
    virtual ~Oscillator() {}

    void setAmplitude(double newValue);
    void setFrequency(double newValue);
    void setPhase(double newValue);
    
    double getAmplitude() const { return amplitude; }
    double getFrequency() const { return frequency; }
    double getPhase() const { return phase; }
    
    double tick();
    void reset();
    
protected:
    double amplitude; // 0-1
    double frequency; // Hz
    double phase; // 0-1
    
    double period;
    double curAngle;
    double angleDelta;
};



#endif