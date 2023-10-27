#ifndef INCLUDE_BIG_TRANSFORM3_H_
#define INCLUDE_BIG_TRANSFORM3_H_

#include <bounding_box3.h>
#include <ray3.h>
#include <vector3.h>

namespace big
{

    //! Represents 3-D rigid body transform.
    //! cos  -sin
    //! sin  +cos
    class Transform3
    {
    public:
        Transform3();

        Transform3(const Vector<double, 3> &translation, double orientation);

        //! return translation
        const Vector<double, 3> &translation() const;

        void setTranslation(const Vector<double, 3> &translation);

        //! return orientation
        double orientation() const;

        void setOrientation(double orientation);

        Vector3D toLocal(const Vector3D &pointInWorld) const;

        Vector3D toLocalDirection(const Vector3D &dirInWorld) const;

        Ray3D toLocal(const Ray3D &rayInWorld) const;

        BoundingBox3D toLocal(const BoundingBox3D &bboxInWorld) const;

        Vector3D toWorld(const Vector3D &pointInLocal) const;

        Vector3D toWorldDirection(const Vector3D &dirInLocal) const;

        Ray3D toWorld(const Ray3D &rayInLocal) const;

        BoundingBox3D toWorld(const BoundingBox3D &bboxInLocal) const;

    private:
        Vector<double, 3> _translation;
        double _orientation = 0.0;
        double _cosAngle = 1.0;
        double _sinAngle = 0.0;
    };

}

#include "detail/transform3-inl.h"
#endif
