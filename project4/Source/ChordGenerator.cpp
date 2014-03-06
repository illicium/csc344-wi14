#include "ChordGenerator.h"

void ChordGenerator::generate(const Meter &start, EventSequence &eventSequence)
{
    Random r;
    
    Meter curTime = start;
    Meter quarter{0, 1, 0};
    Meter quarter_ish{0, 0, 0, 3.9};
    
    for (int bar = 0; bar < 10; bar++) {
        for (int n = 0; n < 16; n++) {
            eventSequence.addNote(channel, 60 + n, 1.0f,
                                  curTime, quarter_ish);
            
            curTime += quarter;
        }
    }
    
}