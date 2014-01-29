#include "SynthADSR.h"

SynthADSR::SynthADSR(double sampleRate)
    : Generator(sampleRate),
    Parameterized({
        {"attackTime", make_shared<Parameter<double>>("Attack Time", 0.01, 0.0, 1.0)},
        {"decayTime", make_shared<Parameter<double>>("Decay Time", 0.01, 0.0, 1.0)},
        {"sustainLevel", make_shared<Parameter<double>>("Sustain Level", 1.0, 0.0, 1.0)},
        {"releaseTime", make_shared<Parameter<double>>("Release Time", 0.01, 0.0, 1.0)}
    }),
    adsr(sampleRate)
{
    for (auto &param : *parameters) {
        param.second->addListener(this);
    }
    
    adsr.setAttackTime(getParameter<double>("attackTime")->getValue());
    adsr.setDecayTime(getParameter<double>("decayTime")->getValue());
    adsr.setSustainLevel(getParameter<double>("sustainLevel")->getValue());
    adsr.setReleaseTime(getParameter<double>("releaseTime")->getValue());
}


void SynthADSR::startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition)
{
    adsr.start();
}

void SynthADSR::stopNote()
{
    adsr.release();
}

bool SynthADSR::isActive()
{
    return adsr.isActive();
}

double SynthADSR::generateValue()
{
    return adsr.generateValue();
}

double SynthADSR::tick()
{
    return adsr.tick();
}

void SynthADSR::reset()
{
    adsr.reset();
}

void SynthADSR::parameterValueChanged(ParameterBase* param)
{
    if (param == getParameter("attackTime").get()) {
        adsr.setAttackTime(Rescale<double>::warp(dynamic_cast<Parameter<double>*>(param)->getValue(),
                                                 1, 2000, 100));
    } else if (param == getParameter("decayTime").get()) {
        adsr.setDecayTime(Rescale<double>::warp(dynamic_cast<Parameter<double>*>(param)->getValue(),
                                                1, 2000, 100));
    } else if (param == getParameter("sustainLevel").get()) {
        adsr.setSustainLevel(dynamic_cast<Parameter<double>*>(param)->getValue());
    } else if (param == getParameter("releaseTime").get()) {
        adsr.setReleaseTime(Rescale<double>::warp(dynamic_cast<Parameter<double>*>(param)->getValue(),
                                                  1, 2000, 100));
    }
}