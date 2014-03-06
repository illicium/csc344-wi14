#ifndef TIMESIGNATURE_H_INCLUDED
#define TIMESIGNATURE_H_INCLUDED

#include <stdexcept>

/**
 * Represents a time/meter signature as a fraction: numerator (beats per bar)
 * and denominator (note value that constitutes a beat)
 */
class TimeSignature
{
public:
    TimeSignature(int numerator, int denominator)
        : numerator(numerator), denominator(denominator)
    {
        if (numerator < 1) {
            throw std::invalid_argument("numerator must be positive");
        }
        if (denominator < 2) {
            throw std::invalid_argument("denominator must be a positive power of two");
        }
        if ((denominator & (denominator - 1)) != 0) {
            throw std::invalid_argument("irrational meter (denominator not a power of two)");
        }
    }
    
    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }
    
    static const TimeSignature COMMON_TIME;
    
private:
    int numerator;
    int denominator;
};

#endif  // TIMESIGNATURE_H_INCLUDED
