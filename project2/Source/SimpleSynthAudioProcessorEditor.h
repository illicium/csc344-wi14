#ifndef SIMPLESYNTHPLUGINEDITOR_H
#define SIMPLESYNTHPLUGINEDITOR_H

#include "../JuceLibraryCode/JuceHeader.h"

#include "SimpleSynthAudioProcessor.h"

class SimpleSynthAudioProcessorEditor : public AudioProcessorEditor
{
public:
    SimpleSynthAudioProcessorEditor(SimpleSynthAudioProcessor* processor);
    ~SimpleSynthAudioProcessorEditor();

    void paint(Graphics&) override;
    void resized() override;
    
private:
    MidiKeyboardComponent midiKeyboard;
    
    ScopedPointer<ResizableCornerComponent> resizer;
    ComponentBoundsConstrainer resizeLimits;
    
    SimpleSynthAudioProcessor* getProcessor() const
    {
        return static_cast<SimpleSynthAudioProcessor*>(getAudioProcessor());
    }
};


#endif