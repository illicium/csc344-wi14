#ifndef CHORDGENERATOR_H_INCLUDED
#define CHORDGENERATOR_H_INCLUDED

#include "EventGenerator.h"

/**
 * Generates a backing chord track
 */
class ChordGenerator : public EventGenerator
{
public:
    ChordGenerator(int channel = 1) : EventGenerator(channel) {}
    
    void generate(const Meter &start, EventSequence &eventSequence);
};




#endif  // CHORDGENERATOR_H_INCLUDED
