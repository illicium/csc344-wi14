#ifndef CHORD_H_INCLUDED
#define CHORD_H_INCLUDED

#include <vector>

#include "Note.h"

class Chord
{
    enum class Quality {
        Major,
        Minor,
        Augmented,
        Diminished,
        MajorSeventh,
        MinorSeventh,
        AugmentedSeventh,
        DiminishedSeventh
    };
    
public:
    Chord(Note::Name root, Quality quality)
        : root(root), quality(quality);

    /**
     * Return the note intervals, starting from 0 (tonic) for this chord
     */
    std::vector<int> getIntervals() const;
    
private:
    Note::Name root;
    Quality quality;
    
};



#endif  // CHORD_H_INCLUDED
