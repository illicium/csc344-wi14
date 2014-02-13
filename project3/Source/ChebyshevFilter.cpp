#include "ChebyshevFilter.h"

#include <numeric>

ChebyshevFilter::ChebyshevFilter()
    : order(4),
    theta(0.0),
    sPoles(make_shared<vector<complex<double>>>(order)),
    zPoles(make_shared<vector<complex<double>>>(order)),
    coefficientsA(make_shared<vector<double>>()),
    coefficientsB(make_shared<vector<double>>())
{
    assert(order > 0);
    
    coefficientsA->clear();
    coefficientsA->push_back(1); // z (current input sample)
    coefficientsA->push_back(4); // z^-1
    coefficientsA->push_back(6); // z^-2
    coefficientsA->push_back(4); // z^-3
    coefficientsA->push_back(1); // z^-4
    
    setRipple(1.0);
}

void ChebyshevFilter::setTheta(double newValue)
{
    theta = newValue;
    
    recalculateZPoles();
    recalculateCoefficients();
    recalculateGain();
}

void ChebyshevFilter::setRipple(double newValue)
{
    assert(newValue > 0);
    
    ripple = newValue;
    
    epsilon = sqrt(pow(10.0, ripple / 10.0) - 1.0);
    v = asinh(1.0 / epsilon) / (double) order;
    
    recalculateSPoles();
    recalculateZPoles();
    recalculateCoefficients();
    recalculateGain();
}


void ChebyshevFilter::recalculateSPoles()
{
    sPoles->clear();
    
    for (int m = 1; m <= order; m++) {
        double angle = ((2.0 * m - 1) * double_Pi) / (2.0 * order);
        double real = sin(angle) * -sinh(v);
        double imag = cos(angle) * cosh(v);
        sPoles->push_back(complex<double>(real, imag));
    }
}

void ChebyshevFilter::recalculateZPoles()
{
    zPoles->clear();
    
    for (complex<double> sPole : *sPoles) {
        sPole *= theta;
        auto halfSPole = sPole / complex<double>(2);
        auto zPole = (complex<double>(1) + halfSPole) /
                     (complex<double>(1) - halfSPole);
        zPoles->push_back(zPole);
    }
}

void ChebyshevFilter::recalculateCoefficients()
{
    complex<double> A = zPoles->at(0),
                    B = zPoles->at(1),
                    C = zPoles->at(2),
                    D = zPoles->at(3);
    
    /*
     (z - A)(z - B)(z - C)(z - D) / z =
     A B C D z^-4
     - A B C z^-3
     - A B D z^-3
     - A C D z^-3
     - B C D z^-3
     + A B z^-2
     + A C z^-2
     + A D z^-2
     + B C z^-2
     + B D z^-2
     + C D z^-2
     - A z^-1
     - B z^-1
     - C z^-1
     - D z^-1
     + z
     */
    
    auto z1 = -(A + B + C + D);
    auto z2 = (A * B) +
              (A * C) +
              (A * D) +
              (B * C) +
              (B * D) +
              (C * D);
    auto z3 = -((A * B * C) +
                (A * B * D) +
                (A * C * D) +
                (B * C * D));
    auto z4 = (A * B * C * D);
    
    coefficientsB->clear();
    coefficientsB->push_back(1); // z (output value that is being calculated)
    coefficientsB->push_back(z1.real()); // z^-1
    coefficientsB->push_back(z2.real()); // z^-2
    coefficientsB->push_back(z3.real()); // z^-3
    coefficientsB->push_back(z4.real()); // z^-4
}

void ChebyshevFilter::recalculateGain()
{
    auto sum = accumulate(coefficientsB->begin(), coefficientsB->end(), complex<double>(0)).real();
    if (sum > 0) {
        dcGain = 1.0 / sum;
    }
}