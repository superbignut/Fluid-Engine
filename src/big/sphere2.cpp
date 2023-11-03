#include "sphere2.h"

namespace big
{
    Sphere2::Sphere2(const Transform2 &transform, bool isNormalFlipped)
        : Surface2(transform, isNormalFlipped), _center(0, 0), _radius(0.0)
    {
    }
    Sphere2::Sphere2(const Vector<double, 2> &center,
                     double radius,
                     const Transform2 &transform,
                     bool isNormalFlipped)
        : Surface2(transform, isNormalFlipped), _center(center), _radius(radius)
    {
    }

    Sphere2::Sphere2(const Sphere2 &other)
        : Surface2(other), _center(other._center), _radius(other._radius)
    {
    }

    Sphere2::Builder Sphere2::builder()
    {
        return Builder();
    }

    Vector<double, 2> Sphere2::closestPointLocal(const Vector<double, 2> &otherPoint) const
    {
    }

    BoundingBox<double, 2> Sphere2::boundingBoxLocal() const
    {
    }

    SurfaceRayIntersection2 Sphere2::closestIntersectionLocal(const Ray<double, 2> &ray) const
    {
    }

    Vector<double, 2> Sphere2::closestNormalLocal(const Vector<double, 2> &otherPoint) const
    {
    }

}