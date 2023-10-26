#ifndef INCLUDE_BIG_BOUNDING_BOX_INL_H_
#define INCLUDE_BIG_BOUNDING_BOX_INL_H_
namespace big
{

    template <typename T, std::size_t N>
    BoundingBox<T, N>::BoundingBox()
    {
        reset();
    }
    template <typename T, std::size_t N>
    BoundingBox<T, N>::BoundingBox(const VectorType &point1, const VectorType &point2)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            lowerCorner[i] = std::min(point1[i], point2[i]);
            upperCorner[i] = std::max(point1[i], point2[i]);
        }
    }
    template <typename T, std::size_t N>
    BoundingBox<T, N>::BoundingBox(const BoundingBox &other)
        : lowerCorner(other.lowerCorner), upperCorner(other.upperCorner)
    {
    }

    template <typename T, std::size_t N>
    bool BoundingBox<T, N>::overlaps(const BoundingBox &other) const
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            if (upperCorner[i] < other.lowerCorner[i] || other.upperCorner[i] < lowerCorner[i])
            {
                return false;
            }
        }
        return true;
    }
    template <typename T, std::size_t N>
    bool BoundingBox<T, N>::contains(const VectorType &point) const
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            if (point[i] > upperCorner[i] || point[i] < lowerCorner[i])
            {
                return false;
            }
        }
        return true;
    }

    template <typename T, std::size_t N>
    Vector<T, N> BoundingBox<T, N>::midPoint() const
    {
        Vector<T, N> result;
        for (std::size_t i = 0; i < N; ++i)
        {
            result[i] = (upperCorner[i] + lowerCorner[i]) / 2;
        }
        return result;
    }
    template <typename T, std::size_t N>
    T BoundingBox<T, N>::diagonalLength() const
    {
        T result = 0;
        for (std::size_t i = 0; i < N; ++i)
        {
            result += square(upperCorner[i] - lowerCorner[i]);
        }
        return std::sqrt(result);
    }
    template <typename T, std::size_t N>
    T BoundingBox<T, N>::diagonalLengthSquared() const
    {
        T result = 0;
        for (std::size_t i = 0; i < N; ++i)
        {
            result += square(upperCorner[i] - lowerCorner[i]);
        }
        return result;
    }
    template <typename T, std::size_t N>
    void BoundingBox<T, N>::reset()
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            lowerCorner[i] = std::numeric_limits<T>::max();
            upperCorner[i] = -std::numeric_limits<T>::max();
        }
    }
    template <typename T, std::size_t N>
    void BoundingBox<T, N>::merge(const VectorType &point)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            lowerCorner[i] = std::min(lowerCorner[i], point[i]);
            upperCorner[i] = std::max(upperCorner[i], point[i]);
        }
    }
    template <typename T, std::size_t N>
    void BoundingBox<T, N>::merge(const BoundingBox &other)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            lowerCorner[i] = std::min(lowerCorner[i], other.lowerCorner[i]);
            upperCorner[i] = std::max(upperCorner[i], other.upperCorner[i]);
        }
    }
    template <typename T, std::size_t N>
    void BoundingBox<T, N>::expand(T delta)
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            lowerCorner -= delta;
            upperCorner += delta;
        }
    }

}

#endif