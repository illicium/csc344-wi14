/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_AC504DDDFFB3AE9E__
#define __JUCE_HEADER_AC504DDDFFB3AE9E__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SimpleSynthAudioProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
Main GUI component
                                                                    //[/Comments]
*/
class SimpleSynthAudioProcessorEditor  : public AudioProcessorEditor,
                                         public Timer
{
public:
    //==============================================================================
    SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor *processor);
    ~SimpleSynthAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    SimpleSynthAudioProcessor* getProcessor() const
    {
        return static_cast<SimpleSynthAudioProcessor*>(getAudioProcessor());
    }

    void timerCallback();

    /*
    void oscLevelChanged(OscComponent* osc);
    void oscWaveformChanged(OscComponent* osc);
    void oscOctaveChanged(OscComponent* osc);
    void oscSemiChanged(OscComponent* osc);
    void oscDetuneChanged(OscComponent* osc);

    void adsrAttackChanged(ADSRComponent *adsr);
    void adsrDecayChanged(ADSRComponent *adsr);
    void adsrSustainChanged(ADSRComponent *adsr);
    void adsrReleaseChanged(ADSRComponent *adsr);
    */

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<MidiKeyboardComponent> midiKeyboardComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_AC504DDDFFB3AE9E__
