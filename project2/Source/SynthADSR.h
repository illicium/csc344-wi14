#ifndef SYNTHADSR_H
#define SYNTHADSR_H

#include "../JuceLibraryCode/JuceHeader.h"

#include "Generator.h"
#include "PerformanceReactive.h"
#include "Parameter.h"
#include "ADSR.h"

/**
 * Synth ADSR building block that provides user-editable parameters
 */
class SynthADSR : public Generator<double>,
                  public PerformanceReactive,
                  public Parameterized,
                  public ParameterBase::Listener
{
public:
    SynthADSR(double sampleRate);
    
    void startNote(int midiNoteNumber, float velocity, int currentPitchWheelPosition) override;
    void stopNote() override;
    
    /**
     * Returns true when this envelope is "in progress" (not before attack
     * or after the end of the release phase)
     */
    bool isActive();
    
    double getValue() const override { return adsr.getValue(); }

    double generateValue();
    
    double tick();
    void reset();
    
    void parameterValueChanged(ParameterBase* param);
    
private:
    ADSR adsr;
    
};




#endif  // SYNTHADSR_H_INCLUDED
