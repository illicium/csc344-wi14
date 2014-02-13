#ifndef PERFORMANCEREACTIVE_H
#define PERFORMANCEREACTIVE_H

/**
 * Base class for objects that react to performance events, like start/stop note,
 * controller changes, etc. This borrows from SynthesiserVoice, but decouples
 * receiving events from generating sample data.
 */
class PerformanceReactive
{
public:
    virtual ~PerformanceReactive() {}
    
    virtual void startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition) {}
    virtual void stopNote() {}
    virtual void pitchWheelMoved(int newValue) {}
    virtual void controllerMoved(int controllerNumber, int newValue) {}
    
};

#endif
