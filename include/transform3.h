#ifndef INCLUDE_BIG_TRANSFORM3_H_
#define INCLUDE_BIG_TRANSFORM3_H_

#include <bounding_box3.h>
#include <ray3.h>
#include <vector3.h>
#include "quaternion.h"
namespace big
{

    //! Represents 3-D rigid body transform.
    //! cos  -sin
    //! sin  +cos
    class Transform3
    {
    public:
        Transform3();

        Transform3(const Vector<double, 3> &translation, const Quaternion<double>& orientation);

        //! return translation
        const Vector<double, 3> &translation() const;

        void setTranslation(const Vector<double, 3> &translation);

        //! return orientation
        const Quaternion<double>& orientation() const;

        void setOrientation(const Quaternion<double>& orientation);

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
        Quaternion<double> _orientation;
        Matrix<double, 3, 3> _orientationMat3;
        Matrix<double, 3, 3> _invertOrientationMat3;
    };

}

#include "detail/transform3-inl.h"
#endif
