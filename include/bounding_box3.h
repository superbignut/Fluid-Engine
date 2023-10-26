#ifndef INCLUDE_BIG_BOUNDING_BOX3_H_
#define INCLUDE_BIG_BOUNDING_BOX3_H_
#include "bounding_box.h"
#include "ray3.h"
// #include "vector3.h"

namespace big
{

    //! 3-D box-ray intersection result.
    template <typename T>
    struct BoundingBoxRayIntersection3
    {
        bool isIntersection = false;
        //! Distance to the first intersection point.
        T tNear = std::numeric_limits<T>::max();
        //! DIstance to the second intersection point.
        T tFar = std::numeric_limits<T>::max();
    };

    //! 3-D axis-aligned bounding box class
    template <typename T>
    class BoundingBox<T, 3>
    {
    public:
        Vector<T, 3> lowerCorner;

        Vector<T, 3> upperCorner;

        BoundingBox();

        BoundingBox(const Vector<T, 3> &point1, const Vector<T, 3> &point3);

        BoundingBox(const BoundingBox &other);

        //! return the width of the box;
        T width() const;

        T height() const;

        T depth() const;

        //! return the length of box in the given axis = 0 or 1 or 2.
        T length(std::size_t axis) const;

        bool overlaps(const BoundingBox &other) const;

        bool contains(const Vector<T, 3> &point) const;

        //！ we don't consider the edge cases.
        bool intersects(const Ray<T, 3> &ray) const;
        
        // return BoundingBoxRayIntersection3 
        BoundingBoxRayIntersection3<T> closestIntersection(const Ray<T, 3> &ray) const;

        Vector<T, 3> midPoint() const;

        //! return diag length
        T diagonalLength() const;

        //!
        T diagonalLengthSquared() const;

        void reset();

        //! merge this and a point
        void merge(const Vector<T, 3> &point);

        //! merge this and a box
        void merge(const BoundingBox &other);

        //! expand delta
        void expand(T delta);
        //      6  7
        //      4  5
        //  2  3
        //  0  1
        Vector<T, 3> corner(std::size_t idx) const;
        
        Vector<T, 3> clamp(const Vector<T, 3> &pt) const;

        bool isEmpty() const;
    };

    template <typename T>
    using BoundingBox3 = BoundingBox<T, 3>;

    typedef BoundingBox3<float> BoundingBox3F;

    typedef BoundingBox3<double> BoundingBox3D;

    typedef BoundingBoxRayIntersection3<float> BoundingBoxRayIntersection3F;

    typedef BoundingBoxRayIntersection3<double> BoundingBoxRayIntersection3D;
}


#include "detail/bounding_box3-inl.h"

#endif