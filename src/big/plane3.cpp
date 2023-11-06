#include "plane3.h"

namespace big
{

    Plane3::Plane3(const Transform3 &transform, bool isNormalFlipped)
        : Surface3(transform, isNormalFlipped), _normal(0.0, 1.0, 0.0), _point(0.0, 0.0, 0.0)
    {
    }
    Plane3::Plane3(const Vector<double, 3> &normal,
                   const Vector<double, 3> &point,
                   const Transform3 &transform,
                   bool isNormalFlipped)
        : Surface3(transform, isNormalFlipped), _normal(normal), _point(point)
    {
    }

    Plane3::Plane3(const Vector<double, 3> &point1,
                   const Vector<double, 3> &point2,
                   const Vector<double, 3> &point3,
                   const Transform3 &_transform,
                   bool isNormalFlipped)
    {
        _normal = (point2 - point1).cross(point3 - point2).normalized();
        _point = point1;
    }
    Plane3::Plane3(const Plane3 &other)
        : Surface3(other), _normal(other._normal), _point(other._point)
    {
    }

    bool Plane3::isBounded() const
    {
        return false;
    }

    Plane3::Builder Plane3::builder()
    {
        return Builder();
    }
    Vector<double, 3> Plane3::closestPointLocal(const Vector<double, 3> &otherPoint) const
    {
        auto line = otherPoint - _point;

        double line_project = line.dot(_normal);

        auto line_tangent = line - (line_project * _normal);

        return _point + line_tangent;
    }

    SurfaceRayIntersection3 Plane3::closestIntersectionLocal(const Ray<double, 3> &ray) const
    {
        SurfaceRayIntersection3 intersection;

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

    Vector<double, 3> Plane3::closestNormalLocal(const Vector<double, 3> &otherPoint) const
    {
        return _normal;
    }

    bool Plane3::intersectsLocal(const Ray<double, 3> &rayLocal) const
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

    BoundingBox<double, 3> Plane3::boundingBoxLocal() const
    {
        auto temp_a = std::fabs(_normal.dot(Vector<double, 3>(1, 0, 0))) - 1.0;
        auto temp_b = std::fabs(_normal.dot(Vector<double, 3>(0, 1, 0))) - 1.0;
        auto temp_c = std::fabs(_normal.dot(Vector<double, 3>(0, 0, 1))) - 1.0;
        if (std::fabs(temp_a) < kEpsilonD) // normal is parallel with (0, 1)
        {
            return BoundingBox<double, 3>({_point.x, -kMaxD, -kMaxD}, {_point.x, kMaxD, kMaxD});
        }
        else if (std::fabs(temp_b) < kEpsilonD)
        {
            return BoundingBox<double, 3>({-kMaxD, -kMaxD, _point.y}, {kMaxD, kMaxD, _point.y});
        }
        else if (std::fabs(temp_c) < kEpsilonD)
        {
            return BoundingBox<double, 3>({-kMaxD, -kMaxD, _point.z}, {kMaxD, kMaxD, _point.z});
        }
        else
        {
            return BoundingBox<double, 3>({-kMaxD, -kMaxD, -kMaxD}, {kMaxD, kMaxD, kMaxD});
        }
    }

    Plane3::Builder &Plane3::Builder::withNormal(const Vector<double, 3> &normal)
    {
        _normal = normal;
        return *this;
    }

    Plane3::Builder &Plane3::Builder::withPoint(const Vector<double, 3> &point)
    {
        _point = point;
        return *this;
    }

    Plane3 Plane3::Builder::build() const
    {
        return Plane3(_normal, _point, _transform, _isNormalFlipped);
    }

    Plane3Ptr Plane3::Builder::makeShared() const
    {
        return std::shared_ptr<Plane3>(
            new Plane3(_normal, _point, _transform, _isNormalFlipped),
            [](Plane3 *obj)
            { delete obj; });
    }

}