#ifndef INCLUDE_BIG_SPHERE2_H_
#define INCLUDE_BIG_SPHERE2_H_
#include "surface2.h"
#include "bounding_box2.h"

namespace big
{
    class Sphere2 final : public Surface2
    {
    public:
        class Builder;

        Vector<double, 2> _center;

        double _radius = 1.0;

        //!
        Sphere2(const Transform2 &transform = Transform2(),
                bool isNormalFlipped = false);

        Sphere2(const Vector<double, 2> &center,
                double radius,
                const Transform2 &transform = Transform2(),
                bool isNormalFlipped = false);
        Sphere2(const Sphere2 &other);

        //! return builder for sphere2.
        static Builder builder();

    private:
        //!
        Vector<double, 2> closestPointLocal(const Vector<double, 2> &otherPoint) const override;

        BoundingBox<double, 2> boundingBoxLocal() const override;

        SurfaceRayIntersection2 closestIntersectionLocal(const Ray<double, 2> &ray) const override;

        Vector<double, 2> closestNormalLocal(const Vector<double, 2> &otherPoint) const override;
    };

    typedef std::shared_ptr<Sphere2> Sphere2Ptr;

    class Sphere2::Builder final : public SurfaceBuilderBase2<Sphere2::Builder>
    {
    public:
        Builder &withCenter(const Vector<double, 2> &center);

        Builder &withRadius(double radius);

        Sphere2 build() const;

        Sphere2Ptr makeShared() const;

    private:
        Vector<double, 2> _center{0, 0}; // or (0.0, 0.0) but (0, 0)

        double _radius = 0.0;
    };
}

#endif