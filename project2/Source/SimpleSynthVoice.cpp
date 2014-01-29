#include "SimpleSynthVoice.h"
#include "SimpleSynthSound.h"


SimpleSynthVoice::SimpleSynthVoice()
    : osc1(make_shared<SynthOsc>(getSampleRate())),
    osc2(make_shared<SynthOsc>(getSampleRate())),
    adsr1(make_shared<SynthADSR>(getSampleRate())),
    adsr2(make_shared<SynthADSR>(getSampleRate())),
    lfo1(make_shared<SynthLFO>(getSampleRate())),
    //lfo2(make_shared<SynthLFO>(getSampleRate())),
    playing(false)
{
    inheritParameters(*osc1, "osc1");
    inheritParameters(*osc2, "osc2");
    inheritParameters(*adsr1, "adsr1");
    inheritParameters(*adsr2, "adsr2");
    inheritParameters(*lfo1, "lfo1");
    //inheritParameters(*lfo2, "lfo2");
    
    //osc1->addFrequencyModifier(osc2);
    
    osc1->addFrequencyModifier(lfo1);
    osc2->addFrequencyModifier(lfo1);
    
    osc1->addAmplitudeModifier(adsr1);
    osc2->addAmplitudeModifier(adsr2);
}

void SimpleSynthVoice::startNote(int midiNoteNumber, float velocity,
                                 SynthesiserSound* s,
                                 int currentPitchWheelPosition)
{
    osc1->startNote(midiNoteNumber, velocity, currentPitchWheelPosition);
    osc2->startNote(midiNoteNumber, velocity, currentPitchWheelPosition);
    adsr1->startNote(midiNoteNumber, velocity, currentPitchWheelPosition);
    adsr2->startNote(midiNoteNumber, velocity, currentPitchWheelPosition);
    lfo1->startNote(midiNoteNumber, velocity, currentPitchWheelPosition);
    //lfo2->startNote(midiNoteNumber, velocity, currentPitchWheelPosition);
    
    playing = true;
}

void SimpleSynthVoice::stopNote(bool /* allowTailOff */)
{
    clearCurrentNote();
    
    adsr1->stopNote();
    adsr2->stopNote();
    lfo1->stopNote();
    //lfo2->stopNote();
}

void SimpleSynthVoice::pitchWheelMoved(int /*newValue*/)
{
}

void SimpleSynthVoice::controllerMoved(int /*controllerNumber*/,
                                       int /*newValue*/)
{
}

void SimpleSynthVoice::renderNextBlock(AudioSampleBuffer& outputBuffer,
                                       int startSample, int numSamples)
{
    if (!playing)
        return;

    while (--numSamples >= 0) {
        float currentSample = 0.0f;

        currentSample = osc1->tick() + osc2->tick();
        
        adsr1->tick();
        adsr2->tick();
        lfo1->tick();
        //lfo2->tick();
        
        for (int i = outputBuffer.getNumChannels(); --i >= 0;) {
            *outputBuffer.getSampleData(i, startSample) += currentSample;
        }
        
        startSample++;
    }
    
    if (!adsr1->isActive() && !adsr2->isActive()) {
        osc1->stopNote();
        osc2->stopNote();
        playing = false;
    }
}


bool SimpleSynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<SimpleSynthSound*>(sound) != 0;
}