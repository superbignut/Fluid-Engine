#ifndef INCLUDE_BIG_RAY2_H_
#define INCLUDE_BIG_RAY2_H_
#include "ray.h"
#include "vector2.h"

namespace big
{

    template <typename T>
    class Ray<T, 2> final
    {
    public:
        static_assert(std::is_floating_point<T>::value, "Ray only can be instantiated with floating point types.");

        Vector<T, 2> origin;

        Vector<T, 2> direction;

        //! empty ray point(1,0) from (0,0)
        Ray();

        Ray(const Vector<T, 2>& newOrigin, const Vector<T, 2>& newDirection);

        Ray(const Ray& other);

        //！ return origin + t * direction.
        Vector<T, 2> pointAt(T t) const;

    };

    template <typename T>
    using Ray2 = Ray<T, 2>;

    typedef Ray<float, 2> Ray2F;
    typedef Ray<double, 2> Ray2D;

}

#include "detail/ray2-inl.h"
#endif