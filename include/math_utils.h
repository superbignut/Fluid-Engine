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

    template <typename T>
    T minn(const T *x, std::size_t n);

    template <typename T>
    T maxn(const T *x, std::size_t n);

    template <typename T>
    T absminn(const T *x, std::size_t n);

    template <typename T>
    T absmaxn(const T *x, std::size_t n);

    template <typename T>
    T square(T x, T y);
}

#include "detail/math_utils-inl.h"
#endif