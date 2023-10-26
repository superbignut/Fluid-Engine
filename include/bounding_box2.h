#ifndef INCLUDE_BIG_BOUNDING_BOX2_H_
#define INCLUDE_BIG_BOUNDING_BOX2_H_

#include "bounding_box.h"
#include "ray2.h"
// #include "vector2.h"

namespace big
{

    //! 2-D box-ray intersection result.
    template <typename T>
    struct BoundingBoxRayIntersection2
    {
        bool isIntersection = false;
        //! Distance to the first intersection point.
        T tNear = std::numeric_limits<T>::max();
        //! DIstance to the second intersection point.
        T tFar = std::numeric_limits<T>::max();
    };

    //! 2-D axis-aligned bounding box class
    template <typename T>
    class BoundingBox<T, 2>
    {
    public:
        Vector<T, 2> lowerCorner;

        Vector<T, 2> upperCorner;

        BoundingBox();

        BoundingBox(const Vector<T, 2> &point1, const Vector<T, 2> &point2);

        BoundingBox(const BoundingBox &other);

        //! return the width of the box;
        T width() const;

        T height() const;

        //! return the length of box in the given axis = 0 or 1.
        T length(std::size_t axis) const;

        bool overlaps(const BoundingBox &other) const;

        bool contains(const Vector<T, 2> &point) const;

        //！ we don't consider the edge cases.
        bool intersects(const Ray<T, 2> &ray) const;
        
        // return BoundingBoxRayIntersection2 
        BoundingBoxRayIntersection2<T> closestIntersection(const Ray<T, 2> &ray) const;

        Vector<T, 2> midPoint() const;

        //! return diag length
        T diagonalLength() const;

        //!
        T diagonalLengthSquared() const;

        void reset();

        //! merge this and a point
        void merge(const Vector<T, 2> &point);

        //! merge this and a box
        void merge(const BoundingBox &other);

        //! expand delta
        void expand(T delta);

        //  2  3
        //  0  1
        Vector<T, 2> corner(std::size_t idx) const;
        
        Vector<T, 2> clamp(const Vector<T, 2> &pt) const;

        bool isEmpty() const;
    };

    template <typename T>
    using BoundingBox2 = BoundingBox<T, 2>;

    typedef BoundingBox2<float> BoundingBox2F;

    typedef BoundingBox2<double> BoundingBox2D;

    typedef BoundingBoxRayIntersection2<float> BoundingBoxRayIntersection2F;

    typedef BoundingBoxRayIntersection2<double> BoundingBoxRayIntersection2D;
}


#include "detail/bounding_box2-inl.h"
#endif