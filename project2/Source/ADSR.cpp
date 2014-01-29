#include "Util.h"
#include "ADSR.h"

ADSR::ADSR(double sampleRate)
    : Generator<double>(sampleRate, 0.0),
    curTime(0.0),
    sustained(false),
    timeReleased(0.0),
    releasedValue(0.0)
{
    timeDelta = 1.0 / sampleRate;
}

void ADSR::start()
{
    curTime = 0.0;
    sustained = true;
}

void ADSR::release()
{
    sustained = false;
    timeReleased = curTime;
    releasedValue = value;
}

bool ADSR::isActive()
{
    return sustained || releasedValue != 0.0;
}

double ADSR::generateValue()
{
    if (!isActive()) {
        return value = 0.0;
    }
        
    double curTimeMs = curTime * 1000.0;
    
    if (sustained) {
        if (curTimeMs > 0.0 &&
            curTimeMs <= attackTime) { // attack
            
            value = Rescale<double>::inverseLinear(curTimeMs,
                                                   0.0,
                                                   attackTime);
        } else if (curTimeMs > attackTime &&
                   curTimeMs <= attackTime + decayTime) { // decay
            value = Rescale<double>::linear(Rescale<double>::inverseLinear(curTimeMs,
                                                                           attackTime,
                                                                           attackTime + decayTime),
                                            1.0,
                                            sustainLevel);
        } else if (curTimeMs > attackTime + decayTime) { // sustain
            value = sustainLevel;
        }
    } else {
        double timeReleasedMs = timeReleased * 1000.0;
        
        if (curTimeMs <= timeReleasedMs + releaseTime) { // in release
            value = Rescale<double>::linear(Rescale<double>::inverseLinear(curTimeMs,
                                                                           timeReleasedMs,
                                                                           timeReleasedMs + releaseTime),
                                            releasedValue,
                                            0.0);
        } else { // past end of release tail
            reset();
        }
    }

    return value;
}

double ADSR::tick()
{
    generateValue();
    
    curTime += timeDelta;
    
    return value;
}


void ADSR::reset()
{
    sustained = false;
    value = 0.0;
    curTime = 0.0;
    timeReleased = 0.0;
    releasedValue = 0.0;
}