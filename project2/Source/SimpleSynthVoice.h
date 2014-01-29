#ifndef SIMPLESYNTHVOICE_H
#define SIMPLESYNTHVOICE_H

#include <memory>

#include "../JuceLibraryCode/JuceHeader.h"

#include "SynthOsc.h"
#include "SynthADSR.h"
#include "SynthLFO.h"
#include "Parameter.h"

class SimpleSynthVoice : public SynthesiserVoice,
                         public Parameterized
{
public:
    SimpleSynthVoice();
        
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* sound,
                    int currentPitchWheelPosition);
    void stopNote (bool allowTailOff);
    void pitchWheelMoved (int newValue);
    void controllerMoved (int controllerNumber, int newValue);
    void renderNextBlock (AudioSampleBuffer& outputBuffer,
                          int startSample, int numSamples);

    bool canPlaySound (SynthesiserSound* sound);
    
private:
    shared_ptr<SynthOsc> osc1;
    shared_ptr<SynthOsc> osc2;
    shared_ptr<SynthADSR> adsr1;
    shared_ptr<SynthADSR> adsr2;
    shared_ptr<SynthLFO> lfo1;
    //shared_ptr<SynthLFO> lfo2;

    double freq;
    bool playing;
    
};

#endif