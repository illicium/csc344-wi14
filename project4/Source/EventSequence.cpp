#include <iostream>

#include "EventSequence.h"

void EventSequence::add(Event e)
{
    events.push_back(e);
    std::sort(events.begin(), events.end());
}

void EventSequence::clear()
{
    events.clear();
}

void EventSequence::addNote(int channel, int noteNumber, float velocity,
                            const Meter &time, const Meter &duration)
{
    add(Event(MidiMessage::noteOn(channel, noteNumber, velocity), time));
    add(Event(MidiMessage::noteOff(channel, noteNumber, 0.0f), time + duration));
}


void EventSequence::process(const Meter &startTime, MidiBuffer &midiBuffer,
                            double bpm, int audioBufferSize, int sampleRate)
{
    std::vector <Event>::iterator deleteEnd;
    bool deleteProcessed = false;

    double startSeconds = startTime.toSeconds(bpm);
    double endSeconds = startSeconds + (1.0 / sampleRate) * audioBufferSize;
    
    for (auto iter = events.begin(); iter < events.end(); iter++) {
        Event &e = *iter;
        Meter eventTime = e.getEventTime();
        double eventTimeSeconds = eventTime.toSeconds(bpm);
        
        if (eventTimeSeconds >= startSeconds &&
                eventTimeSeconds < endSeconds) {
            double offsetSeconds = eventTimeSeconds - startSeconds;
            double sampleNumber = offsetSeconds * sampleRate;
            assert(sampleNumber < audioBufferSize);
                        
            midiBuffer.addEvent(e.getMidiMessage(), sampleNumber);
            
            deleteProcessed = true;
            deleteEnd = iter + 1;
        }
    }
    
    if (deleteProcessed) {
        events.erase(events.begin(), deleteEnd);
    }

}