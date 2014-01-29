#include "WaveformOscillator.h"

WaveformOscillator::WaveformOscillator(double sampleRate)
    : Oscillator(sampleRate),
    waveform(Waveform::SINE) {}

double WaveformOscillator::generateValue()
{
   double angle = curAngle;
    
   switch (waveform) {
        case Waveform::SINE:
            value = sin(angle) * amplitude;
            break;
        case Waveform::SQUARE:
        case Waveform::SAWTOOTH:
        case Waveform::TRIANGLE: {
            value = 0;
            
            // sawtooth has both even and odd harmonics; square and triangle
            // have only odd harmonics
            int harmonicStep = (waveform == Waveform::SAWTOOTH) ? 1 : 2;
            
            for (int i = 1; i * frequency < sampleRate / 2; i += harmonicStep) {
                double harmonicValue = sin(i * angle) * amplitude;
                
                // harmonic amplitudes decay proportionally to their number/frequency
                if (waveform == Waveform::TRIANGLE) {
                    // triangle harmonics decay faster and are alternately
                    // added/subtracted negative for 3, 7, 11, ...
                    //              and positive for 5, 9, 13, ...
                    harmonicValue *= 1.0 / (i * i);
                    if (i > 1 && i + 1 % 4 == 0) {
                        harmonicValue = -harmonicValue;
                    }
                } else {
                    harmonicValue *= 1.0 / i;
                }
                
                value += harmonicValue;
            }
            break;
        }
        case Waveform::NOISE:
            value = Random::getSystemRandom().nextDouble() * 2.0f * amplitude - (amplitude / 2);
            break;
        case Waveform::totalNumWaveforms:
        default:
            break;
    }
    
    return value;
}