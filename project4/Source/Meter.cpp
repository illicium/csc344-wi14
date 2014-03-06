#include "Meter.h"

Meter::Meter(int bars, int beats, int sixteenths, double remainder, TimeSignature timeSignature)
    : bars(bars), beats(beats), sixteenths(sixteenths), remainder(remainder), timeSignature(timeSignature)
{
}

Meter Meter::fromSeconds(double seconds, double bpm, TimeSignature timeSignature)
{
    const double totalBeats = seconds / 60.0 * bpm;
    const double beatsPerBar = (double) timeSignature.getNumerator();
    const double noteValue = (double) timeSignature.getDenominator();

    const int wholeBars = totalBeats / beatsPerBar;
    const int wholeBeats = totalBeats - (wholeBars * beatsPerBar);
    const int wholeSixteenths = (totalBeats - (wholeBars * beatsPerBar) - wholeBeats) *
                                noteValue;
    const double remainder = (totalBeats - (wholeBars * beatsPerBar) - wholeBeats -
                                (wholeSixteenths / noteValue)) *
                              noteValue;
    
    return Meter(wholeBars, wholeBeats, wholeSixteenths, remainder);
}


double Meter::toSeconds(double bpm) const
{
    const double secondsPerBeat = 1.0 / bpm * 60.0;
    const double beatsPerBar = (double) timeSignature.getNumerator();
    const double noteValue = (double) timeSignature.getDenominator();
    
    const double totalBeats = (bars * beatsPerBar) +
                              beats +
                              ((sixteenths + remainder) / noteValue);
    
    return totalBeats * secondsPerBeat;
}


std::ostream& operator<<(std::ostream& os, const Meter &m)
{
    os << m.bars << '|' << m.beats << '|' << m.sixteenths << '|' << m.remainder;
    return os;
}