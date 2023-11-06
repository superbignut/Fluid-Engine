#ifndef INCLUDE_BIG_PLANE2_H_
#define INCLUDE_BIG_PLANE2_H_
#include "surface2.h"

namespace big
{

    class Plane2 final : public Surface2
    {
    public:
        class Builder;

        Vector<double, 2> _normal;

        Vector<double, 2> _point;

        Plane2(const Transform2 &transform = Transform2(), bool isNormalFlipped = false);

        Plane2(const Vector<double, 2> &normal,
               const Vector<double, 2> &point,
               const Transform2 &transform = Transform2(),
               bool isNormalFlipped = false);

        Plane2(const Plane2 &other);

        // ！ Return true if bbx can bedefined.
        bool isBounded() const override;

        static Builder builder();

    private:
        //! Point of both sides are ok.
        Vector<double, 2> closestPointLocal(const Vector<double, 2> &otherPoint) const override;

        SurfaceRayIntersection2 closestIntersectionLocal(const Ray<double, 2> &ray) const override;

        Vector<double, 2> closestNormalLocal(const Vector<double, 2> &otherPoint) const override;

        bool intersectsLocal(const Ray<double, 2> &rayLocal) const override;

        BoundingBox<double, 2> boundingBoxLocal() const override;
    };

    typedef std::shared_ptr<Plane2> Plane2Ptr;
    class Plane2::Builder final : public SurfaceBuilderBase2<Plane2::Builder>
    {
    public:
        //!
        Builder &withNormal(const Vector<double, 2> &normal);

        Builder &withPoint(const Vector<double, 2> &point);

        Plane2 build() const;

        Plane2Ptr makeShared() const;

    private:
        Vector<double, 2> _normal{0, 1};

        Vector<double, 2> _point{0, 0};
    };
}

#endif