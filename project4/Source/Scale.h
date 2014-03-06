#ifndef SCALE_H_INCLUDED
#define SCALE_H_INCLUDED

#include <vector>
#include <map>

#include "Chord.h"

class Scale
{
public:
    enum class Quality {
        Major,
        NaturalMinor,
        HarmonicMinor,
        Chromatic
    };
    
    /**
     * Return the note intervals, starting from 0 (tonic) for this scale quality
     */
    static const std::vector<int>& getIntervals(Scale::Quality quality);
    
    /**
     * Given a chord quality, return the corresponding(ish) scale quality
     */
    static Quality getQualityForChordQuality(Chord::Quality chordQuality);
    
private:
    static const std::map<Scale::Quality, const std::vector<int>> intervals;
};



#endif  // SCALE_H_INCLUDED
