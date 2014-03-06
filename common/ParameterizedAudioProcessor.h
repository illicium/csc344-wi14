#ifndef PARAMETERIZEDAUDIOPROCESSOR_H
#define PARAMETERIZEDAUDIOPROCESSOR_H

#include <memory>
#include <vector>
#include <complex>
using namespace std;

#include "JuceHeader.h"

#include "Parameter.h"

class ParameterizedAudioProcessor : public AudioProcessor,
                                    public Parameterized
{
public:
    ParameterizedAudioProcessor();
    virtual ~ParameterizedAudioProcessor() {};
    
    int getNumParameters();
    float getParameter(int index);
    void setParameter(int index, float newValue);
    
    const String getParameterName(int index);
    const String getParameterText(int index);
        
    void getStateInformation(MemoryBlock &destData);
    void setStateInformation(const void* data, int sizeInBytes);
    
protected:
    vector<String> parameterIds;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterizedAudioProcessor)
};


#endif
