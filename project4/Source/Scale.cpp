#include "Scale.h"

const std::map<Scale::Quality, const std::vector<int>> Scale::intervals =
{
    {Scale::Quality::Major, {0, 2, 4, 5, 7, 9, 11}},
    {Scale::Quality::NaturalMinor, {0, 2, 3, 5, 7, 8, 10}},
    {Scale::Quality::HarmonicMinor, {0, 2, 3, 5, 7, 8, 11}},
    {Scale::Quality::Chromatic, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}}
};

const std::vector<int>& Scale::getIntervals(Scale::Quality quality)
{
    return intervals.at(quality);
}

Scale::Quality Scale::getQualityForChordQuality(Chord::Quality chordQuality)
{
    if (chordQuality == Chord::Quality::Major ||
        chordQuality == Chord::Quality::MajorSeventh ||
        chordQuality == Chord::Quality::DominantSeventh) {
        return Scale::Quality::Major;
    } else if (chordQuality == Chord::Quality::Minor ||
               chordQuality == Chord::Quality::MinorSeventh) {
        return Scale::Quality::NaturalMinor;
    } else {
        return Scale::Quality::Chromatic;
    }
}