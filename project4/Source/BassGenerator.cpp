#include "BassGenerator.h"

#include "Midi.h"
#include "Scale.h"

void BassGenerator::generate(const Meter &start, EventSequence &eventSequence)
{
    Random r;
    
    Meter curTime = start;
    Meter half{0, 2, 0};
    Meter half_ish{0, 1, 3.9};
    Meter quarter{0, 1, 0};
    Meter quarter_ish{0, 0, 0, 3.9};
    
    for (auto chordIter = chordProgression.begin(); chordIter < chordProgression.end(); chordIter++) {
        const Chord &chord = *chordIter;
        const Chord &nextChord = (chordIter + 1 < chordProgression.end()) ?
            *(chordIter + 1) :
            *chordIter;
        const std::vector<int> &chordIntervals = chord.getIntervals();
        const Chord::Quality &chordQuality = chord.getQuality();
        
        Meter noteSize = half;
        Meter noteDuration = half_ish;
        int count = 1;
        if (r.nextFloat() < 0.5f) {
            noteSize = quarter;
            noteDuration = quarter_ish;
            count = 2;
        }

        Meter noteStart = curTime;
        
        int intervalOffset = 0;
        for (int c = 0; c < count; c++) {
            const std::vector<int> &scaleIntervals =
                Scale::getIntervals(Scale::getQualityForChordQuality(chordQuality));

            int interval = 0;
            if (chord.getRoot() == nextChord.getRoot()) {
                const int rand = r.nextInt(3);
                if (rand == 0) {
                    interval = chordIntervals[0];
                } else if (rand == 1) {
                    interval = chordIntervals[1]; // third
                } else {
                    interval = chordIntervals[2]; // fifth
                }
            } else {
                const int rand = r.nextInt(scaleIntervals.size());
                
                if (static_cast<int>(chord.getRoot()) <
                       static_cast<int>(nextChord.getRoot())) {
                    // ascending, maybe
                    intervalOffset = (intervalOffset + rand) % scaleIntervals.size();
                } else {
                    // descending, maybe
                    intervalOffset = (intervalOffset - rand) % scaleIntervals.size();
                }
                
                interval = scaleIntervals[intervalOffset];
            }

            int noteNumber = Midi::C2 +
                             static_cast<int>(chord.getRoot()) +
                             interval;
                
            eventSequence.addNote(channel, noteNumber, 1.0f,
                                  noteStart, noteDuration);
            
            noteStart += noteSize;
        }

        curTime += half;
    }
    
}