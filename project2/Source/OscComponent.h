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

#ifndef __JUCE_HEADER_5064EF4C8118798__
#define __JUCE_HEADER_5064EF4C8118798__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "WaveformOscillator.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class OscComponent  : public Component,
                      public SliderListener,
                      public ComboBoxListener
{
public:
    //==============================================================================
    OscComponent ();
    ~OscComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    double getLevel() const { return level; }
    Waveform getWaveform() const { return waveform; }
    int getOctave() const { return octave; }
    int getSemi() const { return semi; }
    double getDetune() const { return detune; }

    void setLevel(double newValue);
    void setWaveform(Waveform newValue);
    void setOctave(int newValue);
    void setSemi(int newValue);
    void setDetune(double newValue);

    class JUCE_API Listener
    {
    public:
        virtual ~Listener()  {}

        virtual void oscLevelChanged(OscComponent*) = 0;
        virtual void oscWaveformChanged(OscComponent*) = 0;
        virtual void oscOctaveChanged(OscComponent*) = 0;
        virtual void oscSemiChanged(OscComponent*) = 0;
        virtual void oscDetuneChanged(OscComponent*) = 0;
    };

    void addListener(Listener* newListener) { listeners.add(newListener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ListenerList<Listener> listeners;

    double level;
    Waveform waveform;
    int octave;
    int semi;
    double detune;

    void sendLevelChangedMessage();
    void sendWaveformChangedMessage();
    void sendOctaveChangedMessage();
    void sendSemiChangedMessage();
    void sendDetuneChangedMessage();

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> semiSlider;
    ScopedPointer<Label> semiLabel;
    ScopedPointer<ComboBox> waveformComboBox;
    ScopedPointer<Label> waveformLabel;
    ScopedPointer<Slider> detuneSlider;
    ScopedPointer<Label> detuneLabel;
    ScopedPointer<Slider> octaveSlider;
    ScopedPointer<Label> octaveLabel;
    ScopedPointer<Slider> levelSlider;
    ScopedPointer<Label> LevelLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_5064EF4C8118798__
