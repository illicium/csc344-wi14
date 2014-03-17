#ifndef VEXCL_BACKEND_CUDA_HPP
#define VEXCL_BACKEND_CUDA_HPP

/*
The MIT License

Copyright (c) 2012-2013 Denis Demidov <ddemidov@ksu.ru>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/**
 * \file   vexcl/backend/cuda.hpp
 * \author Denis Demidov <ddemidov@ksu.ru>
 * \brief  CUDA backend for compute kernel generation/compilation/launching.
 */

#ifndef VEXCL_BACKEND_CUDA
#  define VEXCL_BACKEND_CUDA
#endif

#include <cuda.h>

#include <vexcl/backend/cuda/error.hpp>
#include <vexcl/backend/cuda/context.hpp>
#include <vexcl/backend/cuda/filter.hpp>
#include <vexcl/backend/cuda/device_vector.hpp>
#include <vexcl/backend/cuda/source.hpp>
#include <vexcl/backend/cuda/compiler.hpp>
#include <vexcl/backend/cuda/kernel.hpp>

#endif
