#ifndef GENERATOR_H
#define GENERATOR_H

/**
 * Base class for classes that generate some value over time.
 */
template <class T>
class Generator
{
public:
    Generator(double sampleRate) : sampleRate(sampleRate) {}
    Generator(double sampleRate, T value) : sampleRate(sampleRate),
                                            value(value) {}
    virtual ~Generator() {}
    
    virtual T getValue() const { return value; }
    
    /**
     * Generate a value, save it internally, and return it
     */
    virtual T generateValue() =0;
    
    /**
     * Advance the internal state of the generator by one sample, generate
     * a new value, and return it
     */
    virtual T tick() =0;
    virtual void reset() =0;
    
protected:
    double sampleRate;
    
    T value;
};


#endif
