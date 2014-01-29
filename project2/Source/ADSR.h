#ifndef ADSR_H
#define ADSR_H

#include "../JuceLibraryCode/JuceHeader.h"

#include "Generator.h"

/**
 * An ADSR envelope generator
 */
class ADSR : public Generator<double>
{
public:
    ADSR(double sampleRate);
   
    // Times are in milliseconds

    void setAttackTime(double newValue) { attackTime = newValue; }
    void setDecayTime(double newValue) { decayTime = newValue; }
    void setSustainLevel(double newValue) { sustainLevel = newValue; }
    void setReleaseTime(double newValue) { releaseTime = newValue; }

    double getAttackTime() const { return attackTime; }
    double getDecayTime() const { return decayTime; }
    double getSustainLevel() const { return sustainLevel; }
    double getReleaseTime() const { return releaseTime; }

    /**
     * Start the envelope, and continue generating values through the
     * sustain period until stopped
     */
    void start();
    
    /**
     * Start the release phase of the envelope
     */
    void release();
    
    /**
     * Returns true when this envelope is "in progress" (not before attack
     * or after the end of the release phase)
     */
    bool isActive();
    
    double generateValue();
    double tick();
    void reset();
    
protected:
    double attackTime;
    double decayTime;
    double sustainLevel;
    double releaseTime;
    
    double curTime; // in seconds
    double timeDelta; // in seconds
    
    bool sustained;
    double timeReleased;
    double releasedValue;
};


#endif
