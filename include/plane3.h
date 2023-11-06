#ifndef INCLUDE_BIG_PLANE3_H_
#define INCLUDE_BIG_PLANE3_H_
#include "surface3.h"

namespace big
{

    class Plane3 final : public Surface3
    {
    public:
        class Builder;

        Vector<double, 3> _normal;

        Vector<double, 3> _point;

        Plane3(const Transform3 &_transform = Transform3(), bool isNormalFlipped = false);

        Plane3(const Vector<double, 3> &normal,
               const Vector<double, 3> &point,
               const Transform3 &_transform = Transform3(),
               bool isNormalFlipped = false);

        Plane3(const Vector<double, 3> &point1,
               const Vector<double, 3> &point2,
               const Vector<double, 3> &point3,
               const Transform3 &_transform = Transform3(),
               bool isNormalFlipped = false);

        Plane3(const Plane3 &other);

        // ！ Return true if bbx can bedefined.
        bool isBounded() const override;

        static Builder builder();

    private:
        //!
        Vector<double, 3> closestPointLocal(const Vector<double, 3> &otherPoint) const override;

        SurfaceRayIntersection3 closestIntersectionLocal(const Ray<double, 3> &ray) const override;

        Vector<double, 3> closestNormalLocal(const Vector<double, 3> &otherPoint) const override;

        bool intersectsLocal(const Ray<double, 3> &rayLocal) const override;

        BoundingBox<double, 3> boundingBoxLocal() const override;
    };

    typedef std::shared_ptr<Plane3> Plane3Ptr;
    class Plane3::Builder final : public SurfaceBuilderBase3<Plane3::Builder>
    {
    public:
        //!
        Builder &withNormal(const Vector<double, 3> &normal);

        Builder &withPoint(const Vector<double, 3> &normal);

        Plane3 build() const;

        Plane3Ptr makeShared() const;

    private:
        Vector<double, 3> _normal{0, 1, 0};

        Vector<double, 3> _point{0, 0, 0};
    };
}

#endif