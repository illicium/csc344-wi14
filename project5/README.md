# Convolution

![Convolution screenshot](http://illicium.github.io/csc344-wi14/convolution.png)

Convolves the input audio with a user-provided impulse response, using a parallel OpenCL FFT implementation.

* Brandon Bevans
* Yegor Pomortsev


## Building

Dependencies: Boost. To build the CPU-only version, remove the `AUDIOFFT_VEXCL` compile-time define (use Introjucer), and optionally use `AUDIOFFT_APPLE_ACCELERATE=1` (OS X only), or `AUDIOFFT_FFTW=1` (needs fftw linked)

## Usage

1. Open a plugin host (e.g. JUCE audio plugin host). Set OpenCL device settings using an environment variable:
	* `OCL_TYPE=CPU OCL_MAX_DEVICES=1` for CPU
	* `OCL_TYPE=GPU OCL_MAX_DEVICES=1` for GPU
	* Or, [choose a specific device](http://ddemidov.github.io/vexcl/namespacevex_1_1Filter.html) using the the other environment variables supported by VexCL
2. Add the Convolution audio effect
3. Open the Convolution plugin UI and choose an impulse response
4. Run some audio through it