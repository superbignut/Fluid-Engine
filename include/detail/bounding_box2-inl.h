#ifndef INCLUDE_BIG_BOUNDING_BOX2_INL_H_
#define INCLUDE_BIG_BOUNDING_BOX2_INL_H_

namespace big
{
    template <typename T>
    BoundingBox<T, 2>::BoundingBox()
    {
        reset();
    }
    template <typename T>
    BoundingBox<T, 2>::BoundingBox(const Vector<T, 2> &point1, const Vector<T, 2> &point2)
    {
        lowerCorner.x = std::min(point1.x, point2.x);
        lowerCorner.y = std::min(point1.y, point2.y);

        upperCorner.x = std::max(point1.x, point2.x);
        upperCorner.y = std::max(point1.y, point2.y);
    }
    template <typename T>
    BoundingBox<T, 2>::BoundingBox(const BoundingBox &other)
        : lowerCorner(other.lowerCorner), upperCorner(other.upperCorner)
    {
    }

    template <typename T>
    T BoundingBox<T, 2>::width() const
    {
        return upperCorner.x - lowerCorner.x;
    }
    template <typename T>
    T BoundingBox<T, 2>::height() const
    {
        return upperCorner.y - lowerCorner.y;
    }

    template <typename T>
    T BoundingBox<T, 2>::length(std::size_t axis) const
    {
        return upperCorner[axis] - lowerCorner[axis];
    }
    template <typename T>
    bool BoundingBox<T, 2>::overlaps(const BoundingBox &other) const
    {
        if (upperCorner.x < other.lowerCorner.x || other.upperCorner.x < lowerCorner.x)
        {
            return false;
        }
        if (upperCorner.y < other.lowerCorner.y || other.upperCorner.y < lowerCorner.y)
        {
            return false;
        }
        return true;
    }

    template <typename T>
    bool BoundingBox<T, 2>::contains(const Vector<T, 2> &point) const
    {
        if (point.x > upperCorner.x || point.x < lowerCorner.x)
        {
            return false;
        }
        if (point.y > upperCorner.y || point.y < lowerCorner.y)
        {
            return false;
        }
        return true;
    }

    template <typename T>
    bool BoundingBox<T, 2>::intersects(const Ray<T, 2> &ray) const
    {
        T max_1_3 = 0;
        T min_2_4 = std::numeric_limits<T>::max();

        const Vector<T, 2> &rayInvDirection = ray.direction.rdiv(1);

        for (std::size_t i = 0; i < 2; ++i)
        {
            T t_small = (lowerCorner[i] - ray.origin[i]) * rayInvDirection[i];
            T t_big = (upperCorner[i] - ray.origin[i]) * rayInvDirection[i];

            if (t_small > t_big)
            {
                std::swap(t_small, t_big); // ensure t_small < t_big
            }
            max_1_3 = std::max(max_1_3, t_small);
            min_2_4 = std::min(min_2_4, t_big);
            if (max_1_3 > min_2_4)
            {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    BoundingBoxRayIntersection2<T> BoundingBox<T, 2>::closestIntersection(const Ray<T, 2> &ray) const
    {
        BoundingBoxRayIntersection2<T> intersection;
        T max_1_3 = 0;
        T min_2_4 = std::numeric_limits<T>::max();

        const Vector<T, 2> &rayInvDirection = ray.direction.rdiv(1);

        for (std::size_t i = 0; i < 2; ++i)
        {
            T t_small = (lowerCorner[i] - ray.origin[i]) * rayInvDirection[i];
            T t_big = (upperCorner[i] - ray.origin[i]) * rayInvDirection[i];

            if (t_small > t_big)
            {
                std::swap(t_small, t_big);
            }
            max_1_3 = std::max(max_1_3, t_small);
            min_2_4 = std::min(min_2_4, t_big);
            if (max_1_3 > min_2_4)
            {
                intersection.isIntersection = false;
                return intersection;
            }
        }

        if (contains(ray.origin))
        {
            intersection.tNear = min_2_4;                      // core of algorithm
            intersection.tFar = std::numeric_limits<T>::max(); // means no tFar
        }
        else
        {
            intersection.tNear = max_1_3; // core of algorithm
            intersection.tFar = min_2_4;  // core of algorithm
        }

        return intersection;
    }
    template <typename T>
    Vector<T, 2> BoundingBox<T, 2>::midPoint() const
    {
        return (lowerCorner + upperCorner) / static_cast<T>(2);
    }

    template <typename T>
    T BoundingBox<T, 2>::diagonalLength() const
    {
        return (upperCorner - lowerCorner).length();
    }

    //!
    template <typename T>
    T BoundingBox<T, 2>::diagonalLengthSquared() const
    {
        return (upperCorner - lowerCorner).lengthSquared();
    }

    template <typename T>
    void BoundingBox<T, 2>::reset()
    {
        lowerCorner.x = std::numeric_limits<T>::max();
        lowerCorner.y = std::numeric_limits<T>::max();
        upperCorner.x = -std::numeric_limits<T>::max();
        upperCorner.y = -std::numeric_limits<T>::max();
    }

    template <typename T>
    void BoundingBox<T, 2>::merge(const Vector<T, 2> &point)
    {
        lowerCorner.x = std::min(lowerCorner.x, point.x);
        lowerCorner.y = std::min(lowerCorner.y, point.y);

        upperCorner.x = std::max(upperCorner.x, point.x);
        upperCorner.y = std::max(upperCorner.y, point.y);
    }

    template <typename T>
    void BoundingBox<T, 2>::merge(const BoundingBox &other)
    {
        lowerCorner.x = std::min(lowerCorner.x, other.lowerCorner.x);
        lowerCorner.y = std::min(lowerCorner.y, other.lowerCorner.y);

        upperCorner.x = std::max(upperCorner.x, other.upperCorner.x);
        upperCorner.y = std::max(upperCorner.y, other.upperCorner.y);
    }

    template <typename T>
    void BoundingBox<T, 2>::expand(T delta)
    {
        lowerCorner -= delta;
        upperCorner += delta;
    }
    template <typename T>
    Vector<T, 2> BoundingBox<T, 2>::corner(std::size_t idx) const
    {
        static const T h = static_cast<T>(1) / 2;
        static const Vector<T, 2> offset[4] = {
            {-h, -h}, {h, -h}, {-h, h}, {h, h}};

        return Vector<T, 2>(width(), height()) * offset[idx] + midPoint();
    }
    template <typename T>
    Vector<T, 2> BoundingBox<T, 2>::clamp(const Vector<T, 2> &pt) const
    {
        return ::big::clamp(pt, lowerCorner, upperCorner);
    }
    template <typename T>
    bool BoundingBox<T, 2>::isEmpty() const
    {
        return (lowerCorner.x >= upperCorner.x || lowerCorner.y >= upperCorner.y);
    }
}
#endif