#include "SimpleSynthAudioProcessor.h"
#include "SimpleSynthAudioProcessorEditor.h"


SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor* processor)
    : AudioProcessorEditor (processor),
    midiKeyboard (processor->keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(midiKeyboard);
    
    addAndMakeVisible(resizer = new ResizableCornerComponent(this, &resizeLimits));
    resizeLimits.setSizeLimits(150, 150, 800, 300);
    
    setSize(processor->lastUIWidth, processor->lastUIHeight);
}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}


void SimpleSynthAudioProcessorEditor::paint(Graphics& g)
{
    g.fillAll(Colours::red);
}

void SimpleSynthAudioProcessorEditor::resized()
{
    const int keyboardHeight = 70;
    midiKeyboard.setBounds (4,
                            getHeight() - keyboardHeight - 4,
                            getWidth() - 8,
                            keyboardHeight);
    
    resizer->setBounds (getWidth() - 16,
                        getHeight() - 16,
                        16,
                        16);
    
    getProcessor()->lastUIWidth = getWidth();
    getProcessor()->lastUIHeight = getHeight();
}

