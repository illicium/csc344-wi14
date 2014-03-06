#include "Chord.h"

const std::map<Chord::Quality, const std::vector<int>> Chord::intervals =
    {
        {Chord::Quality::Major, {0, 4, 7}},
        {Chord::Quality::Minor, {0, 3, 7}},
        {Chord::Quality::Augmented, {0, 4, 8}},
        {Chord::Quality::Diminished, {0, 3, 6}},
        {Chord::Quality::MajorSeventh, {0, 4, 7, 10}},
        {Chord::Quality::MinorSeventh, {0, 3, 7, 9}},
        {Chord::Quality::DominantSeventh, {0, 4, 7, 9}}
    };

const std::vector<int>& Chord::getIntervals() const
{
    return intervals.at(quality);
}