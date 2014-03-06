#include <iostream>

#include "DrumGenerator.h"
#include "Midi.h"

// one bar of 32nd notes
const float DrumGenerator::kickProbabilities[] =
    { 0.3, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.3, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.1,
      0.3, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.3, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.1 };
const float DrumGenerator::snareProbabilities[] =
    { 0.0, 0.0, 0.0, 0.0,  0.2, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.2, 0.0, 0.0, 0.1,
      0.0, 0.0, 0.0, 0.0,  0.2, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.2, 0.0, 0.0, 0.1 };
const float DrumGenerator::rideProbabilities[] =
    { 1.0, 0.0, 0.0, 0.0,  0.8, 0.0, 0.0, 1.0,  1.0, 0.0, 0.0, 0.0,  0.8, 0.0, 0.0, 1.0,
      1.0, 0.0, 0.0, 0.0,  0.8, 0.0, 0.0, 1.0,  1.0, 0.0, 0.0, 0.0,  0.8, 0.0, 0.0, 1.0 };
const float DrumGenerator::crashProbabilities[] =
    { 0.3, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0 };


void DrumGenerator::generate(const Meter &start, EventSequence &eventSequence)
{
    Random r;

    Meter curTime = start;
    Meter quarter{0, 1, 0};
    Meter sixteenth{0, 0, 1};
    Meter thirtysecond{0, 0, 0, 1};
    // back-to-back notes with the same channel/notenumber and end/start
    // aren't being sorted properly yet so leave some space in between them
    Meter thirtysecond_ish{0, 0, 0, 0.9};
    
    for (int bar = 0; bar < 10; bar++) {
        for (int n = 0; n < 32; n++) {
            if (r.nextFloat() < kickProbabilities[n]) {
                eventSequence.addNote(channel, Midi::Percussion::AcousticBassDrum, jmax(kickProbabilities[n] * 2, 1.0f),
                                      curTime, thirtysecond_ish);
            }

            if (r.nextFloat() < snareProbabilities[n]) {
                eventSequence.addNote(channel, Midi::Percussion::AcousticSnare, jmax(kickProbabilities[n] * 2, 1.0f),
                                      curTime, thirtysecond_ish);
            }

            if (r.nextFloat() < rideProbabilities[n]) {
                eventSequence.addNote(channel, Midi::Percussion::RideCymbal1, jmax(kickProbabilities[n] * 2, 1.0f),
                                      curTime, thirtysecond_ish);
            }

            if (r.nextFloat() < crashProbabilities[n]) {
                eventSequence.addNote(channel, Midi::Percussion::CrashCymbal1, jmax(kickProbabilities[n] * 2, 1.0f),
                                      curTime, thirtysecond_ish);
            }

            curTime += thirtysecond;
        }
    }

}