#ifndef INCLUDE_BIG_RAY_H_
#define INCLUDE_BIG_RAY_H_
#include <vector.h>

namespace big
{
    template <typename T, std::size_t N>
    class Ray
    {
        static_assert(N != 2 && N != 3, "N can't be 2 or 3.");

        static_assert(std::is_floating_point<T>::value, "Ray only can be instantiated with floating point types.");
    };

}

#endif