
#ifndef SIMPLECONVOLVE_H_INCLUDED
#define SIMPLECONVOLVE_H_INCLUDED

#include <cstring>

class SimpleConvolve
{
public:
    /**
     * Convolve input with ir and store in output
     * Output buffer size should be inLen + irLen - 1
     */
    template<typename T>
    static void convolve(const T* input, size_t inLen, const T* ir, size_t irLen, T* output)
    {
        if (irLen > inLen)
        {
            SimpleConvolve(ir, irLen, input, inLen, output);
            return;
        }
        
        ::memset(output, 0, (inLen+irLen-1) * sizeof(T));
        
        for (size_t n=0; n<irLen; ++n)
        {
            for (size_t m=0; m<=n; ++m)
            {
                output[n] += ir[m] * input[n-m];
            }
        }
        
        for (size_t n=irLen; n<inLen; ++n)
        {
            for (size_t m=0; m<irLen; ++m)
            {
                output[n] += ir[m] * input[n-m];
            }
        }
        
        for (size_t n=inLen; n<inLen+irLen-1; ++n)
        {
            for (size_t m=n-inLen+1; m<irLen; ++m)
            {
                output[n] += ir[m] * input[n-m];
            }
        }
    }

};



#endif  // SIMPLECONVOLVE_H_INCLUDED
