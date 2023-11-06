#include "surface3.h"

namespace big
{

    Surface3::Surface3(const Transform3 &transform, bool isNormalFlipped)
        : _transform(transform), _isNormalFlipped(isNormalFlipped) {}

    Surface3::Surface3(const Surface3 &other)
        : _transform(other._transform), _isNormalFlipped(other._isNormalFlipped) {}

    Vector<double, 3> Surface3::closestPoint(const Vector<double, 3> &otherPoint) const
    {
        return _transform.toWorld(closestPointLocal(_transform.toLocal(otherPoint)));
    }

    BoundingBox<double, 3> Surface3::boundingBox() const
    {
        return _transform.toWorld(boundingBoxLocal());
    }

    bool Surface3::intersects(const Ray<double, 3> &ray) const
    {
        return intersectsLocal(_transform.toLocal(ray));
    }

    double Surface3::closestDistance(const Vector<double, 3> &otherPoint) const
    {
        return closestDistanceLocal(_transform.toLocal(otherPoint));
    }

    Vector<double, 3> Surface3::closestNormal(const Vector<double, 3> &otherPoint) const
    {
        auto result = _transform.toWorldDirection(
            closestNormalLocal(_transform.toLocal(otherPoint))); 
        result *= (_isNormalFlipped) ? -1.0 : 1.0;
        return result;
    }

    SurfaceRayIntersection3 Surface3::closestIntersection(const Ray<double, 3> &ray) const
    {
        auto result = closestIntersectionLocal(_transform.toLocal(ray));
        result.point = _transform.toWorld(result.point);
        result.normal = _transform.toWorld(result.normal);
        result.normal *= _isNormalFlipped ? -1.0 : 1.0;
        return result;
    }

    void Surface3::updateQueryEngine()
    {
        //! empty
    }

    bool Surface3::isBounded() const
    {
        return true;
    }

    bool Surface3::isValidGeometry() const
    {
        return true;
    }

    bool Surface3::isInside(const Vector<double, 3> &otherPoint) const
    {
        return _isNormalFlipped == !isInsideLocal(_transform.toLocal(otherPoint));
    }

    bool Surface3::intersectsLocal(const Ray<double, 3> &rayLocal) const
    {
        return closestIntersectionLocal(rayLocal).isIntersecting;
    }

    double Surface3::closestDistanceLocal(const Vector<double, 3> &otherPointLocal) const
    {
        return otherPointLocal.distanceTo(closestPointLocal(otherPointLocal));
    }

    bool Surface3::isInsideLocal(const Vector<double, 3> &otherPointLocal) const
    {
        auto cpLocal = closestPointLocal(otherPointLocal);
        auto nrLocal = closestNormalLocal(otherPointLocal);
        return (otherPointLocal - cpLocal).dot(nrLocal) < 0.0;
    }
}