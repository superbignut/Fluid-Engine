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

        for (int i = 0; i < 2; ++i)
        {
            T t_small = (lowerCorner[i] - ray.origin[i]) * rayInvDirection[i];
            T t_big = (upperCorner[i] - ray.origin[i]) * rayInvDirection[i];

            if (t_small < t_big)
            {
                std::swap(t_small, t_big);
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
    void BoundingBox<T, 2>::reset()
    {
        lowerCorner.x = std::numeric_limits<T>::max();
        lowerCorner.y = std::numeric_limits<T>::max();
        upperCorner.x = -std::numeric_limits<T>::max();
        upperCorner.y = -std::numeric_limits<T>::max();
    }
}
#endif