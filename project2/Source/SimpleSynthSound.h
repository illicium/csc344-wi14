#ifndef SIMPLESYNTHSOUND_H
#define SIMPLESYNTHSOUND_H

#include "../JuceLibraryCode/JuceHeader.h"

class SimpleSynthVoice;

class SimpleSynthSound : public SynthesiserSound
{
    friend SimpleSynthVoice;
public:
    bool appliesToNote (const int /*midiNoteNumber*/) { return true; }
    bool appliesToChannel (const int /*midiChannel*/) { return true; }    
};

#endif
