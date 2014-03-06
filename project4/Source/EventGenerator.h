#ifndef EVENTGENERATOR_H_INCLUDED
#define EVENTGENERATOR_H_INCLUDED

#include "EventSequence.h"
#include "Meter.h"

class EventGenerator
{
public:
    EventGenerator(int channel = 1) : channel(channel)
    {
        if (channel < 1 || channel > 16) {
            throw std::invalid_argument("channel must be between 1-16");
        }
    }
    virtual ~EventGenerator() {}
    
    int getChannel() const { return channel; }
    
    virtual void generate(const Meter &start, EventSequence &eventSequence) =0;
    
protected:
    int channel;
    
};



#endif  // EVENTGENERATOR_H_INCLUDED
