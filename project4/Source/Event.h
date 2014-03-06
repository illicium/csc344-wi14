#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <cstring>
#include <boost/operators.hpp>

#include "JuceHeader.h"

#include "Meter.h"

class Event : boost::partially_ordered<Event>
{
public:
    Event(MidiMessage midiMessage, Meter eventTime)
        : midiMessage(midiMessage), eventTime(eventTime) {}
    virtual ~Event() {};

    void setMidiMessage(MidiMessage newMessage) { midiMessage = newMessage; }
    const MidiMessage& getMidiMessage() const { return midiMessage; }

    void setEventTime(Meter newTime) { eventTime = newTime; };
    const Meter& getEventTime() const { return eventTime; };
    
    bool operator<(const Event &rhs) const
    {
        // FIXME: look at midiMessage and put noteoffs before noteons for
        // events with the same channel, notenumber, and time
        return getEventTime() < rhs.getEventTime();
    }
    
    bool operator==(const Event &rhs) const
    {
        const MidiMessage &rhsMidiMessage = rhs.getMidiMessage();
        return (getEventTime() == rhs.getEventTime()) &&
            (midiMessage.getRawDataSize() == rhsMidiMessage.getRawDataSize()) &&
            (std::memcmp(midiMessage.getRawData(), rhsMidiMessage.getRawData(),
                         midiMessage.getRawDataSize()) == 0);
    }
    
protected:
    MidiMessage midiMessage;
    Meter eventTime;
    
};



#endif  // EVENT_H_INCLUDED
