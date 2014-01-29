#ifndef SYNTHOSC_H
#define SYNTHOSC_H

#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"

#include "Generator.h"
#include "PerformanceReactive.h"
#include "Parameter.h"
#include "WaveformOscillator.h"

/**
 * Synth oscillator building block that provides user-editable parameters like
 * waveform, octave, etc. and responds to start/stop note commands.
 * (but not quite a SynthesiserVoice)
 */
class SynthOsc : public Generator<double>,
                 public PerformanceReactive,
                 public Parameterized,
                 public ParameterBase::Listener
{
public:
    SynthOsc(double sampleRate);
    
    void startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition) override;
    void stopNote() override;
    
    /**
     * Return the frequency of the currently playing note (as modified by
     * parameters, pitch wheel, etc.)
     */
    double calculateNoteFrequency();
    
    double getValue() const override { return osc.getValue(); }
    
    double generateValue();
    
    double tick();
    void reset();

    void parameterValueChanged(ParameterBase* param);

    /**
     * Attach a generator to this SynthOsc that will modify its amplitude
     */
    void addAmplitudeModifier(shared_ptr<Generator<double>> modifier);

    /**
     * Attach a generator to this SynthOsc that will modify its frequency
     */
    void addFrequencyModifier(shared_ptr<Generator<double>> modifier);
    
private:
    WaveformOscillator osc;
    vector<shared_ptr<Generator<double>>> amplitudeModifiers;
    vector<shared_ptr<Generator<double>>> frequencyModifiers;
    
    int noteNumber;
    float velocity;
    double baseAmplitude;
    double baseFrequency;
};


#endif
