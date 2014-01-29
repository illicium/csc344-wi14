#include "SynthLFO.h"

SynthLFO::SynthLFO(double sampleRate)
    : Generator(sampleRate),
    Parameterized({
        {"amount", make_shared<Parameter<double>>("Amount", 0.25, 0.0, 1.0)},
        {"frequency", make_shared<Parameter<double>>("Frequency", 0.1, 0.0, 1.0)},
        // FIXME: use Waveform enum instead
        {"waveform", make_shared<Parameter<int>>("Waveform",
                                                 0,
                                                 0,
                                                 static_cast<int>(Waveform::totalNumWaveforms) - 1)},
    }),
    lfo(sampleRate)
{
    for (auto &param : *parameters) {
        param.second->addListener(this);
    }
    
    lfo.setAmplitude(getParameter<double>("amount")->getValue());
    lfo.setFrequency(getParameter<double>("frequency")->getValue());
    lfo.setWaveform(static_cast<Waveform>(getParameter<int>("frequency")->getValue()));
}


void SynthLFO::startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition)
{
    lfo.reset();
}

void SynthLFO::stopNote()
{
    lfo.reset();
}

double SynthLFO::generateValue()
{
    return lfo.generateValue();
}

double SynthLFO::tick()
{
    return lfo.tick();
}

void SynthLFO::reset()
{
    lfo.reset();
}

void SynthLFO::parameterValueChanged(ParameterBase* param)
{
    if (param == getParameter("amount").get()) {
        lfo.setAmplitude(dynamic_cast<Parameter<double>*>(param)->getValue());
    } else if (param == getParameter("frequency").get()) {
        lfo.setFrequency(Rescale<double>::warp(dynamic_cast<Parameter<double>*>(param)->getValue(),
                                               0.5, 100, 5));
    } else if (param == getParameter("waveform").get()) {
        lfo.setWaveform(static_cast<Waveform>(dynamic_cast<Parameter<int>*>(param)->getValue()));
    }
}