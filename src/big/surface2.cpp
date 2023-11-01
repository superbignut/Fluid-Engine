#include "surface2.h"

namespace big
{

    Surface2::Surface2(const Transform2 transform, bool isNormalFlipped)
        : _transform(transform), _isNormalFlipped(isNormalFlipped) {}

    Surface2::Surface2(const Surface2 &other)
        : _transform(other._transform), _isNormalFlipped(other._isNormalFlipped) {}

    Vector<double, 2> Surface2::closestPoint(const Vector<double, 2> &otherPoint) const
    {
        return _transform.toWorld(closestPointLocal(_transform.toLocal(otherPoint)));
    }

    BoundingBox<double, 2> Surface2::boundingBox() const
    {
        return _transform.toWorld(boundingBoxLocal());
    }

    bool Surface2::intersects(const Ray<double, 2> &ray) const
    {
        return intersectsLocal(_transform.toLocal(ray));
    }

    double Surface2::closestDistance(const Vector<double, 2> &otherPoint) const
    {
        return closestDistance(_transform.toLocal(otherPoint));
    }

    Vector<double, 2> Surface2::closestNormal(const Vector<double, 2> &otherPoint) const
    {
        auto result = _transform.toWorldDirection(
            closestNormalLocal(transform.toLocal(otherPoint)));
        result *= (_isNormalFlipped) ? -1.0 : 1.0;
        return result;
    }

    SurfaceRayIntersection2 Surface2::closestIntersection(const Ray<double, 2> &ray) const
    {
        auto result = closestIntersectionLocal(_transform.toLocal(ray));
        result.point = _transform.toWorld(result.point);
        result.normal = _transform.toWorld(result.normal);
        result.normal *= _isNormalFlipped ? -1.0 : 1.0;
        return result;
    }

    void Surface2::updateQueryEngine()
    {
        //! empty
    }

    bool Surface2::isBounded() const
    {
        return true;
    }

    bool Surface2::isValidGeometry() const
    {
        return true;
    }

    bool Surface2::isInside(const Vector<double, 2> &otherPoint) const
    {
        return _isNormalFlipped == !isInsideLocal(_transform.toLocal(otherPoint));
    }

    bool Surface2::intersectsLocal(const Ray<double, 2> &rayLocal) const
    {
        return closestIntersectionLocal(rayLocal).isIntersecting;
    }

    double Surface2::closestDistanceLocal(const Vector<double, 2> &otherPointLocal) const
    {
        return otherPointLocal.distanceTo(closestPointLocal(otherPointLocal));
    }

    bool Surface2::isInsideLocal(const Vector<double, 2> &otherPointLocal) const
    {
        auto cpLocal = closestPointLocal(otherPointLocal);
        auto nrLocal = closestNormalLocal(otherPointLocal);
        return (otherPointLocal - cpLocal).dot() < 0.0;
    }
}