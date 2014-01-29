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
#include "Util.h"
#include "WaveformOscillator.h"
//[/Headers]

#include "SimpleSynthAudioProcessorEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor *processor)
    : AudioProcessorEditor(processor), Timer()
{
    addAndMakeVisible (midiKeyboardComponent = new MidiKeyboardComponent (processor->keyboardState, MidiKeyboardComponent::horizontalKeyboard));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    // oscComponent->addListener(this);
    // adsrComponent->addListener(this);
    // startTimer(200);

    //[/Constructor]
}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    midiKeyboardComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SimpleSynthAudioProcessorEditor::resized()
{
    midiKeyboardComponent->setBounds (0, getHeight() - 80, proportionOfWidth (1.0000f), 80);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SimpleSynthAudioProcessorEditor::timerCallback()
{
    /*
    SimpleSynthAudioProcessor *processor = getProcessor();

    if(processor->needsUIUpdate)
    {
        volumeSlider->setValue(Decibels::gainToDecibels(processor->getParameter(SimpleSynthAudioProcessor::volumeParam)));


        oscComponent->setLevel(Decibels::gainToDecibels(processor->getParameter(SimpleSynthAudioProcessor::osc1LevelParam)));
        oscComponent->setWaveform(static_cast<Waveform>(ParamValue<float>::intStep(processor->getParameter(SimpleSynthAudioProcessor::osc1WaveformParam),
                                                                                   0, static_cast<int>(Waveform::totalNumWaveforms) - 1)));
        oscComponent->setOctave(ParamValue<float>::intStep(processor->getParameter(SimpleSynthAudioProcessor::osc1OctaveParam),
                                                           -12, 12));
        oscComponent->setSemi(ParamValue<float>::intStep(processor->getParameter(SimpleSynthAudioProcessor::osc1SemiParam),
                                                         -3, 3));
        oscComponent->setDetune(ParamValue<float>::linear(processor->getParameter(SimpleSynthAudioProcessor::osc1DetuneParam),
                                                          -1, 1));


        adsrComponent->setAttack(ParamValue<double>::linear(processor->getParameter(SimpleSynthAudioProcessor::env1AParam),
                                                            5, 15000));
        adsrComponent->setDecay(ParamValue<double>::linear(processor->getParameter(SimpleSynthAudioProcessor::env1DParam),
                                                            5, 15000));
        adsrComponent->setSustain(processor->getParameter(SimpleSynthAudioProcessor::env1SParam));
        adsrComponent->setRelease(ParamValue<double>::linear(processor->getParameter(SimpleSynthAudioProcessor::env1RParam),
                                                             5, 15000));


        processor->needsUIUpdate = false;
    }
    */
}

/*
void SimpleSynthAudioProcessorEditor::oscLevelChanged(OscComponent* osc)
{
    getProcessor()->setParameterNotifyingHost(SimpleSynthAudioProcessor::osc1LevelParam,
                                              Decibels::decibelsToGain(osc->getLevel()));
    getProcessor()->needsUIUpdate = false;
}

void SimpleSynthAudioProcessorEditor::oscWaveformChanged(OscComponent* osc)
{
    getProcessor()->setParameterNotifyingHost(SimpleSynthAudioProcessor::osc1WaveformParam,
                                              ParamValue<float>::inverseIntStep(static_cast<int>(osc->getWaveform()),
                                                                                0, static_cast<int>(Waveform::totalNumWaveforms) - 1));
    getProcessor()->needsUIUpdate = false;
}

void SimpleSynthAudioProcessorEditor::oscOctaveChanged(OscComponent* osc)
{
    getProcessor()->setParameterNotifyingHost(SimpleSynthAudioProcessor::osc1OctaveParam,
                                              ParamValue<float>::inverseIntStep(osc->getOctave(),
                                                                               -3, 3));
    getProcessor()->needsUIUpdate = false;
}

void SimpleSynthAudioProcessorEditor::oscSemiChanged(OscComponent* osc)
{
    getProcessor()->setParameterNotifyingHost(SimpleSynthAudioProcessor::osc1SemiParam,
                                              ParamValue<float>::inverseIntStep(osc->getSemi(),
                                                                               -12, 12));
    getProcessor()->needsUIUpdate = false;
}

void SimpleSynthAudioProcessorEditor::oscDetuneChanged(OscComponent* osc)
{
    getProcessor()->setParameterNotifyingHost(SimpleSynthAudioProcessor::osc1DetuneParam,
                                              ParamValue<float>::inverseLinear(osc->getDetune(),
                                                                               -1, 1));
    getProcessor()->needsUIUpdate = false;
}


void SimpleSynthAudioProcessorEditor::adsrAttackChanged(ADSRComponent *adsr)
{
    getProcessor()->setParameterNotifyingHost(SimpleSynthAudioProcessor::env1AParam,
                                         ParamValue<float>::inverseLinear(adsr->getAttack(),
                                                                          5, 15000));
    getProcessor()->needsUIUpdate = false;
}

void SimpleSynthAudioProcessorEditor::adsrDecayChanged(ADSRComponent *adsr)
{
    getProcessor()->setParameterNotifyingHost(SimpleSynthAudioProcessor::env1DParam,
                                              ParamValue<float>::inverseLinear(adsr->getDecay(),
                                                                               5, 15000));
    getProcessor()->needsUIUpdate = false;
}

void SimpleSynthAudioProcessorEditor::adsrSustainChanged(ADSRComponent *adsr)
{
    getProcessor()->setParameterNotifyingHost(SimpleSynthAudioProcessor::env1SParam,
                                              (float) adsr->getSustain());

    getProcessor()->needsUIUpdate = false;
}

void SimpleSynthAudioProcessorEditor::adsrReleaseChanged(ADSRComponent *adsr)
{
    getProcessor()->setParameterNotifyingHost(SimpleSynthAudioProcessor::env1RParam,
                                              ParamValue<float>::inverseLinear(adsr->getRelease(),
                                                                               5, 15000));
    getProcessor()->needsUIUpdate = false;
}
*/

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SimpleSynthAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer, public OscComponent::Listener, public ADSRComponent::Listener"
                 constructorParams="SimpleSynthAudioProcessor *processor" variableInitialisers="AudioProcessorEditor(processor), Timer()"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="" id="392670d82374eb70" memberName="midiKeyboardComponent"
                    virtualName="" explicitFocusOrder="0" pos="0 0Rr 100% 80" class="MidiKeyboardComponent"
                    params="processor-&gt;keyboardState, MidiKeyboardComponent::horizontalKeyboard"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
