#ifndef INCLUDE_BIG_RAY2_INL_H_
#define INCLUDE_BIG_RAY2_INL_H_
namespace big
{
    template <typename T>
    Ray<T, 2>::Ray()
        : origin({0, 0}), direction({1, 0})
    {
    }

    template <typename T>
    Ray<T, 2>::Ray(const Vector<T, 2> &newOrigin, const Vector<T, 2> &newDirection)
        : origin(newOrigin), direction(newDirection.normalized())
    {
    }

    template <typename T>
    Ray<T, 2>::Ray(const Ray &other)
        : origin(other.origin), direction(other.direction)
    {
    }

    template <typename T>
    Vector<T, 2> Ray<T, 2>::pointAt(T t) const
    {
        return origin + t * direction;
    }

}

#endif