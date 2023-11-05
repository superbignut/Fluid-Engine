#ifndef INCLUDE_BIG_SPHERE3_H_
#define INCLUDE_BIG_SPHERE3_H_
#include "surface3.h"
#include "bounding_box3.h"

namespace big
{
    class Sphere3 final : public Surface3
    {
    public:
        class Builder;

        Vector<double, 3> _center{0, 0, 0};

        double _radius = 1.0;

        //!
        Sphere3(const Transform3 &transform = Transform3(),
                bool isNormalFlipped = false);

        Sphere3(const Vector<double, 3> &center,
                double radius,
                const Transform3 &transform = Transform3(),
                bool isNormalFlipped = false);
        Sphere3(const Sphere3 &other);

        //! return builder for sphere3.
        static Builder builder();

    private:
        //!
        Vector<double, 3> closestPointLocal(const Vector<double, 3> &otherPoint) const override;

        BoundingBox<double, 3> boundingBoxLocal() const override;

        SurfaceRayIntersection3 closestIntersectionLocal(const Ray<double, 3> &ray) const override;

        Vector<double, 3> closestNormalLocal(const Vector<double, 3> &otherPoint) const override;

        bool intersectsLocal(const Ray<double, 3> &rayLocal) const override; //use a special and simple version

        double closestDistanceLocal(const Vector<double, 3> &otherPointLocal) const override; //use a special and simple version
    };

    typedef std::shared_ptr<Sphere3> Sphere3Ptr;

    class Sphere3::Builder final : public SurfaceBuilderBase3<Sphere3::Builder>
    {
    public:
        Builder &withCenter(const Vector<double, 3> &center);

        Builder &withRadius(double radius);

        //! return a Sphere3.
        Sphere3 build() const;

        //! return a Sphere3Ptr
        Sphere3Ptr makeShared() const;

    private:
        Vector<double, 3> _center{0, 0, 0}; 

        double _radius = 1.0;
    };
}

#endif