#ifndef INCLUDE_BIG_FUNCTORS_H_
#define INCLUDE_BIG_FUNCTORS_H_
#include <functional>
namespace big
{
    template <typename T, typename U>
    struct TypeCast
    {
        constexpr U operator()(const T &a) const;
    };

    template <typename T>
    struct RMinus
    {
        constexpr T operator()(const T &a, const T &b) const;
    };

    template <typename T>
    struct RDivides
    {
        constexpr T operator()(const T& a, const T& b) const;
    };

}

#include "detail/functors-inl.h"
#endif