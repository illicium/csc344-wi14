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
//[/Headers]

#include "OscComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
OscComponent::OscComponent ()
{
    addAndMakeVisible (semiSlider = new Slider (String::empty));
    semiSlider->setTooltip (TRANS("Semi"));
    semiSlider->setRange (-12, 12, 1);
    semiSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    semiSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    semiSlider->addListener (this);

    addAndMakeVisible (semiLabel = new Label (String::empty,
                                              TRANS("Semi")));
    semiLabel->setFont (Font (15.00f, Font::bold));
    semiLabel->setJustificationType (Justification::centred);
    semiLabel->setEditable (false, false, false);
    semiLabel->setColour (TextEditor::textColourId, Colours::black);
    semiLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (waveformComboBox = new ComboBox (String::empty));
    waveformComboBox->setEditableText (false);
    waveformComboBox->setJustificationType (Justification::centredLeft);
    waveformComboBox->setTextWhenNothingSelected (TRANS("Sine"));
    waveformComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    waveformComboBox->addItem (TRANS("Sine"), 1);
    waveformComboBox->addItem (TRANS("Square"), 2);
    waveformComboBox->addItem (TRANS("Sawtooth"), 3);
    waveformComboBox->addItem (TRANS("Triangle"), 4);
    waveformComboBox->addItem (TRANS("Noise"), 5);
    waveformComboBox->addListener (this);

    addAndMakeVisible (waveformLabel = new Label (String::empty,
                                                  TRANS("Waveform")));
    waveformLabel->setFont (Font (15.00f, Font::bold));
    waveformLabel->setJustificationType (Justification::centred);
    waveformLabel->setEditable (false, false, false);
    waveformLabel->setColour (TextEditor::textColourId, Colours::black);
    waveformLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (detuneSlider = new Slider (String::empty));
    detuneSlider->setTooltip (TRANS("Detune"));
    detuneSlider->setRange (-1, 1, 0);
    detuneSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    detuneSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    detuneSlider->addListener (this);

    addAndMakeVisible (detuneLabel = new Label (String::empty,
                                                TRANS("Detune")));
    detuneLabel->setFont (Font (15.00f, Font::bold));
    detuneLabel->setJustificationType (Justification::centred);
    detuneLabel->setEditable (false, false, false);
    detuneLabel->setColour (TextEditor::textColourId, Colours::black);
    detuneLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (octaveSlider = new Slider (String::empty));
    octaveSlider->setTooltip (TRANS("Octave"));
    octaveSlider->setRange (-3, 3, 1);
    octaveSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    octaveSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    octaveSlider->addListener (this);

    addAndMakeVisible (octaveLabel = new Label (String::empty,
                                                TRANS("Octave")));
    octaveLabel->setFont (Font (15.00f, Font::bold));
    octaveLabel->setJustificationType (Justification::centred);
    octaveLabel->setEditable (false, false, false);
    octaveLabel->setColour (TextEditor::textColourId, Colours::black);
    octaveLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (levelSlider = new Slider (String::empty));
    levelSlider->setTooltip (TRANS("Level"));
    levelSlider->setRange (-40, 6, 0);
    levelSlider->setSliderStyle (Slider::LinearBar);
    levelSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    levelSlider->addListener (this);
    levelSlider->setSkewFactor (2);

    addAndMakeVisible (LevelLabel = new Label (String::empty,
                                               TRANS("Level")));
    LevelLabel->setFont (Font (15.00f, Font::bold));
    LevelLabel->setJustificationType (Justification::centred);
    LevelLabel->setEditable (false, false, false);
    LevelLabel->setColour (TextEditor::textColourId, Colours::black);
    LevelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (450, 120);


    //[Constructor] You can add your own custom stuff here..
    setLevel(0);
    setWaveform(Waveform::SINE);
    setOctave(0);
    setSemi(0);
    setDetune(0);
    //[/Constructor]
}

OscComponent::~OscComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    semiSlider = nullptr;
    semiLabel = nullptr;
    waveformComboBox = nullptr;
    waveformLabel = nullptr;
    detuneSlider = nullptr;
    detuneLabel = nullptr;
    octaveSlider = nullptr;
    octaveLabel = nullptr;
    levelSlider = nullptr;
    LevelLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void OscComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void OscComponent::resized()
{
    semiSlider->setBounds (280, 8, 72, 80);
    semiLabel->setBounds ((280) + 0, (8) + (80) - -5, roundFloatToInt ((72) * 1.0000f), 20);
    waveformComboBox->setBounds (8, 64, 150, 24);
    waveformLabel->setBounds ((8) + 0, (64) + (24) - -5, roundFloatToInt ((150) * 1.0000f), 20);
    detuneSlider->setBounds (368, 8, 72, 80);
    detuneLabel->setBounds ((368) + 0, (8) + (80) - -5, roundFloatToInt ((72) * 1.0000f), 20);
    octaveSlider->setBounds (192, 8, 72, 80);
    octaveLabel->setBounds ((192) + 0, (8) + (80) - -5, roundFloatToInt ((72) * 1.0000f), 20);
    levelSlider->setBounds (8, 8, 152, 24);
    LevelLabel->setBounds ((8) + 0, (8) + (24) - -5, roundFloatToInt ((152) * 1.0000f), 20);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void OscComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == semiSlider)
    {
        //[UserSliderCode_semiSlider] -- add your slider handling code here..
        semi = (int) semiSlider->getValue();
        sendSemiChangedMessage();
        //[/UserSliderCode_semiSlider]
    }
    else if (sliderThatWasMoved == detuneSlider)
    {
        //[UserSliderCode_detuneSlider] -- add your slider handling code here..
        detune = detuneSlider->getValue();
        sendDetuneChangedMessage();
        //[/UserSliderCode_detuneSlider]
    }
    else if (sliderThatWasMoved == octaveSlider)
    {
        //[UserSliderCode_octaveSlider] -- add your slider handling code here..
        octave = (int) octaveSlider->getValue();
        sendOctaveChangedMessage();
        //[/UserSliderCode_octaveSlider]
    }
    else if (sliderThatWasMoved == levelSlider)
    {
        //[UserSliderCode_levelSlider] -- add your slider handling code here..
        level = levelSlider->getValue();
        sendLevelChangedMessage();
        //[/UserSliderCode_levelSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void OscComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == waveformComboBox)
    {
        //[UserComboBoxCode_waveformComboBox] -- add your combo box handling code here..
        // this will blow up if the items in the combo box don't match the enum 1:1
        waveform = static_cast<Waveform>(waveformComboBox->getSelectedItemIndex());
        sendWaveformChangedMessage();
        //[/UserComboBoxCode_waveformComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void OscComponent::setLevel(double newValue)
{
    level = newValue;
    levelSlider->setValue(level);
}

void OscComponent::setWaveform(Waveform newValue)
{
    waveform = newValue;
    waveformComboBox->setSelectedItemIndex(static_cast<int>(waveform));
}

void OscComponent::setOctave(int newValue)
{
    octave = newValue;
    octaveSlider->setValue(octave);
}

void OscComponent::setSemi(int newValue)
{
    semi = newValue;
    semiSlider->setValue(semi);
}

void OscComponent::setDetune(double newValue)
{
    detune = newValue;
    detuneSlider->setValue(detune);
}


void OscComponent::sendLevelChangedMessage()
{
    Component::BailOutChecker checker(this);

    if (!checker.shouldBailOut())
        listeners.callChecked(checker, &OscComponent::Listener::oscLevelChanged, this);
}

void OscComponent::sendWaveformChangedMessage()
{
    Component::BailOutChecker checker(this);

    if (!checker.shouldBailOut())
        listeners.callChecked(checker, &OscComponent::Listener::oscWaveformChanged, this);
}

void OscComponent::sendOctaveChangedMessage()
{
    Component::BailOutChecker checker(this);

    if (!checker.shouldBailOut())
        listeners.callChecked(checker, &OscComponent::Listener::oscOctaveChanged, this);
}

void OscComponent::sendSemiChangedMessage()
{
    Component::BailOutChecker checker(this);

    if (!checker.shouldBailOut())
        listeners.callChecked(checker, &OscComponent::Listener::oscSemiChanged, this);
}

void OscComponent::sendDetuneChangedMessage()
{
    Component::BailOutChecker checker(this);

    if (!checker.shouldBailOut())
        listeners.callChecked(checker, &OscComponent::Listener::oscDetuneChanged, this);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="OscComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="450" initialHeight="120">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="" id="a24e595036e5737" memberName="semiSlider" virtualName=""
          explicitFocusOrder="0" pos="280 8 72 80" tooltip="Semi" min="-12"
          max="12" int="1" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="9071c4ccf755e743" memberName="semiLabel" virtualName=""
         explicitFocusOrder="0" pos="0 -5R 100% 20" posRelativeX="a24e595036e5737"
         posRelativeY="a24e595036e5737" posRelativeW="a24e595036e5737"
         posRelativeH="a24e595036e5737" edTextCol="ff000000" edBkgCol="0"
         labelText="Semi" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="36"/>
  <COMBOBOX name="" id="21ebf971dc4a34e1" memberName="waveformComboBox" virtualName=""
            explicitFocusOrder="0" pos="8 64 150 24" editable="0" layout="33"
            items="Sine&#10;Square&#10;Sawtooth&#10;Triangle&#10;Noise" textWhenNonSelected="Sine"
            textWhenNoItems="(no choices)"/>
  <LABEL name="" id="e0ce5c6a9d97094f" memberName="waveformLabel" virtualName=""
         explicitFocusOrder="0" pos="0 -5R 100% 20" posRelativeX="21ebf971dc4a34e1"
         posRelativeY="21ebf971dc4a34e1" posRelativeW="21ebf971dc4a34e1"
         posRelativeH="a24e595036e5737" edTextCol="ff000000" edBkgCol="0"
         labelText="Waveform" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="36"/>
  <SLIDER name="" id="bb68078b6cb5cd41" memberName="detuneSlider" virtualName=""
          explicitFocusOrder="0" pos="368 8 72 80" tooltip="Detune" min="-1"
          max="1" int="0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="6b7db7ee8bc3351c" memberName="detuneLabel" virtualName=""
         explicitFocusOrder="0" pos="0 -5R 100% 20" posRelativeX="bb68078b6cb5cd41"
         posRelativeY="bb68078b6cb5cd41" posRelativeW="bb68078b6cb5cd41"
         posRelativeH="bb68078b6cb5cd41" edTextCol="ff000000" edBkgCol="0"
         labelText="Detune" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="36"/>
  <SLIDER name="" id="3cf5a873d5ce8fda" memberName="octaveSlider" virtualName=""
          explicitFocusOrder="0" pos="192 8 72 80" tooltip="Octave" min="-3"
          max="3" int="1" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="" id="39251cf78aaef6f6" memberName="octaveLabel" virtualName=""
         explicitFocusOrder="0" pos="0 -5R 100% 20" posRelativeX="3cf5a873d5ce8fda"
         posRelativeY="3cf5a873d5ce8fda" posRelativeW="3cf5a873d5ce8fda"
         posRelativeH="3cf5a873d5ce8fda" edTextCol="ff000000" edBkgCol="0"
         labelText="Octave" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="36"/>
  <SLIDER name="" id="3c9628338ae1fa55" memberName="levelSlider" virtualName=""
          explicitFocusOrder="0" pos="8 8 152 24" tooltip="Level" min="-40"
          max="6" int="0" style="LinearBar" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="2"/>
  <LABEL name="" id="f48e3f149a2e587d" memberName="LevelLabel" virtualName=""
         explicitFocusOrder="0" pos="0 -5R 100% 20" posRelativeX="3c9628338ae1fa55"
         posRelativeY="3c9628338ae1fa55" posRelativeW="3c9628338ae1fa55"
         posRelativeH="3c9628338ae1fa55" edTextCol="ff000000" edBkgCol="0"
         labelText="Level" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
