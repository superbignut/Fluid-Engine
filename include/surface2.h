#ifndef INCLUDE_BIG_SURFACE2_H_
#define INCLUDE_BIG_SURFACE2_H_
#include "bounding_box2.h"
#include "constants.h"
#include "ray2.h"
#include "transform2.h"
#include <memory>

namespace big
{

    //! Struct that represents ray-surface intersection point.
    struct SurfaceRayIntersection2
    {
        bool isIntersecting = false;

        double distance = kMaxD;

        Vector<double, 2> point;

        Vector<double, 2> normal;
    };

    class Surface2
    {
    public:
        //!
        //! local-to-world transform.
        Transform2 _transform;

        bool _isNormalFlipped = false;

        Surface2(const Transform2 transform = Transform2(), bool isNormalFlippe = false);

        Surface2(const Surface2 &other);

        virtual ~Surface2();

        //! the closest point of the surface.
        Vector<double, 2> closestPoint(const Vector<double, 2> &otherPoint) const;

        //! the bbx of the surface.
        BoundingBox<double, 2> boundingBox() const;

        //! if ray intersects with the surface.
        bool intersects(const Ray<double, 2> &ray) const;

        double closestDistance(const Vector<double, 2> &otherPoint) const;

        Vector<double, 2> closestNormal(const Vector<double, 2> &otherPoint) const;

        SurfaceRayIntersection2 closestIntersection(const Ray<double, 2> &ray) const;

        //! Update internal spatial quary engine. Empty
        virtual void updateQueryEngine();

        //! If bbx can be defined.
        virtual bool isBounded() const;

        // ！ If surface is valid geometry.
        virtual bool isValidGeometry() const;

        //! If point is inside the volume defined by surface.
        bool isInside(const Vector<double, 2> &otherPoint) const;

    protected:
        //!
        //! Return the closest point from the given point to the surface in local frame.
        virtual Vector<double, 2> closestPointLocal(const Vector<double, 2> &otherPoint) const = 0;

        //! Return the BoundingBox of this surface in local frame.
        virtual BoundingBox<double, 2> boundingBoxLocal(const Vector<double, 2> &otherPoint) const = 0;

        //! Local
        virtual SurfaceRayIntersection2 closestIntersectionLocal(const Ray<double, 2> &ray) const = 0;

        virtual Vector<double, 2> closestNormalLocal(const Vector<double, 2> &otherPoint) const = 0;

        virtual bool intersectsLocal(const Ray<double, 2> &ray) const;

        virtual double closestDistanceLocal(const Vector<double, 2> &otherPoint) const;

        virtual bool isInsideLocal(const Vector<double, 2> &otherPoint) const;
    };

    typedef std::shared_ptr<Surface2> Surface2Ptr;

    template <typename DrivedBuilder>
    class SurfaceBuilderBase2
    {
    public:
        //! return builder with ...
        DrivedBuilder &withIsNormalFlipped(bool isNormalFlipped);

        DrivedBuilder &withTranslation(const Vector<double, 2> &translation);

        DrivedBuilder &withOrientation(double orientation);

        DrivedBuilder &withTransform(const Transform2 &transform);

    protected:
        bool _isNormalFlipped = false;

        Transform2 _transform;
    };

    template <typename DrivedBuilder>
    DrivedBuilder &SurfaceBuilderBase2<DrivedBuilder>::withIsNormalFlipped(bool isNormalFlipped)
    {
        _isNormalFlipped = isNormalFlipped;
        return static_cast<DrivedBuilder &>(*this);
    }

    template <typename DrivedBuilder>
    DrivedBuilder &SurfaceBuilderBase2<DrivedBuilder>::withTranslation(const Vector<double, 2> &translation)
    {
        _transform.setTranslation(translation);
        return static_cast<DrivedBuilder &>(*this);
    }

    template <typename DrivedBuilder>
    DrivedBuilder &SurfaceBuilderBase2<DrivedBuilder>::withOrientation(double orientation)
    {
        _transform.setOrientation(orientation);
        return static_cast<DrivedBuilder &>(*this);
    }

    template <typename DrivedBuilder>
    DrivedBuilder &SurfaceBuilderBase2<DrivedBuilder>::withTransform(const Transform2 &transform)
    {
        _transform = transform;
        return static_cast<DrivedBuilder &>(*this);
    }
}

#endif