#ifndef CHORDGENERATOR_H_INCLUDED
#define CHORDGENERATOR_H_INCLUDED

#include <vector>

#include "EventGenerator.h"

#include "Chord.h"

/**
 * Generates a backing chord track
 */
class ChordGenerator : public EventGenerator
{
public:
    ChordGenerator(const std::vector<Chord> &chordProgression, int channel = 1)
        : EventGenerator(channel),
        chordProgression(chordProgression)
    {}
    
    void generate(const Meter &start, EventSequence &eventSequence);
    
private:
    std::vector<Chord> chordProgression;
};




#endif  // CHORDGENERATOR_H_INCLUDED
