#ifndef BASSGENERATOR_H_INCLUDED
#define BASSGENERATOR_H_INCLUDED

#include "EventGenerator.h"
#include "Note.h"

/**
 * Generates a bassline
 */
class BassGenerator : public EventGenerator
{
public:
    BassGenerator(int channel = 1)
        : EventGenerator(channel),
        key(Note::Name::C)
    {}
    
    BassGenerator(Note::Name key, int channel = 1)
        : EventGenerator(channel),
        key(key)
    {}
    
    void generate(const Meter &start, EventSequence &eventSequence);
    
private:
    Note::Name key;
};



#endif  // BASSGENERATOR_H_INCLUDED
