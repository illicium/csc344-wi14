#include "Parameter.h"

// special case for int parameters; use better float->int conversion logic
template <>
float Parameter<int>::getFloatValueLinear() const
{
    return Rescale<float>::inverseIntStep(getValue(), getMin(), getMax());
}

// special case for int parameters; use better float->int conversion logic
template <>
void Parameter<int>::setFloatValueLinear(float newValue)
{
    setValue(static_cast<int>(Rescale<float>::intStep(newValue, getMin(), getMax())));
}