#ifndef INCLUDE_BIG_MATH_UTILS_H_
#define INCLUDE_BIG_MATH_UTILS_H_
namespace big
{
    template <typename T>
    T absmin(T x, T y);

    template <typename T>
    T absmax(T x, T y);

    template <typename T>
    T absmin(T x, T y, T z);

    template <typename T>
    T absmax(T x, T y, T z);

    template <typename T>
    T cubic(T x);

    template <typename T>
    T square(T x);
}

#include "detail/math_utils-inl.h"
#endif