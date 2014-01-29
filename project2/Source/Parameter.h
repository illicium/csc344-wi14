#ifndef PARAMETER_H
#define PARAMETER_H

#include <memory>
#include <map>
using namespace std;

#include "../JuceLibraryCode/JuceHeader.h"

#include "Util.h"

/**
 * A parameter that can be edited in some way by the user, especially through
 * the standard 0-1 float plugin parameter interface.
 */
class ParameterBase {
public:
    ParameterBase(String name) : name(name) {}
    virtual ~ParameterBase() {}

    const String& getName() const { return name; }

    virtual const String getValueText() const =0;

    /**
     * Return the value of this parameter as a float in the range 0.0f-1.0f,
     * using a linear mapping
     */
    virtual float getFloatValueLinear() const =0;
    
    /**
     * Set the value of this parameter from a float in the range 0.0f-1.0f,
     * using a linear mapping
     */
    virtual void setFloatValueLinear(float newValue) =0;
    
    
    class JUCE_API Listener
    {
    public:
        virtual ~Listener() {}
        
        virtual void parameterValueChanged(ParameterBase*) = 0;
    };
    
    void addListener(Listener* newListener) { listeners.add(newListener); }
    void removeListener(Listener* listener) { listeners.remove(listener); }

protected:
    String name;
    
    ListenerList<Listener> listeners;
};

// TODO: make this work with enum types
template <class T>
class Parameter : public ParameterBase
{
public:
    Parameter(String name, T value, T min, T max) : ParameterBase(name),
                                                           value(value),
                                                           min(min),
                                                           max(max) {}
    
    T getValue() const { return value; }
    T getValueLinear() const
    {
        return Rescale<T>::inverseLinear(getValue(), getMin(), getMax());
    }
    
    void setValue(T newValue)
    {
        value = newValue;
        listeners.call(&ParameterBase::Listener::parameterValueChanged, dynamic_cast<ParameterBase*>(this));
    }
    void setValueLinear(T newValue)
    {
        setValue(Rescale<T>::linear(newValue, getMin(), getMax()));
    }

    
    float getFloatValueLinear() const
    {
        return Rescale<float>::inverseLinear(getValue(), getMin(), getMax());
    }
    
    void setFloatValueLinear(float newValue)
    {
        setValue(static_cast<T>(Rescale<float>::linear(newValue, getMin(), getMax())));
    }

    
    const String getValueText() const { return String(getValue()); }
    
    T getMin() const { return min; }
    T getMax() const { return max; }

private:
    T value;
    T min, max;
};


/**
 * Base class that provides a map (String to ParameterBase) of parameters.
 * Parameterized objects can share parameters
 */
typedef map<String, shared_ptr<ParameterBase>> Parameters;

class Parameterized
{
public:
    Parameterized()
        : parameters(make_shared<Parameters>()) {}
    Parameterized(initializer_list<pair<const String, shared_ptr<ParameterBase>>> ilist)
        : parameters(make_shared<Parameters>(ilist)) {}
    Parameterized(shared_ptr<Parameters> parameters)
        : parameters(move(parameters)) {}
    virtual ~Parameterized() {}
    
    shared_ptr<ParameterBase> getParameter(const String& id) const
    {
        auto iter = parameters->find(id);
        if (iter != parameters->end()) {
            return iter->second;
        } else {
            return nullptr;
        }
    }

    template <class T>
    shared_ptr<Parameter<T>> getParameter(const String& id) const
    {
        return static_pointer_cast<Parameter<T>>(getParameter(id));
    }
    
    shared_ptr<Parameters> getParameters() const { return parameters; }
    
    void setParameters(shared_ptr<Parameters> newValue)
    {
        parameters = newValue;
    }
    
    /**
     * Copy parameters (by reference) from another Parameterized,
     * namespacing new keys under the prefix
     */
    void inheritParameters(const Parameterized& parameterized, String idPrefix)
    {
        inheritParameters(*parameterized.getParameters(), idPrefix);
    }
    
    /**
     * Copy parameters (by reference), namespacing new keys under the prefix
     */
    void inheritParameters(const Parameters& params, String idPrefix)
    {
        for (auto &param : params) {
            (*parameters)[idPrefix + '_' + param.first] = param.second;
        }
    }
    
protected:
    shared_ptr<Parameters> parameters;
    
};


/*
class ParameterGroup : public ParameterBase,
                       public Parameterized
{
    ParameterGroup(Parameters parameters,
                   String name)
        : Parameterized(parameters),
          name(name) {}
    
    const String& getName() const { return name; }
    
private:
    String name;
};
*/



#endif
