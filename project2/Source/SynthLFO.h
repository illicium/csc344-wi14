#ifndef SYNTHLFO_H
#define SYNTHLFO_H

#include "../JuceLibraryCode/JuceHeader.h"

#include "Generator.h"
#include "PerformanceReactive.h"
#include "Parameter.h"
#include "WaveformOscillator.h"

/**
 * Synth LFO building block that provides user-editable parameters
 */
class SynthLFO : public Generator<double>,
                 public PerformanceReactive,
                 public Parameterized,
                 public ParameterBase::Listener
{
public:
    SynthLFO(double sampleRate);
    
    void startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition) override;
    void stopNote() override;
    
    double getValue() const override { return lfo.getValue(); }
    
    double generateValue();
    
    double tick();
    void reset();
    
    void parameterValueChanged(ParameterBase* param);
    
private:
    WaveformOscillator lfo;
    
};



#endif  // SYNTHLFO_H
