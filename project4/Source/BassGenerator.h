#ifndef BASSGENERATOR_H_INCLUDED
#define BASSGENERATOR_H_INCLUDED

#include <vector>

#include "EventGenerator.h"
#include "Note.h"
#include "Chord.h"

/**
 * Generates a bassline
 */
class BassGenerator : public EventGenerator
{
public:
    BassGenerator(int channel = 1)
        : EventGenerator(channel)
    {}
    
    BassGenerator(const std::vector<Chord> &chordProgression, int channel = 1)
        : EventGenerator(channel),
        chordProgression(chordProgression)
    {}
    
    void generate(const Meter &start, EventSequence &eventSequence);
    
private:
    std::vector<Chord> chordProgression;
};



#endif  // BASSGENERATOR_H_INCLUDED
