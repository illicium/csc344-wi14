#ifndef EVENTSEQUENCE_H_INCLUDED
#define EVENTSEQUENCE_H_INCLUDED

#include <set>

#include "Event.h"
#include "Meter.h"
#include "TimeSignature.h"

class EventSequence
{
public:
    void add(Event e);
    
    void clear();
    
    const std::vector<Event>::size_type size() const { return events.size(); }
    
    /**
     * Add a note on/off pair to the sequence at the given `time`,
     * with `duration` time in between.
     * The note-off will have a velocity of zero.
     */
    void addNote(int channel, int noteNumber, float velocity,
                 const Meter &time, const Meter &duration);

    /**
     * Put events from startTime into the midiBuffer, in which the
     * timestamps are defined by the audioBufferSize and sampleRate.
     * Only those messages that fit into the current midi buffer (as defined
     * by the audioBufferSize) will be put into the buffer
     */
    void process(const Meter &startTime, MidiBuffer &midiBuffer,
                 double bpm, int audioBufferSize, int sampleRate);
    
public:
    std::vector<Event> events;
};



#endif  // EVENTSEQUENCE_H_INCLUDED
