#include "sphere3.h"

namespace big
{
    Sphere3::Sphere3(const Transform3 &transform, bool isNormalFlipped)
        : Surface3(transform, isNormalFlipped), _center(0, 0, 0), _radius(1.0)
    {
        // Empty
    }
    Sphere3::Sphere3(const Vector<double, 3> &center,
                     double radius,
                     const Transform3 &transform,
                     bool isNormalFlipped)
        : Surface3(transform, isNormalFlipped), _center(center), _radius(radius)
    {
        // Empty
    }

    Sphere3::Sphere3(const Sphere3 &other)
        : Surface3(other), _center(other._center), _radius(other._radius)
    {
        // Empty
    }

    Sphere3::Builder Sphere3::builder()
    {
        return Builder();
    }

    Vector<double, 3> Sphere3::closestPointLocal(const Vector<double, 3> &otherPoint) const
    {
        return _radius * closestNormalLocal(otherPoint) + _center; // r * n + o
    }

    BoundingBox<double, 3> Sphere3::boundingBoxLocal() const
    {
        Vector<double, 3> r(_radius, _radius, _radius);
        return BoundingBox<double, 3>(_center - r, _center + r);
    }

    SurfaceRayIntersection3 Sphere3::closestIntersectionLocal(const Ray<double, 3> &ray) const
    {
        SurfaceRayIntersection3 intersection;
        Vector<double, 3> origin3center = _center - ray.origin;
        double d_ray_project = origin3center.dot(ray.direction);

        double d3_perpendicular = origin3center.lengthSquared() - square(d_ray_project);

        double d3_delta = square(_radius) - d3_perpendicular;

        if (d3_delta > 0) // line have intersectons with circle, but not ray
        {
            double d_delta = std::sqrt(d3_delta);

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

    Vector<double, 3> Sphere3::closestNormalLocal(const Vector<double, 3> &otherPoint) const
    {
        if (otherPoint.isSimilar(_center))
        {
            return Vector<double, 3>{1, 0, 0};
        }
        else
        {
            return (otherPoint - _center).normalized();
        }
    }

    bool Sphere3::intersectsLocal(const Ray<double, 3> &rayLocal) const
    {
        Vector<double, 3> origin3center = _center - rayLocal.origin;
        double d_ray_project = origin3center.dot(rayLocal.direction);

        double d3_perpendicular = origin3center.lengthSquared() - square(d_ray_project);

        // std::cout << "IntersectsLocal INFO:Distance^2 betweeen _center and ray is :" << d3_perpendicular<<std::endl;

        double d3_delta = square(_radius) - d3_perpendicular;

        if (d3_delta > 0) // line have intersectons with circle, but not ray
        {
            double d_delta = std::sqrt(d3_delta);

            double t_min = d_ray_project - d_delta;
            double t_max = d_ray_project + d_delta;
            if (t_min > 0 || t_max > 0) // ray.origin is inside circle
            {
                return true;
            }
        }
        return false;
    }

    double Sphere3::closestDistanceLocal(const Vector<double, 3> &otherPointLocal) const
    {
        return std::fabs(_center.distanceTo(otherPointLocal) - _radius);
    }

    Sphere3::Builder &Sphere3::Builder::withCenter(const Vector<double, 3> &center)
    {
        _center = center;
        return *this;
    }

    Sphere3::Builder &Sphere3::Builder::withRadius(double radius)
    {
        _radius = radius;
        return *this;
    }

    //! return a Sphere3.
    Sphere3 Sphere3::Builder::build() const
    {
        return Sphere3(_center, _radius, _transform, _isNormalFlipped);
    }

    //! return a Sphere3Ptr
    Sphere3Ptr Sphere3::Builder::makeShared() const
    {
        return std::shared_ptr<Sphere3>(
            new Sphere3(_center, _radius, _transform, _isNormalFlipped),
            [](Sphere3 *obj)
            { delete obj; });
    }
}