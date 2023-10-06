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
    template <typename T>
    inline T cubic(T x)
    {
        return x * x * x;
    }

    template <typename T>
    inline T square(T x)
    {
        return x * x;
    }

    template <typename T>
    T minn(const T *x, std::size_t n)
    {
        T ret = *x;
        for (std::size_t i = 0; i < n; ++i)
        {
            ret = std::min(x[i], ret);
        }
        return ret;
    }

    template <typename T>
    T maxn(const T *x, std::size_t n)
    {
        T ret = *x;
        for (std::size_t i = 0; i < n; ++i)
        {
            ret = std::max(x[i], ret);
        }
        return ret;
    }

    template <typename T>
    T absminn(const T *x, std::size_t n)
    {
        T ret = *x;
        for (std::size_t i = 0; i < n; ++i)
        {
            ret = absmin(x[i], ret);
        }
        return ret;
    }

    template <typename T>
    T absmaxn(const T *x, std::size_t n)
    {
        T ret = *x;
        for (std::size_t i = 0; i < n; ++i)
        {
            ret = absmax(x[i], ret);
        }
        return ret;
    }

}

#endif