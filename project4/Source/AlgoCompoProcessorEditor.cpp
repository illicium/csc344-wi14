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
#include "AlgoCompoAudioProcessor.h"
//[/Headers]

#include "AlgoCompoProcessorEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AlgoCompoAudioProcessorEditor::AlgoCompoAudioProcessorEditor (AlgoCompoAudioProcessor *owner)
    : AudioProcessorEditor(owner),
      owner(owner)
{
    addAndMakeVisible (timeLabel = new Label ("Time label",
                                              TRANS("<time>")));
    timeLabel->setFont (Font (32.00f, Font::plain));
    timeLabel->setJustificationType (Justification::centredLeft);
    timeLabel->setEditable (false, false, false);
    timeLabel->setColour (TextEditor::textColourId, Colours::black);
    timeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (numEventsLabel = new Label ("Num Events Label",
                                                   TRANS("Events: 0")));
    numEventsLabel->setFont (Font (15.00f, Font::plain));
    numEventsLabel->setJustificationType (Justification::centredLeft);
    numEventsLabel->setEditable (false, false, false);
    numEventsLabel->setColour (TextEditor::textColourId, Colours::black);
    numEventsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (generatorComboBox = new ComboBox ("Generator Combo Box"));
    generatorComboBox->setEditableText (false);
    generatorComboBox->setJustificationType (Justification::centredLeft);
    generatorComboBox->setTextWhenNothingSelected (TRANS("Drums"));
    generatorComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    generatorComboBox->addItem (TRANS("Drums"), 1);
    generatorComboBox->addItem (TRANS("Bass"), 2);
    generatorComboBox->addItem (TRANS("Chords"), 3);
    generatorComboBox->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    startTimer(50);
    //[/Constructor]
}

AlgoCompoAudioProcessorEditor::~AlgoCompoAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    timeLabel = nullptr;
    numEventsLabel = nullptr;
    generatorComboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AlgoCompoAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AlgoCompoAudioProcessorEditor::resized()
{
    timeLabel->setBounds (32, 32, 520, 24);
    numEventsLabel->setBounds (40, 144, 150, 24);
    generatorComboBox->setBounds (48, 88, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AlgoCompoAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == generatorComboBox)
    {
        //[UserComboBoxCode_generatorComboBox] -- add your combo box handling code here..
        owner->selectGenerator(generatorComboBox->getSelectedItemIndex());
        //[/UserComboBoxCode_generatorComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void AlgoCompoAudioProcessorEditor::timerCallback()
{
    if (owner->time != lastDisplayedTime) {
        displayPositionInfo();
    }

    if (owner->eventSequence.size() != lastDisplayedEvents) {
        String displayText;
        displayText.preallocateBytes (128);

        displayText << "Events: " << (int) owner->eventSequence.size();

        numEventsLabel->setText(displayText, dontSendNotification);

        lastDisplayedEvents = owner->eventSequence.size();
    }
}

void AlgoCompoAudioProcessorEditor::displayPositionInfo()
{
    lastDisplayedTime = owner->time;

    String displayText;
    displayText.preallocateBytes (128);

    displayText << owner->time <<
                '(' << owner->meter.getBars() << '|' << owner->meter.getBeats() << '|'
                    << owner->meter.getSixteenths() << '|' << owner->meter.getRemainder() << ')' <<
                " [" << owner->timeSignature.getNumerator() << '/' << owner->timeSignature.getDenominator() << ']';

    if (owner->pos.isRecording) {
        displayText << "  (recording)";
    } else if (owner->pos.isPlaying) {
        displayText << "  (playing)";
    }

    timeLabel->setText(displayText, dontSendNotification);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AlgoCompoAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="AlgoCompoAudioProcessor *owner" variableInitialisers="AudioProcessorEditor(owner),&#10;owner(owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="Time label" id="4e4a6e48d8716f64" memberName="timeLabel"
         virtualName="" explicitFocusOrder="0" pos="32 32 520 24" edTextCol="ff000000"
         edBkgCol="0" labelText="&lt;time&gt;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="32" bold="0" italic="0" justification="33"/>
  <LABEL name="Num Events Label" id="b12de3b9879e3539" memberName="numEventsLabel"
         virtualName="" explicitFocusOrder="0" pos="40 144 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Events: 0" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Generator Combo Box" id="bae13ffd17014d09" memberName="generatorComboBox"
            virtualName="" explicitFocusOrder="0" pos="48 88 150 24" editable="0"
            layout="33" items="Drums&#10;Bass&#10;Chords" textWhenNonSelected="Drums"
            textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
