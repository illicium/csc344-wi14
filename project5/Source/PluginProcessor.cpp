#include <iostream>
#include <cstring>

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "FFTConvolver.h"


ConvolutionAudioProcessor::ConvolutionAudioProcessor()
    : ParameterizedAudioProcessor({
        {"input_gain", make_shared<Parameter<double>>("Input Gain (dB)", -6.0, -48.0, 3.0)},
    }),
    bypass(false),
    samplesPerBlock(0),
    irLoaded(false),
    outBuffer(2, 0),
    irBuffer(2, 0),
    convolvers(),
    processTimeAvg(0)
{
}

ConvolutionAudioProcessor::~ConvolutionAudioProcessor()
{
}


//==============================================================================
void ConvolutionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock_)
{
    samplesPerBlock = samplesPerBlock_;
    
    outBuffer.setSize(getNumInputChannels(), samplesPerBlock);
}

void ConvolutionAudioProcessor::releaseResources()
{
}

void ConvolutionAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int64 startTicks = Time::getHighResolutionTicks();
    
    if (!bypass && isIrLoaded()) {
        if (outBuffer.getNumSamples() < buffer.getNumSamples()) {
            // make sure the output buffer is big enough (samplesPerBlock might
            // not actually be the real buffer size)
            outBuffer.setSize(getNumInputChannels(), samplesPerBlock);
        }

        for (int channel = 0; channel < getNumInputChannels(); channel++) {
            // apply input gain (the output will generally be louder than desired,
            // so the user can turn down the gain to compensate)
            double input_gain = Parameterized::getParameter<double>("input_gain")->getValue();
            buffer.applyGain(channel, 0, buffer.getNumSamples(), Decibels::decibelsToGain(input_gain));
            
            float *channelData = buffer.getSampleData(channel);
            float *outData = outBuffer.getSampleData(channel);
            int irChannel = jmin(channel, irBuffer.getNumChannels() - 1);
            
            /*
            SimpleConvolve<float>(channelData, buffer.getNumSamples(),
                                  irData, irBuffer.getNumSamples(),
                                  outData);
            */
            
            // apply the convolution to the channel
            convolvers.at(irChannel)->process(channelData, outData, buffer.getNumSamples());
            
            // copy from the convolution output buffer back into the input buffer
            // (`buffer` serves as both input and output)
            buffer.copyFrom(channel, 0,
                            outBuffer, channel, 0,
                            buffer.getNumSamples());
        }
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
    }

    // print a message if we took too long to process this block
    const int64 endTicks = Time::getHighResolutionTicks();
    const int64 processBlockTicks = endTicks - startTicks;
    double processBlockTime = Time::highResolutionTicksToSeconds(processBlockTicks);
    const double maxTime = (1.0 / getSampleRate()) * buffer.getNumSamples();
    
    if (processBlockTime > maxTime) {
        std::cerr << "buffer underrun: processBlock took "
                  << processBlockTime << " seconds (" << endTicks - startTicks << " ticks, "
                  << (processBlockTime / maxTime) << "x max time [" << maxTime << "])" << std::endl;
    }
    
    // keep a running average of processing time
    const int n = getSampleRate() / buffer.getNumSamples(); // about a second
    processTimeAvg -= processTimeAvg / n;
    processTimeAvg += processBlockTime / n;
}



void ConvolutionAudioProcessor::readIrFile(const File &file)
{
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    ScopedPointer<AudioFormatReader> audioFormatReader(formatManager.createReaderFor(file));
    
    if (audioFormatReader->sampleRate != getSampleRate()) {
        std::cerr << "error: IR samplerate != input samplerate" << std::endl;
        return;
    }
    
    irBuffer.setSize(audioFormatReader->numChannels,
                     audioFormatReader->lengthInSamples);

    AudioSourceChannelInfo info(irBuffer);

    AudioFormatReaderSource audioFormatReaderSource(audioFormatReader, false);
    audioFormatReaderSource.getNextAudioBlock(info);
}

void ConvolutionAudioProcessor::loadIrFile(const File &file)
{
    readIrFile(file);

    convolvers.clear();
    for (int channel = 0; channel < irBuffer.getNumChannels(); channel++) {
        float *irData = irBuffer.getSampleData(channel);
        
        std::shared_ptr<fftconvolver::FFTConvolver> convolver =
            std::make_shared<fftconvolver::FFTConvolver>();
        convolver->init(samplesPerBlock, irData, irBuffer.getNumSamples());
        convolvers.push_back(convolver);
    }
    
    std::cout << "Loaded IR file: " << file.getFullPathName() << std::endl;
    
    processTimeAvg = 0;
}

bool ConvolutionAudioProcessor::isIrLoaded() const
{
    return irBuffer.getNumSamples() != 0;
}

//==============================================================================
bool ConvolutionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ConvolutionAudioProcessor::createEditor()
{
    return new ConvolutionAudioProcessorEditor(this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ConvolutionAudioProcessor();
}
