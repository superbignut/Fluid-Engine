#ifndef INCLUDE_BIG_RAY3_INL_H_
#define INCLUDE_BIG_RAY3_INL_H_
namespace big
{
    template <typename T>
    Ray<T, 3>::Ray()
        : origin({0, 0, 0}), direction({1, 0, 0})
    {
    }

    template <typename T>
    Ray<T, 3>::Ray(const Vector<T, 3> &newOrigin, const Vector<T, 3> &newDirection)
        : origin(newOrigin), direction(newDirection.normalized())
    {
    }

    template <typename T>
    Ray<T, 3>::Ray(const Ray &other)
        : origin(other.origin), direction(other.direction)
    {
    }

    template <typename T>
    Vector<T, 3> Ray<T, 3>::pointAt(T t) const
    {
        return origin + t * direction;
    }

}

#endif