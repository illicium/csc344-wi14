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

#ifndef __JUCE_HEADER_2C90FED4CD64E19E__
#define __JUCE_HEADER_2C90FED4CD64E19E__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ADSRComponent  : public Component,
                       public SliderListener
{
public:
    //==============================================================================
    ADSRComponent ();
    ~ADSRComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    double getAttack() const { return attack; }
    double getDecay() const { return decay; }
    double getSustain() const { return sustain; }
    double getRelease() const { return release; }

    void setAttack(double newValue);
    void setDecay(double newValue);
    void setSustain(double newValue);
    void setRelease(double newValue);


    class JUCE_API Listener
    {
    public:
        virtual ~Listener()  {}

        virtual void adsrAttackChanged(ADSRComponent*) = 0;
        virtual void adsrDecayChanged(ADSRComponent*) = 0;
        virtual void adsrSustainChanged(ADSRComponent*) = 0;
        virtual void adsrReleaseChanged(ADSRComponent*) = 0;
    };

    void addListener(Listener* newListener) { listeners.add(newListener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ListenerList<Listener> listeners;

    double attack;
    double decay;
    double sustain;
    double release;

    void sendAttackChangedMessage();
    void sendDecayChangedMessage();
    void sendSustainChangedMessage();
    void sendReleaseChangedMessage();

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> attackSlider;
    ScopedPointer<Slider> decaySlider;
    ScopedPointer<Slider> sustainSlider;
    ScopedPointer<Slider> releaseSlider;
    ScopedPointer<Label> attackLabel;
    ScopedPointer<Label> decayLabel;
    ScopedPointer<Label> sustainLabel;
    ScopedPointer<Label> releaseLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_2C90FED4CD64E19E__
