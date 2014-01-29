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

#include "ADSRComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ADSRComponent::ADSRComponent ()
{
    addAndMakeVisible (attackSlider = new Slider ("Attack slider"));
    attackSlider->setTooltip (TRANS("Attack"));
    attackSlider->setRange (5, 15000, 0);
    attackSlider->setSliderStyle (Slider::LinearVertical);
    attackSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    attackSlider->addListener (this);
    attackSlider->setSkewFactor (0.4);

    addAndMakeVisible (decaySlider = new Slider (String::empty));
    decaySlider->setTooltip (TRANS("Decay"));
    decaySlider->setRange (5, 15000, 0);
    decaySlider->setSliderStyle (Slider::LinearVertical);
    decaySlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    decaySlider->addListener (this);
    decaySlider->setSkewFactor (0.4);

    addAndMakeVisible (sustainSlider = new Slider (String::empty));
    sustainSlider->setTooltip (TRANS("Sustain"));
    sustainSlider->setRange (0, 1, 0);
    sustainSlider->setSliderStyle (Slider::LinearVertical);
    sustainSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    sustainSlider->addListener (this);

    addAndMakeVisible (releaseSlider = new Slider (String::empty));
    releaseSlider->setTooltip (TRANS("Release"));
    releaseSlider->setRange (5, 15000, 0);
    releaseSlider->setSliderStyle (Slider::LinearVertical);
    releaseSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    releaseSlider->addListener (this);
    releaseSlider->setSkewFactor (0.4);

    addAndMakeVisible (attackLabel = new Label (String::empty,
                                                TRANS("A")));
    attackLabel->setFont (Font (15.00f, Font::bold));
    attackLabel->setJustificationType (Justification::centred);
    attackLabel->setEditable (false, false, false);
    attackLabel->setColour (TextEditor::textColourId, Colours::black);
    attackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (decayLabel = new Label (String::empty,
                                               TRANS("D")));
    decayLabel->setFont (Font (15.00f, Font::bold));
    decayLabel->setJustificationType (Justification::centred);
    decayLabel->setEditable (false, false, false);
    decayLabel->setColour (TextEditor::textColourId, Colours::black);
    decayLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sustainLabel = new Label (String::empty,
                                                 TRANS("S")));
    sustainLabel->setFont (Font (15.00f, Font::bold));
    sustainLabel->setJustificationType (Justification::centred);
    sustainLabel->setEditable (false, false, false);
    sustainLabel->setColour (TextEditor::textColourId, Colours::black);
    sustainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (releaseLabel = new Label (String::empty,
                                                 TRANS("R")));
    releaseLabel->setFont (Font (15.00f, Font::bold));
    releaseLabel->setJustificationType (Justification::centred);
    releaseLabel->setEditable (false, false, false);
    releaseLabel->setColour (TextEditor::textColourId, Colours::black);
    releaseLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    setAttack(5);
    setDecay(5);
    setSustain(1);
    setRelease(5);
    //[/Constructor]
}

ADSRComponent::~ADSRComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    attackSlider = nullptr;
    decaySlider = nullptr;
    sustainSlider = nullptr;
    releaseSlider = nullptr;
    attackLabel = nullptr;
    decayLabel = nullptr;
    sustainLabel = nullptr;
    releaseLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ADSRComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ADSRComponent::resized()
{
    attackSlider->setBounds (0, 0, proportionOfWidth (0.2504f), getHeight() - 30);
    decaySlider->setBounds ((0) + (proportionOfWidth (0.2504f)), 0, proportionOfWidth (0.2504f), getHeight() - 30);
    sustainSlider->setBounds (((0) + (proportionOfWidth (0.2504f))) + (proportionOfWidth (0.2504f)), 0, proportionOfWidth (0.2504f), getHeight() - 30);
    releaseSlider->setBounds ((((0) + (proportionOfWidth (0.2504f))) + (proportionOfWidth (0.2504f))) + (proportionOfWidth (0.2504f)), 0, proportionOfWidth (0.2504f), getHeight() - 30);
    attackLabel->setBounds ((0) + 0, getHeight() - 30, roundFloatToInt ((proportionOfWidth (0.2504f)) * 1.0000f), 30);
    decayLabel->setBounds (((0) + (proportionOfWidth (0.2504f))) + 0, getHeight() - 30, roundFloatToInt ((proportionOfWidth (0.2504f)) * 1.0000f), 30);
    sustainLabel->setBounds ((((0) + (proportionOfWidth (0.2504f))) + (proportionOfWidth (0.2504f))) + 0, (0) + (getHeight() - 30), roundFloatToInt ((proportionOfWidth (0.2504f)) * 1.0000f), 30);
    releaseLabel->setBounds (((((0) + (proportionOfWidth (0.2504f))) + (proportionOfWidth (0.2504f))) + (proportionOfWidth (0.2504f))) + 0, (0) + (getHeight() - 30), roundFloatToInt ((proportionOfWidth (0.2504f)) * 1.0000f), 30);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ADSRComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == attackSlider)
    {
        //[UserSliderCode_attackSlider] -- add your slider handling code here..
        attack = attackSlider->getValue();
        sendAttackChangedMessage();
        //[/UserSliderCode_attackSlider]
    }
    else if (sliderThatWasMoved == decaySlider)
    {
        //[UserSliderCode_decaySlider] -- add your slider handling code here..
        decay = decaySlider->getValue();
        sendDecayChangedMessage();
        //[/UserSliderCode_decaySlider]
    }
    else if (sliderThatWasMoved == sustainSlider)
    {
        //[UserSliderCode_sustainSlider] -- add your slider handling code here..
        sustain = sustainSlider->getValue();
        sendSustainChangedMessage();
        //[/UserSliderCode_sustainSlider]
    }
    else if (sliderThatWasMoved == releaseSlider)
    {
        //[UserSliderCode_releaseSlider] -- add your slider handling code here..
        release = releaseSlider->getValue();
        sendReleaseChangedMessage();
        //[/UserSliderCode_releaseSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ADSRComponent::setAttack(double newValue)
{
    attack = newValue;
    attackSlider->setValue(attack);
}

void ADSRComponent::setDecay(double newValue)
{
    decay = newValue;
    decaySlider->setValue(decay);
}

void ADSRComponent::setSustain(double newValue)
{
    sustain = newValue;
    sustainSlider->setValue(sustain);
}

void ADSRComponent::setRelease(double newValue)
{
    release = newValue;
    releaseSlider->setValue(release);
}

void ADSRComponent::sendAttackChangedMessage()
{
    Component::BailOutChecker checker(this);
    
    if (!checker.shouldBailOut())
        listeners.callChecked(checker, &ADSRComponent::Listener::adsrAttackChanged, this);
}

void ADSRComponent::sendDecayChangedMessage()
{
    Component::BailOutChecker checker(this);
    
    if (!checker.shouldBailOut())
        listeners.callChecked(checker, &ADSRComponent::Listener::adsrDecayChanged, this);
}

void ADSRComponent::sendSustainChangedMessage()
{
    Component::BailOutChecker checker(this);
    
    if (!checker.shouldBailOut())
        listeners.callChecked(checker, &ADSRComponent::Listener::adsrSustainChanged, this);
}

void ADSRComponent::sendReleaseChangedMessage()
{
    Component::BailOutChecker checker(this);
    
    if (!checker.shouldBailOut())
        listeners.callChecked(checker, &ADSRComponent::Listener::adsrReleaseChanged, this);
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ADSRComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Attack slider" id="7f7857eed0d2277a" memberName="attackSlider"
          virtualName="" explicitFocusOrder="0" pos="0 0 25.039% 30M" posRelativeX="8c289f7475dc46a4"
          posRelativeY="8c289f7475dc46a4" posRelativeW="8c289f7475dc46a4"
          posRelativeH="8c289f7475dc46a4" tooltip="Attack" min="5" max="15000"
          int="0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.4000000000000000222"/>
  <SLIDER name="" id="23a645b25113f09" memberName="decaySlider" virtualName=""
          explicitFocusOrder="0" pos="0R 0 25.039% 30M" posRelativeX="7f7857eed0d2277a"
          posRelativeY="8c289f7475dc46a4" posRelativeW="8c289f7475dc46a4"
          posRelativeH="8c289f7475dc46a4" tooltip="Decay" min="5" max="15000"
          int="0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.4000000000000000222"/>
  <SLIDER name="" id="eff3d0d7628bf331" memberName="sustainSlider" virtualName=""
          explicitFocusOrder="0" pos="0R 0 25.039% 30M" posRelativeX="23a645b25113f09"
          posRelativeY="8c289f7475dc46a4" posRelativeW="8c289f7475dc46a4"
          posRelativeH="8c289f7475dc46a4" tooltip="Sustain" min="0" max="1"
          int="0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="" id="3e5214333495e0c9" memberName="releaseSlider" virtualName=""
          explicitFocusOrder="0" pos="0R 0 25.039% 30M" posRelativeX="eff3d0d7628bf331"
          posRelativeY="8c289f7475dc46a4" posRelativeW="8c289f7475dc46a4"
          posRelativeH="8c289f7475dc46a4" tooltip="Release" min="5" max="15000"
          int="0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="0.4000000000000000222"/>
  <LABEL name="" id="c0ba3e933abba5e" memberName="attackLabel" virtualName=""
         explicitFocusOrder="0" pos="0 0Rr 100% 30" posRelativeX="7f7857eed0d2277a"
         posRelativeW="7f7857eed0d2277a" posRelativeH="8c289f7475dc46a4"
         edTextCol="ff000000" edBkgCol="0" labelText="A" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="36"/>
  <LABEL name="" id="172ce0ab4cb86bd3" memberName="decayLabel" virtualName=""
         explicitFocusOrder="0" pos="0 0Rr 100% 30" posRelativeX="23a645b25113f09"
         posRelativeW="23a645b25113f09" posRelativeH="8c289f7475dc46a4"
         edTextCol="ff000000" edBkgCol="0" labelText="D" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="1" italic="0" justification="36"/>
  <LABEL name="" id="309cbab7ba8649a4" memberName="sustainLabel" virtualName=""
         explicitFocusOrder="0" pos="0 0R 100% 30" posRelativeX="eff3d0d7628bf331"
         posRelativeY="eff3d0d7628bf331" posRelativeW="eff3d0d7628bf331"
         posRelativeH="8c289f7475dc46a4" edTextCol="ff000000" edBkgCol="0"
         labelText="S" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="36"/>
  <LABEL name="" id="d4a9b959690b76ee" memberName="releaseLabel" virtualName=""
         explicitFocusOrder="0" pos="0 0R 100% 30" posRelativeX="3e5214333495e0c9"
         posRelativeY="3e5214333495e0c9" posRelativeW="3e5214333495e0c9"
         posRelativeH="8c289f7475dc46a4" edTextCol="ff000000" edBkgCol="0"
         labelText="R" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="1" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
