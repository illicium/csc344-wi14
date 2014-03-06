#ifndef DRUMGENERATOR_H_INCLUDED
#define DRUMGENERATOR_H_INCLUDED

#include "EventGenerator.h"

/**
 * Generates a drum track
 */
class DrumGenerator : public EventGenerator
{
public:
    DrumGenerator(int channel = 1) : EventGenerator(channel) {}
    
    static const float kickProbabilities[];
    static const float snareProbabilities[];
    // static const float openHatProbabilities[];
    // static const float closedHatProbabilities[];
    static const float rideProbabilities[];
    static const float crashProbabilities[];
    
    void generate(const Meter &start, EventSequence &eventSequence);
};



#endif  // DRUMGENERATOR_H_INCLUDED
