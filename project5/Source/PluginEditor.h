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

#ifndef __JUCE_HEADER_846B5CD9B4505A63__
#define __JUCE_HEADER_846B5CD9B4505A63__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
class ConvolutionAudioProcessor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ConvolutionAudioProcessorEditor  : public AudioProcessorEditor,
                                         public Timer,
                                         public FilenameComponentListener,
                                         public ButtonListener
{
public:
    //==============================================================================
    ConvolutionAudioProcessorEditor (ConvolutionAudioProcessor *owner);
    ~ConvolutionAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void filenameComponentChanged(FilenameComponent *fileComponentThatHasChanged);
    void timerCallback();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ConvolutionAudioProcessor *owner;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ToggleButton> bypassButton;
    ScopedPointer<FilenameComponent> irFilename;
    ScopedPointer<Label> irLabel;
    ScopedPointer<Label> processTimeLabelLabel;
    ScopedPointer<Label> processTimeValueLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolutionAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_846B5CD9B4505A63__
