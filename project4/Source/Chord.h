#ifndef CHORD_H_INCLUDED
#define CHORD_H_INCLUDED

#include <vector>
#include <map>

#include "Note.h"

class Chord
{
public:
    enum class Quality {
        Major,
        Minor,
        Augmented,
        Diminished,
        MajorSeventh,
        MinorSeventh,
        DominantSeventh
    };
    
    
    Chord(Note::Name root, Quality quality)
        : root(root), quality(quality)
    {}

    Note::Name getRoot() const { return root; }
    Quality getQuality() const { return quality; }
    
    /**
     * Return the note intervals, starting from 0 (tonic) for this chord
     */
    const std::vector<int>& getIntervals() const;

private:
    Note::Name root;
    Quality quality;
    
    static const std::map<Quality, const std::vector<int>> intervals;
};


#endif  // CHORD_H_INCLUDED
