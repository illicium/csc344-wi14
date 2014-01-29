#include "Oscillator.h"
#include <ostream>

Oscillator::Oscillator(double sampleRate)
    : Generator(sampleRate, 0.0),
    curAngle(0.0)
{
    setAmplitude(1.0);
    setFrequency(440);
    setPhase(0);
}


void Oscillator::setAmplitude(double newValue)
{
    amplitude = newValue;
}


void Oscillator::setFrequency(double newValue)
{
    frequency = newValue > 1 ? newValue : 1;
    
    period = sampleRate / frequency;
    angleDelta = 2.0 * double_Pi * (1.0 / period);
}

void Oscillator::setPhase(double newValue)
{
    phase = newValue;
}

double Oscillator::tick()
{
    generateValue();
    
    curAngle += angleDelta;
    if (curAngle > 2.0 * double_Pi) {
        curAngle -= 2.0 * double_Pi;
    }
    
    return value;
}


void Oscillator::reset()
{
    curAngle = 0.0;
}