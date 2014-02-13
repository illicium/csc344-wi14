#ifndef PARAMETER_H
#define PARAMETER_H

#include <memory>
#include <map>
using namespace std;

#include "JuceHeader.h"

#include "Rescale.h"

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

/**
 * A linear, ranged numeric parameter
 */
template <class T>
class Parameter : public ParameterBase
{
public:
    Parameter(String name, T value, T min, T max) : ParameterBase(name),
                                                           value(value),
                                                           min(min),
                                                           max(max) {}

    /**
     * Return the value of this parameter.
     */
    T getValue() const { return value; }
    /**
     * Return the value of this parameter linearly recaled to the range 0-1
     */
    T getValueLinear() const
    {
        return Rescale<T>::inverseLinear(getValue(), getMin(), getMax());
    }

    /**
     * Set the value of this parameter.
     */
    void setValue(T newValue)
    {
        value = newValue;
        listeners.call(&ParameterBase::Listener::parameterValueChanged, dynamic_cast<ParameterBase*>(this));
    }
    /**
     * Set the value of this parameter from a value in the range 0-1 to the
     * linearly rescaled value in this parameter's range
     */
    void setValueLinear(T newValue)
    {
        setValue(Rescale<T>::linear(newValue, getMin(), getMax()));
    }


    /**
     * Return the value of this parameter as a float in the range 0-1, linearly rescaled
     */
    float getFloatValueLinear() const
    {
        return Rescale<float>::inverseLinear(getValue(), getMin(), getMax());
    }
    /**
     * Set the value of this parameter from a float in the range 0-1 to the
     * linearly rescaled value in this parameter's range
     */
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

/*
 * A parameter that remaps linear values to a warped (logarithmic, exponential) space
 * The additional `mid` parameter specifies the value in the range of this parameter
 * that will be halfway value in the range rescaled back into linear space
 */
template <class T>
class WarpedParameter : public ParameterBase
{
public:
    WarpedParameter(String name, T value, T min, T max, T mid) : ParameterBase(name),
    value(value),
    min(min),
    max(max),
    mid(mid) {}
    
    /**
     * Return the value of this parameter.
     */
    T getValue() const { return value; }
    /**
     * Return the value of this parameter recaled from the warped space/range of
     * this parameter to the linear range 0-1
     */
    T getValueLinear() const
    {
        return Rescale<T>::inverseWarp(getValue(), getMin(), getMax(), getMid());
    }
    
    /**
     * Set the value of this parameter.
     */
    void setValue(T newValue)
    {
        value = newValue;
        listeners.call(&ParameterBase::Listener::parameterValueChanged, dynamic_cast<ParameterBase*>(this));
    }
    /**
     * Set the value of this parameter from a value in the linear range 0-1 to the
     * warped value in this parameter's range
     */
    void setValueLinear(T newValue)
    {
        setValue(Rescale<T>::warp(newValue, getMin(), getMax(), getMid()));
    }
    
    
    /**
     * Return the value of this parameter scaled from the warped space/range of
     * this parameter to a linear float value in the range 0-1
     */
    float getFloatValueLinear() const
    {
        return Rescale<float>::inverseWarp(getValue(), getMin(), getMax(), getMid());
    }
    /**
     * Set the value of this parameter from a float in the linear range 0-1 to the
     * warped value in this parameter's range
     */
    void setFloatValueLinear(float newValue)
    {
        setValue(static_cast<T>(Rescale<float>::warp(newValue, getMin(), getMax(), getMid())));
    }
    
    
    const String getValueText() const { return String(getValue()); }
    
    T getMin() const { return min; }
    T getMax() const { return max; }
    T getMid() const { return mid; }
    
private:
    T value;
    T min, max, mid;
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
