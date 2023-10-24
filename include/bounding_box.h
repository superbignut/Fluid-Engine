#ifndef INCLUDE_BIG_BOUNDING_BOX_H_
#define INCLUDE_BIG_BOUNDING_BOX_H_

#include "vector.h"

namespace big
{
    //! \brief Generic N-D axis-aligned bounding box class.

    template <typename T, std::size_t N>
    class BoundingBox
    {
    public:
        static_assert(N > 0, "Size of bounding box should be greater than 0.");

        typedef Vector<T, N> VectorType;

        VectorType lowerCorner;

        VectorType upperCorner;

        BoundingBox();

        //! construct a box that tightly covers two points.
        BoundingBox(const VectorType &point1, const VectorType &point2);

        BoundingBox(const BoundingBox &other);

        //! whether overlaps
        bool overlaps(const BoundingBox &other) const;

        //! whether contain 
        bool contains(const VectorType &point) const;

        //! return mid
        VectorType midPoint() const;

        //! return diag length
        T diagonalLength() const;

        //!
        T diagonalLengthSquared() const;

        //!
        void reset();

        //! merge this and a point
        void merge(const VectorType &point);

        //! merge this and a box
        void merge(const BoundingBox &other);

        //!expand delta
        void expand(T delta);
    };

}

#include "detail/bounding_box-inl.h"
#endif