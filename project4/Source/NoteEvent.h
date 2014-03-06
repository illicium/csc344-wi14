#ifndef NOTEEVENT_H_INCLUDED
#define NOTEEVENT_H_INCLUDED
/*
#include "JuceHeader.h"

#include "Event.h"

class NoteEvent : public Event {
public:
    NoteEvent(int channel, int noteNumber, float velocity)
        : noteNumber(noteNumber), velocity(velocity)
    {}
    
    int getNoteNumber() const { return noteNumber; }
    int getNoteNumber() const { return noteNumber; }
    float getVelocity() const { return velocity; }
    
    virtual MidiMessage getMidiMessage() =0;
    
public:
    int channel;
    int noteNumber;
    float velocity;
};

class NoteOnEvent : public NoteEvent {
public:
    MidiMessage getMidiMessage()
    {
        return MidiMessage::noteOn(1, noteNumber, velocity);
    }
};

class NoteOffEvent : public NoteEvent {
public:
    MidiMessage getMidiMessage()
    {
        return MidiMessage::noteOff(1, noteNumber, velocity);
    }
};
*/

#endif  // NOTEEVENT_H_INCLUDED
