#ifndef SIMPLESYNTHVOICE_H
#define SIMPLESYNTHVOICE_H

#include "../JuceLibraryCode/JuceHeader.h"

class SimpleSynthVoice : public SynthesiserVoice
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
    double gain;
    double freq;
    double period;
    double curAngle;
    double angleDelta;
    bool playing;
};

#endif