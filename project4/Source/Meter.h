#ifndef METER_H_INCLUDED
#define METER_H_INCLUDED

#include <numeric>
#include <limits>
#include <ostream>

#include <boost/operators.hpp>

#include "TimeSignature.h"

/**
 * Represents time as a number of bars, beats, sixteenths, and remainder (fraction of sixteenth)
 * All values are zero-based (not like in normal people music)
 */
class Meter : boost::addable<Meter>
{
public:
    Meter(int bars = 0, int beats = 0, int sixteenths = 0, double remainder = 0.0,
          TimeSignature signature = TimeSignature::COMMON_TIME);
    
    /**
     * Convert number of seconds to a meter value given the given the beats per minute,
     * and a time signature
     */
    static Meter fromSeconds(double seconds, double bpm, TimeSignature timeSignature);
    
    /**
     * Convert the meter value to a number of seconds, given the beats per minute,
     * using this meter's time signature
     */
    double toSeconds(double bpm) const;

    
    int getBars() const { return bars; }
    int getBeats() const { return beats; }
    int getSixteenths() const { return sixteenths; }
    double getRemainder() const { return remainder; }
    const TimeSignature& getTimeSignature() const { return timeSignature; }

    /**
     * Compare two meters, assuming they have the same time signature
     */
    static int compare(const Meter &m1, const Meter &m2)
    {
        if (m1.bars != m2.bars) {
            return m1.bars - m2.bars;
        } else if (m1.beats != m2.beats) {
            return m1.beats - m2.beats;
        } else if (m1.sixteenths != m2.sixteenths) {
            return m1.sixteenths - m2.sixteenths;
        } else {
            double remainderDiff = m1.remainder - m2.remainder;
            
            if (remainderDiff == 0) {
                return 0;
            } else if (remainderDiff <
                       -std::numeric_limits<double>::epsilon()) {
                return -1;
            } else if (remainderDiff >
                       std::numeric_limits<double>::epsilon()) {
                return 1;
            }
        }
        return 0;
    }
    
    bool operator>(const Meter &rhs) const { return compare(*this, rhs) > 0; }
    bool operator<(const Meter &rhs) const { return compare(*this, rhs) < 0; }
    bool operator>=(const Meter &rhs) const { return compare(*this, rhs) >= 0; }
    bool operator<=(const Meter &rhs) const { return compare(*this, rhs) <= 0; }
    bool operator==(const Meter &rhs) const { return compare(*this, rhs) == 0; }
    bool operator!=(const Meter &rhs) const { return compare(*this, rhs) != 0; }

    friend std::ostream& operator<<(std::ostream& os, const Meter &m);
    
    
    Meter& operator+=(const Meter &rhs)
    {
        remainder += rhs.getRemainder();
        if (remainder >= 1) {
            remainder -= 1;
            sixteenths++;
        }
        
        sixteenths += rhs.getSixteenths();
        if (sixteenths >= timeSignature.getDenominator()) {
            sixteenths -= timeSignature.getDenominator();
            beats++;
        }
        
        beats += rhs.getBeats();
        if (beats > timeSignature.getNumerator()) {
            beats -= timeSignature.getNumerator();
            bars++;
        }
        
        return *this;
    }

private:
    int bars;
    int beats;
    int sixteenths;
    double remainder;
    TimeSignature timeSignature;
};


#endif  // METER_H_INCLUDED
