#include "ParameterizedAudioProcessor.h"

ParameterizedAudioProcessor::ParameterizedAudioProcessor()
    : Parameterized(std::make_shared<Parameters>())
{
    initParameterIds();
}

ParameterizedAudioProcessor::ParameterizedAudioProcessor(std::initializer_list<std::pair<const String, std::shared_ptr<ParameterBase>>> ilist)
    : Parameterized(std::make_shared<Parameters>(ilist))
{
    initParameterIds();
}

ParameterizedAudioProcessor::ParameterizedAudioProcessor(std::shared_ptr<Parameters> parameters)
    : Parameterized(std::move(parameters))
{
    initParameterIds();
}

void ParameterizedAudioProcessor::initParameterIds()
{
    for (auto &param : *parameters) {
        parameterIds.push_back(param.first);
    }
}


int ParameterizedAudioProcessor::getNumParameters()
{
    return parameterIds.size();
}

float ParameterizedAudioProcessor::getParameter(int index)
{
    if (index < 0 || index >= parameterIds.size()) {
        return 0.0f;
    }
    
    return (*parameters)[parameterIds[index]]->getFloatValueLinear();
}

void ParameterizedAudioProcessor::setParameter(int index, float newValue)
{
    if (index < 0 || index >= parameterIds.size()) {
        return;
    }
    
    (*parameters)[parameterIds[index]]->setFloatValueLinear(newValue);
}

const String ParameterizedAudioProcessor::getParameterName(int index)
{
    if (index < 0 || index >= parameterIds.size()) {
        return String::empty;
    }
    
    return String(parameterIds[index] +
                  + " (" + (*parameters)[parameterIds[index]]->getName() + ')');
}

const String ParameterizedAudioProcessor::getParameterText(int index)
{
    if (index < 0 && index > parameterIds.size()) {
        return String::empty;
    }
    
    return (*parameters)[parameterIds[index]]->getValueText();
}


void ParameterizedAudioProcessor::getStateInformation(MemoryBlock &destData)
{
    XmlElement xml(JucePlugin_Name "_settings");
    
    for (const String& paramId : parameterIds) {
        xml.setAttribute(paramId, (*parameters)[paramId]->getFloatValueLinear());
    }
    
    copyXmlToBinary(xml, destData);
}

void ParameterizedAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName(JucePlugin_Name "_settings"))
        {
            for (const String& paramId : parameterIds) {
                float prevValue = (*parameters)[paramId]->getFloatValueLinear();
                float newValue = (float) xmlState->getDoubleAttribute(paramId, prevValue);
                (*parameters)[paramId]->setFloatValueLinear(newValue);
            }
        }
    }
}