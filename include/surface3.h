#ifndef INCLUDE_BIG_SURFACE3_H_
#define INCLUDE_BIG_SURFACE3_H_
#include "bounding_box3.h"
#include "constants.h"
#include "ray3.h"
#include "transform3.h"
#include <memory>

namespace big
{

    //! Struct that represents ray-surface intersection point.
    struct SurfaceRayIntersection3
    {
        bool isIntersecting = false;

        double distance = kMaxD; // distance between origin point and intersection

        Vector<double, 3> point; // intersection

        Vector<double, 3> normal; // surface normal at intersection
    };

    class Surface3
    {
    public:
        //!
        //! local-to-world transform.
        Transform3 _transform;

        bool _isNormalFlipped = false;

        Surface3(const Transform3 transform = Transform3(), bool isNormalFlipped = false);

        Surface3(const Surface3 &other);

        virtual ~Surface3();

        //! the closest point of the surface.
        Vector<double, 3> closestPoint(const Vector<double, 3> &otherPoint) const;

        //! the bbx of the surface.
        BoundingBox<double, 3> boundingBox() const;

        //! if ray intersects with the surface.
        bool intersects(const Ray<double, 3> &ray) const;

        //! min distance 
        double closestDistance(const Vector<double, 3> &otherPoint) const;

        //! return the normal to the closest point on the surface.
        Vector<double, 3> closestNormal(const Vector<double, 3> &otherPoint) const;

        //! return the closest intersection
        SurfaceRayIntersection3 closestIntersection(const Ray<double, 3> &ray) const;

        //! Update internal spatial quary engine. Empty
        virtual void updateQueryEngine();

        //! If bbx can be defined.
        virtual bool isBounded() const;

        // ！ If surface is valid geometry.
        virtual bool isValidGeometry() const;

        //! If point is inside the volume defined by surface.
        bool isInside(const Vector<double, 3> &otherPoint) const;

    protected:
        //!
        //! Return the closest point from the given point to the surface in local frame.
        virtual Vector<double, 3> closestPointLocal(const Vector<double, 3> &otherPoint) const = 0;

        //! Return the BoundingBox of this surface in local frame.
        virtual BoundingBox<double, 3> boundingBoxLocal() const = 0;

        //! Local
        virtual SurfaceRayIntersection3 closestIntersectionLocal(const Ray<double, 3> &ray) const = 0;

        virtual Vector<double, 3> closestNormalLocal(const Vector<double, 3> &otherPoint) const = 0;

        virtual bool intersectsLocal(const Ray<double, 3> &rayLocal) const;

        virtual double closestDistanceLocal(const Vector<double, 3> &otherPointLocal) const;

        virtual bool isInsideLocal(const Vector<double, 3> &otherPointLocal) const;
    };

    typedef std::shared_ptr<Surface3> Surface3Ptr;

    template <typename DrivedBuilder>
    class SurfaceBuilderBase3
    {
    public:
        //! return builder with ...
        DrivedBuilder &withIsNormalFlipped(bool isNormalFlipped);

        DrivedBuilder &withTranslation(const Vector<double, 3> &translation);

        DrivedBuilder &withOrientation(const Quaternion<double>& orientation);

        DrivedBuilder &withTransform(const Transform3 &transform);

    protected:
        bool _isNormalFlipped = false;

        Transform3 _transform;
    };

    template <typename DrivedBuilder>
    DrivedBuilder &SurfaceBuilderBase3<DrivedBuilder>::withIsNormalFlipped(bool isNormalFlipped)
    {
        _isNormalFlipped = isNormalFlipped;
        return static_cast<DrivedBuilder &>(*this);
    }

    template <typename DrivedBuilder>
    DrivedBuilder &SurfaceBuilderBase3<DrivedBuilder>::withTranslation(const Vector<double, 3> &translation)
    {
        _transform.setTranslation(translation);
        return static_cast<DrivedBuilder &>(*this);
    }

    template <typename DrivedBuilder>
    DrivedBuilder &SurfaceBuilderBase3<DrivedBuilder>::withOrientation(const Quaternion<double>& orientation)
    {
        _transform.setOrientation(orientation);
        return static_cast<DrivedBuilder &>(*this);
    }

    template <typename DrivedBuilder>
    DrivedBuilder &SurfaceBuilderBase3<DrivedBuilder>::withTransform(const Transform3 &transform)
    {
        _transform = transform;
        return static_cast<DrivedBuilder &>(*this);
    }
}

#endif