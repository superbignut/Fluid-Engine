#ifndef CONSTANT_H_
#define CONSTANT_H_
#include <cmath>
namespace big
{

    template <typename T>
    constexpr T zero()
    {
        return 0;
    }

    template <>
    constexpr float zero<float>()
    {
        return 0.f;
    }

    template <>
    constexpr double zero<double>()
    {
        return 0.0;
    }


    constexpr std::size_t kMaxSize = std::numeric_limits<std::size_t>::max();
}

#endif