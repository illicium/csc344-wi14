#include "SimpleSynthVoice.h"
#include "SimpleSynthSound.h"

SimpleSynthVoice::SimpleSynthVoice()
    : curAngle(0.0),
    playing(false)
{
    gain = Decibels::decibelsToGain(-3.0);
}

void SimpleSynthVoice::startNote(int midiNoteNumber, float velocity,
                                 SynthesiserSound* /*sound*/,
                                 int /*currentPitchWheelPosition*/)
{
    freq = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    period = getSampleRate() / freq;
    angleDelta = 2.0 * double_Pi * (1.0 / period);
    playing = true;
}

void SimpleSynthVoice::stopNote(bool /* allowTailOff */)
{
    clearCurrentNote();
    curAngle = 0.0;
    playing = false;
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
        
        for (int i = 1; i * freq < getSampleRate() / 2; i += 2) {
            currentSample += (float) (sin(i * curAngle) * gain * (1.0 / i));
        }
        
        for (int i = outputBuffer.getNumChannels(); --i >= 0;) {
            *outputBuffer.getSampleData(i, startSample) += currentSample;
        }
        
        
        curAngle += angleDelta;
        if (curAngle > 2.0 * double_Pi) {
            curAngle -= 2.0 * double_Pi;
        }
        
        startSample++;
    }
}


bool SimpleSynthVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast<SimpleSynthSound*>(sound) != 0;
}