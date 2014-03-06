#include "ChordGenerator.h"

#include "Midi.h"

void ChordGenerator::generate(const Meter &start, EventSequence &eventSequence)
{
    Random r;
    
    Meter curTime = start;
    Meter half{0, 2, 0};
    Meter quarter{0, 1, 0};
    Meter quarter_ish{0, 0, 0, 3.9};
    Meter eighth{0, 0, 2};
    Meter eighth_ish{0, 0, 0, 1.9};
    Meter sixteenth{0, 0, 1};
    Meter sixteenth_ish{0, 0, 0.9};
    
    Meter duration;
    
    for (const Chord &chord : chordProgression) {
        const std::vector<int> &chordIntervals = chord.getIntervals();

        duration = eighth_ish;
        for (int i = 0; i < 2; i++) {
            if (r.nextFloat() < 0.5f) {
                duration += sixteenth;
            }
        }
        
        for (int interval : chordIntervals) {
            int noteNumber = Midi::C2 +
                             static_cast<int>(chord.getRoot()) +
                             interval;
            
            Meter fudge{0, 0, 0, r.nextDouble() / 8};
            Meter fudge2{0, 0, 0, r.nextDouble() / 4};
            
            eventSequence.addNote(channel, noteNumber, 1.0f,
                                  curTime + fudge, duration + fudge2);
        }
        
        curTime += half;
    }
    
}