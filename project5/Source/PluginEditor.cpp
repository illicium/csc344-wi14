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

//[Headers] You can add your own extra header files here...
#include "PluginProcessor.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConvolutionAudioProcessorEditor::ConvolutionAudioProcessorEditor (ConvolutionAudioProcessor *owner)
    : AudioProcessorEditor(owner),
      owner(owner)
{
    addAndMakeVisible (bypassButton = new ToggleButton ("Bypass Toggle"));
    bypassButton->setButtonText (TRANS("Bypass"));
    bypassButton->addListener (this);

    addAndMakeVisible (irFilename = new FilenameComponent ("IR Filename",
                                                           File(),
                                                           true,
                                                           false,
                                                           false,
                                                           String::empty,
                                                           String::empty,
                                                           String::empty));
    irFilename->setName ("IR Filename");

    addAndMakeVisible (irLabel = new Label ("Impulse Response Label",
                                            TRANS("Impulse Response")));
    irLabel->setFont (Font (15.00f, Font::bold));
    irLabel->setJustificationType (Justification::centredLeft);
    irLabel->setEditable (false, false, false);
    irLabel->setColour (TextEditor::textColourId, Colours::black);
    irLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (processTimeLabelLabel = new Label ("Process Time Label Label",
                                                          TRANS("Process Time (avg)")));
    processTimeLabelLabel->setFont (Font (15.00f, Font::bold));
    processTimeLabelLabel->setJustificationType (Justification::centredLeft);
    processTimeLabelLabel->setEditable (false, false, false);
    processTimeLabelLabel->setColour (TextEditor::textColourId, Colours::black);
    processTimeLabelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (processTimeValueLabel = new Label ("Process Time Value Label",
                                                          TRANS("0")));
    processTimeValueLabel->setFont (Font (15.00f, Font::plain));
    processTimeValueLabel->setJustificationType (Justification::centredLeft);
    processTimeValueLabel->setEditable (false, false, false);
    processTimeValueLabel->setColour (TextEditor::textColourId, Colours::black);
    processTimeValueLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    irFilename->addListener(this);
    startTimer(100);
    //[/Constructor]
}

ConvolutionAudioProcessorEditor::~ConvolutionAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    bypassButton = nullptr;
    irFilename = nullptr;
    irLabel = nullptr;
    processTimeLabelLabel = nullptr;
    processTimeValueLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConvolutionAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConvolutionAudioProcessorEditor::resized()
{
    bypassButton->setBounds (184, 80, 150, 24);
    irFilename->setBounds (184, 32, 272, 24);
    irLabel->setBounds (24, 32, 128, 24);
    processTimeLabelLabel->setBounds (24, 128, 150, 24);
    processTimeValueLabel->setBounds (184, 128, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConvolutionAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bypassButton)
    {
        //[UserButtonCode_bypassButton] -- add your button handler code here..
        owner->bypass = bypassButton->getToggleState();
        owner->processTimeAvg = 0;
        //[/UserButtonCode_bypassButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ConvolutionAudioProcessorEditor::filenameComponentChanged(FilenameComponent *fileComponentThatHasChanged)
{
    if (fileComponentThatHasChanged == irFilename)
    {
        owner->loadIrFile(irFilename->getCurrentFile());
    }
}

void ConvolutionAudioProcessorEditor::timerCallback()
{
    processTimeValueLabel->setText(String(owner->processTimeAvg) + " sec",
                                   dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConvolutionAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer, public FilenameComponentListener"
                 constructorParams="ConvolutionAudioProcessor *owner" variableInitialisers="AudioProcessorEditor(owner),&#10;owner(owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TOGGLEBUTTON name="Bypass Toggle" id="b8a0086e7f6735bb" memberName="bypassButton"
                virtualName="" explicitFocusOrder="0" pos="184 80 150 24" buttonText="Bypass"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <GENERICCOMPONENT name="IR Filename" id="a877807b9860ccfa" memberName="irFilename"
                    virtualName="" explicitFocusOrder="0" pos="184 32 272 24" class="FilenameComponent"
                    params="&quot;IR Filename&quot;,&#10;File(),&#10;true,&#10;false,&#10;false,&#10;String::empty,&#10;String::empty,&#10;String::empty"/>
  <LABEL name="Impulse Response Label" id="1aeec50e45ad4977" memberName="irLabel"
         virtualName="" explicitFocusOrder="0" pos="24 32 128 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Impulse Response" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <LABEL name="Process Time Label Label" id="9cdf7965750f14cf" memberName="processTimeLabelLabel"
         virtualName="" explicitFocusOrder="0" pos="24 128 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Process Time (avg)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="33"/>
  <LABEL name="Process Time Value Label" id="23cac2ef29d71b97" memberName="processTimeValueLabel"
         virtualName="" explicitFocusOrder="0" pos="184 128 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
