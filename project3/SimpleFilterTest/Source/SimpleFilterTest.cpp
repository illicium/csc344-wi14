#include "SimpleFilterTest.h"

#include "ChebyshevFilter.h"

#include <iostream>
using namespace std;

int main(int argc, const char * argv[])
{
    ChebyshevFilter filter;
    
    filter.setRipple(0.9691);

    cout << "ripple: " << filter.getRipple() << endl;
    
    double freq = 800.0;
    double sampleRate = 44100.0;
    double theta = (freq / (sampleRate / 2)) * double_Pi;

    cout << "freq: " << freq << endl;
    cout << "sampleRate: " << sampleRate << endl;
    cout << "theta: " << theta << endl;

    filter.setTheta(theta);

    cout << "s-poles:" << endl;
    for (complex<double> pole : *filter.getSPoles()) {
        cout << '\t' << pole << endl;
    }

    cout << "z-poles:" << endl;
    for (complex<double> pole : *filter.getZPoles()) {
        cout << '\t' << pole << endl;
    }

    cout << "coefficients a:" << endl;
    for (double coeff : *filter.getCoefficientsA()) {
        cout << '\t' << coeff << endl;
    }

    cout << "coefficients b:" << endl;
    for (double coeff : *filter.getCoefficientsB()) {
        cout << '\t' << coeff << endl;
    }
    
    cout << "gain: " << filter.getDCGain() << endl;
    
    return 0;
}