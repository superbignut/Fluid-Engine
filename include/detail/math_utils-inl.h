#ifndef INCLUDE_BIG_MATH_UTILS_INL_H_
#define INCLUDE_BIG_MATH_UTILS_INL_H_
namespace big
{
    template <typename T>
    inline T absmin(T x, T y)
    {
        return x * x <= y * y ? x : y;
    }
    template <typename T>
    inline T absmax(T x, T y)
    {
        return x * x >= y * y ? x : y;
    }

    template <typename T>
    inline T absmin(T x, T y, T z)
    {
        return (x * x <= y * y) ? (x * x <= z * z ? x : z) : (y * y <= z * z ? y : z);
    }
    template <typename T>
    inline T absmax(T x, T y, T z)
    {
        return (x * x >= y * y) ? (x * x >= z * z ? x : z) : (y * y >= z * z ? y : z);
    }
    
}

#endif