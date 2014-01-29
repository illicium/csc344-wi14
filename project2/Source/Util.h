#ifndef UTIL_H
#define UTIL_H

#include "../JuceLibraryCode/JuceHeader.h"

// http://www.juce.com/comment/286103#comment-286103
template <class T>
class Rescale
{
public:
    static T warp(T value, T min, T max, T mid)
    {
        T sf = warpCoefficients(min, max, mid);
        T y = exp(log(value) / sf);
        
        return min + (max - min) * y;
    }
    
    static T inverseWarp(T value, T min, T max, T mid)
    {
        T sf = warpCoefficients(min, max, mid);
        
        T n = (value - min) / (max - min);
        
        return pow(n, sf);
    }
    
    static T warpCoefficients(T min, T max, T mid)
    {
        T skewFactor = log(0.5) / log((mid - min) / (max - min));
        
        return skewFactor;
    }
    
    /**
     * Given a value in the range 0-1, return the value linearly rescaled
     * to the range min-max
     */
    static T linear(T value, T min, T max)
    {
        return min + (max - min) * value;
    }

    /**
     * Given a value in the range min-max, return the value linearly rescaled
     * to the range 0-1
     */
    static T inverseLinear(T value, T min, T max)
    {
        return (value - min) / (max - min);
    }

    /**
     * Given a value in the range 0-1, return the value linearly rescaled
     * to the range of integers min-max
     */
    static int intStep(T value, int min, int max)
    {
        return min + (int)((T)(max - min) * value + 0.5);
    }

    /**
     * Given a value in the range of integers min-max, return the value linearly
     * rescaled to the range 0-1
     */
    static T inverseIntStep(int value, int min, int max)
    {
        return (T)(value - min) / (T)(max - min);
    }
    
    static bool boolStep(T value)
    {
        return value >= 0.5;
    }
    
    static T inverseBoolStep(bool value)
    {
        return value ? 1.0 : 0.0;
    }
    
};


#endif
