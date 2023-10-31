#ifndef CONSTANT_H_
#define CONSTANT_H_
#include <cmath>
namespace big
{

    constexpr std::size_t kZeroSize = 0;

    constexpr ssize_t kZeroSSize = 0;

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

    constexpr double kMaxD = std::numeric_limits<double>::max();

    constexpr float kMaxF = std::numeric_limits<float>::max();

    constexpr float kPiF = 3.1415926535;

    constexpr double kPiD = 3.1415926535;

    template <typename T>
    constexpr T pi()
    {
        return static_cast<T>(kPiD);
    }
    template <>
    constexpr float pi<float>()
    {
        return kPiF;
    }
    template <>
    constexpr double pi<double>()
    {
        return kPiD;
    }

}

#endif