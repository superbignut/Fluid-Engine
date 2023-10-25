#ifndef INCLUDE_BIG_RAY3_H_
#define INCLUDE_BIG_RAY3_H_
#include "ray.h"
#include "vector3.h"

namespace big
{

    template <typename T>
    class Ray<T, 3> final
    {
    public:
        static_assert(std::is_floating_point<T>::value, "Ray only can be instantiated with floating point types.");

        Vector<T, 3> origin;

        Vector<T, 3> direction;

        //! empty ray point(1,0,0) from (0,0,0)
        Ray();

        Ray(const Vector<T, 3>& newOrigin, const Vector<T, 3>& newDirection);

        Ray(const Ray& other);

        //！ return origin + t * direction.
        Vector<T, 3> pointAt(T t) const;

    };

    template <typename T>
    using Ray3 = Ray<T, 3>;

    typedef Ray<float, 3> Ray3F;
    typedef Ray<double, 3> Ray3D;

}

#include "detail/ray3-inl.h"
#endif