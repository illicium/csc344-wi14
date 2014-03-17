#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include <vector>
#include <memory>

#include <vexcl/vexcl.hpp>

#include "../JuceLibraryCode/JuceHeader.h"

#include "FFTConvolver.h"

#include "parameter/ParameterizedAudioProcessor.h"

#include "PluginEditor.h"

class ConvolutionAudioProcessor  : public ParameterizedAudioProcessor
{
    friend class ConvolutionAudioProcessorEditor;
public:
    ConvolutionAudioProcessor();
    ~ConvolutionAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    void loadIrFile(const File &file);
    bool isIrLoaded() const;
    
    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const
    {
        return JucePlugin_Name;
    }
    
    const String getInputChannelName (int channelIndex) const
    {
        return String (channelIndex + 1);
    }
    
    const String getOutputChannelName (int channelIndex) const
    {
        return String (channelIndex + 1);
    }
    
    bool isInputChannelStereoPair (int index) const
    {
        return true;
    }
    
    bool isOutputChannelStereoPair (int index) const
    {
        return true;
    }
    
    bool acceptsMidi() const
    {
#if JucePlugin_WantsMidiInput
        return true;
#else
        return false;
#endif
    }
    
    bool producesMidi() const
    {
#if JucePlugin_ProducesMidiOutput
        return true;
#else
        return false;
#endif
    }
    
    bool silenceInProducesSilenceOut() const
    {
        return false;
    }
    
    double getTailLengthSeconds() const
    {
        return 0.0;
    }
    
    int getNumPrograms()
    {
        return 0;
    }
    
    int getCurrentProgram()
    {
        return 0;
    }
    
    void setCurrentProgram (int index)
    {
    }
    
    const String getProgramName (int index)
    {
        return String::empty;
    }
    
    void changeProgramName (int index, const String& newName)
    {
    }
    
private:
    void readIrFile(const File &file);
    
    bool bypass;
    
    int samplesPerBlock;
    bool irLoaded;
    
    AudioSampleBuffer outBuffer;
    AudioSampleBuffer irBuffer;
    
    std::vector<std::shared_ptr<fftconvolver::FFTConvolver>> convolvers;
    
    double processTimeAvg;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolutionAudioProcessor)
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
