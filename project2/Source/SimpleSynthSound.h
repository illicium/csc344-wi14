#ifndef SIMPLESYNTHSOUND_H
#define SIMPLESYNTHSOUND_H

#include "../JuceLibraryCode/JuceHeader.h"

class SimpleSynthSound : public SynthesiserSound
{
public:
    SimpleSynthSound() {}
    
    bool appliesToNote (const int /*midiNoteNumber*/) { return true; }
    bool appliesToChannel (const int /*midiChannel*/) { return true; }
};

#endif
