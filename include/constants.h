#ifndef CONSTANT_H_
#define CONSTANT_H_

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
}

#endif