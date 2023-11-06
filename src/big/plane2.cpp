#include "plane2.h"

namespace big
{

    Plane2::Plane2(const Transform2 &transform, bool isNormalFlipped)
        : Surface2(transform, isNormalFlipped), _normal(0.0, 1.0), _point(0.0, 0.0)
    {
    }
    Plane2::Plane2(const Vector<double, 2> &normal,
                   const Vector<double, 2> &point,
                   const Transform2 &transform,
                   bool isNormalFlipped)
        : Surface2(transform, isNormalFlipped), _normal(normal), _point(point)
    {
    }
    Plane2::Plane2(const Plane2 &other)
        : Surface2(other), _normal(other._normal), _point(other._point)
    {
    }

    bool Plane2::isBounded() const
    {
        return false;
    }

    Plane2::Builder Plane2::builder()
    {
        return Builder();
    }
    Vector<double, 2> Plane2::closestPointLocal(const Vector<double, 2> &otherPoint) const
    {
        auto line = otherPoint - _point;

        double line_project = line.dot(_normal);

        auto line_tangent = line - (line_project * _normal);

        return _point + line_tangent;
    }

    SurfaceRayIntersection2 Plane2::closestIntersectionLocal(const Ray<double, 2> &ray) const
    {
        SurfaceRayIntersection2 intersection;

        auto cos_angle = ray.direction.dot(_normal);

        if (std::fabs(cos_angle) > 0) // not parallel with plane
        {
            auto line = _point - ray.origin;

            double line_project = line.dot(_normal);

            if (line_project > 0) // ray intersect with plane but not line
            {
                intersection.distance = line_project / cos_angle;
                intersection.isIntersecting = true;
                intersection.normal = _normal;
                intersection.point = ray.pointAt(intersection.distance);
            }
        }
        intersection.isIntersecting = false;
        return intersection;
    }

    Vector<double, 2> Plane2::closestNormalLocal(const Vector<double, 2> &otherPoint) const
    {
        return _normal;
    }

    bool Plane2::intersectsLocal(const Ray<double, 2> &rayLocal) const
    {
        auto cos_angle = rayLocal.direction.dot(_normal);

        if (std::fabs(cos_angle) > 0) // not parallel with plane
        {
            auto line = _point - rayLocal.origin;

            double line_project = line.dot(_normal);

            if (line_project > 0) // ray intersect with plane but not line
            {
                return true;
            }
        }
        return false;
    }

    BoundingBox<double, 2> Plane2::boundingBoxLocal() const
    {
        auto temp_a = std::fabs(_normal.dot(Vector<double, 2>(1, 0))) - 1.0;
        auto temp_b = std::fabs(_normal.dot(Vector<double, 2>(0, 1))) - 1.0;
        if (std::fabs(temp_a) < kEpsilonD) // normal is parallel with (0, 1)
        {
            return BoundingBox<double, 2>({_point.x, -kMaxD}, {_point.x, kMaxD});
        }
        else if (std::fabs(temp_b) < kEpsilonD)
        {
            return BoundingBox<double, 2>({-kMaxD, _point.y}, {kMaxD, _point.y});
        }
        else
        {
            return BoundingBox<double, 2>({-kMaxD, -kMaxD}, {kMaxD, kMaxD});
        }
    }

    Plane2::Builder &Plane2::Builder::withNormal(const Vector<double, 2> &normal)
    {
        _normal = normal;
        return *this;
    }

    Plane2::Builder &Plane2::Builder::withPoint(const Vector<double, 2> &point)
    {
        _point = point;
        return *this;
    }

    Plane2 Plane2::Builder::build() const
    {
        return Plane2(_normal, _point, _transform, _isNormalFlipped);
    }

    Plane2Ptr Plane2::Builder::makeShared() const
    {
        return std::shared_ptr<Plane2>(
            new Plane2(_normal, _point, _transform, _isNormalFlipped),
            [](Plane2 *obj)
            { delete obj; });
    }

}