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

#ifndef __JUCE_HEADER_FB368B6614B4876__
#define __JUCE_HEADER_FB368B6614B4876__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "Meter.h"
class AlgoCompoAudioProcessor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class AlgoCompoAudioProcessorEditor  : public AudioProcessorEditor,
                                       public Timer,
                                       public ComboBoxListener
{
public:
    //==============================================================================
    AlgoCompoAudioProcessorEditor (AlgoCompoAudioProcessor *owner);
    ~AlgoCompoAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void displayPositionInfo();

    AlgoCompoAudioProcessor *owner;

    double lastDisplayedTime;
    int lastDisplayedEvents;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> timeLabel;
    ScopedPointer<Label> numEventsLabel;
    ScopedPointer<ComboBox> generatorComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgoCompoAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_FB368B6614B4876__
