#ifndef CHEBYSHEVFILTER_H_INCLUDED
#define CHEBYSHEVFILTER_H_INCLUDED

#include <complex>
#include <memory>
#include <vector>
using namespace std;

#include "../JuceLibraryCode/JuceHeader.h"

class ChebyshevFilter
{
public:
    ChebyshevFilter();
    
    /**
     * Set filter angle, 0 to pi, e.g.
     * theta = (cutoff / sampleRate) * pi
     */
    void setTheta(double newValue);
    
    /**
     * Set filter ripple, in dB
     */
    void setRipple(double newValue);

    unsigned int getOrder() const { return order; }
    double getTheta() const { return theta; }
    double getRipple() const { return ripple; }
    double getDCGain() const { return dcGain; }
    
    shared_ptr<vector<complex<double>>> getSPoles() const { return sPoles; }
    shared_ptr<vector<complex<double>>> getZPoles() const { return zPoles; }
    shared_ptr<vector<double>> getCoefficientsA() const { return coefficientsA; }
    shared_ptr<vector<double>> getCoefficientsB() const { return coefficientsB; }
    
private:
    /**
     * Calculate the position of filter poles in the s-plane
     */
    void recalculateSPoles();

    /**
     * Calculate the position of filter poles in the z-plane, prescaling by theta
     */
    void recalculateZPoles();

    /**
     * Calculate filter coefficients for current ripple/theta
     */
    void recalculateCoefficients();

    /**
     * Calculate filter gain (only DC gain for now) for current coefficients
     */
    void recalculateGain();
    
    unsigned int order;
    
    double theta;
    double ripple;
    
    double epsilon;
    double v;
    
    double dcGain;
    
    shared_ptr<vector<complex<double>>> sPoles;
    shared_ptr<vector<complex<double>>> zPoles;
    shared_ptr<vector<double>> coefficientsA;
    shared_ptr<vector<double>> coefficientsB;
};



#endif  // CHEBYSHEVFILTER_H_INCLUDED
