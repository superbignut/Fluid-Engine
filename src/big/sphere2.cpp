#include "sphere2.h"

namespace big
{
    Sphere2::Sphere2(const Transform2 &transform, bool isNormalFlipped)
        : Surface2(transform, isNormalFlipped), _center(0, 0), _radius(0.0)
    {
        // Empty
    }
    Sphere2::Sphere2(const Vector<double, 2> &center,
                     double radius,
                     const Transform2 &transform,
                     bool isNormalFlipped)
        : Surface2(transform, isNormalFlipped), _center(center), _radius(radius)
    {
        // Empty
    }

    Sphere2::Sphere2(const Sphere2 &other)
        : Surface2(other), _center(other._center), _radius(other._radius)
    {
        // Empty
    }

    Sphere2::Builder Sphere2::builder()
    {
        return Builder();
    }

    Vector<double, 2> Sphere2::closestPointLocal(const Vector<double, 2> &otherPoint) const
    {
        return _radius * closestNormalLocal(otherPoint) + _center; // r * n + o
    }

    BoundingBox<double, 2> Sphere2::boundingBoxLocal() const
    {
        Vector<double, 2> r(_radius, _radius);
        return BoundingBox<double, 2>(_center - r, _center + r);
    }

    SurfaceRayIntersection2 Sphere2::closestIntersectionLocal(const Ray<double, 2> &ray) const
    {
        SurfaceRayIntersection2 intersection;
        Vector<double, 2> origin2center = _center - ray.origin;
        double d_ray_project = origin2center.dot(ray.direction);

        double d2_perpendicular = origin2center.lengthSquared() - square(d_ray_project);

        double d2_delta = square(_radius) - d2_perpendicular;

        if (d2_delta > 0) // line have intersectons with circle, but not ray
        {
            double d_delta = std::sqrt(d2_delta);

            double t_min = d_ray_project - d_delta;
            double t_max = d_ray_project + d_delta;
            if (t_min < 0) // ray.origin is inside circle
            {
                t_min = t_max;
            }
            if (t_min < 0) // no intersection while reverse-direction ray has two intersections.
            {
                intersection.isIntersecting = false;
            }
            else
            {
                intersection.isIntersecting = true;
                intersection.distance = t_min;
                intersection.point = ray.origin + ray.direction * t_min;
                intersection.normal = (intersection.point - _center).normalized();
            }
        }
        else
        {
            intersection.isIntersecting = false;
        }
        return intersection;
    }

    Vector<double, 2> Sphere2::closestNormalLocal(const Vector<double, 2> &otherPoint) const
    {
        if (otherPoint.isSimilar(_center))
        {
            return Vector<double, 2>{1, 0};
        }
        else
        {
            return (otherPoint - _center).normalized();
        }
    }

    bool Sphere2::intersectsLocal(const Ray<double, 2> &rayLocal) const
    {
        Vector<double, 2> origin2center = _center - rayLocal.origin;
        double d_ray_project = origin2center.dot(rayLocal.direction);

        double d2_perpendicular = origin2center.lengthSquared() - square(d_ray_project);

        double d2_delta = square(_radius) - d2_perpendicular;

        if (d2_delta > 0) // line have intersectons with circle, but not ray
        {
            double d_delta = std::sqrt(d2_delta);

            double t_min = d_ray_project - d_delta;
            double t_max = d_ray_project + d_delta;
            if (t_min > 0 || t_max > 0) // ray.origin is inside circle
            {
                return true;
            }
        }
        return false;
    }

    double Sphere2::closestDistanceLocal(const Vector<double, 2> &otherPointLocal) const
    {
        return std::fabs(_center.distanceTo(otherPointLocal) - _radius);
    }

    Sphere2::Builder &Sphere2::Builder::withCenter(const Vector<double, 2> &center)
    {
        _center = center;
        return *this;
    }

    Sphere2::Builder &Sphere2::Builder::withRadius(double radius)
    {
        _radius = radius;
        return *this;
    }

    //! return a Sphere2.
    Sphere2 Sphere2::Builder::build() const
    {
        return Sphere2(_center, _radius, _transform, _isNormalFlipped);
    }

    //! return a Sphere2Ptr
    Sphere2Ptr Sphere2::Builder::makeShared() const
    {
        // return std::shared_ptr<Sphere2>()
        return std::shared_ptr<Sphere2>(
            new Sphere2(_center, _radius, _transform, _isNormalFlipped),
            [](Sphere2 *obj)
            { delete obj; });
    }
}