#ifndef INCLUDE_BIG_TRANSFORM2_H_
#define INCLUDE_BIG_TRANSFORM2_H_

#include <bounding_box2.h>
#include <ray2.h>
#include <vector2.h>

namespace big
{

    //! Represents 2-D rigid body transform.
    class Transform2
    {
    public:
        Transform2();

        Transform2(const Vector<double, 2> &translation, double orientation);

        const Vector<double, 2> &translation() const;

        void setTranslation(const Vector<double, 2> &translation);

        double orientation() const;

        void setOrientation(double orientation);

        Vector2D toLocal(const Vector2D &pointInWorld) const;

        Vector2D toLocalDirection(const Vector2D &dirInWorld);

        Ray2D toLocal(const Ray2D &rayInWorld) const;

        BoundingBox2D toLocal(const BoundingBox2D &bboxInWorld) const;

        Vector2D toWorld(const Vector2D &pointInLocal) const;

        Vector2D toWorldDirection(const Vector2D &dirInLocal);

        Ray2D toWorld(const Ray2D &rayInLocal) const;

        BoundingBox2D toWorld(const BoundingBox2D &bboxInLocal) const;

    private:
        Vector<double, 2> _translation;
        double _orientation = 0.0;
        double _cosAngle = 1.0;
        double _sinAngle = 0.0;
    };

}

#include "detail/transform2-inl.h"
#endif
