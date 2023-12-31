#ifndef INCLUDE_BIG_TRANSFORM3_INL_H_
#define INCLUDE_BIG_TRANSFORM3_INL_H_
namespace big
{
    inline Transform3::Transform3()
        : _translation(), _orientation(), _orientationMat3(), _invertOrientationMat3()
    {
        _orientationMat3 = _orientation.matrix3();
        _invertOrientationMat3 = _orientation.inverse().matrix3();
    }

    inline Transform3::Transform3(const Vector<double, 3> &translation, const Quaternion<double> &orientation)
        : _translation(translation), _orientation(orientation)
    {
        _orientationMat3 = orientation.matrix3();
        _invertOrientationMat3 = orientation.inverse().matrix3();
    }

    inline const Vector<double, 3> &Transform3::translation() const
    {
        return _translation;
    }

    inline void Transform3::setTranslation(const Vector<double, 3> &translation)
    {
        _translation = translation;
    }

    //! return orientation
    inline const Quaternion<double> &Transform3::orientation() const
    {
        return _orientation;
    }

    inline void Transform3::setOrientation(const Quaternion<double> &orientation)
    {
        _orientation = orientation;
        _orientationMat3 = orientation.matrix3();
        _invertOrientationMat3 = orientation.inverse().matrix3();
    }

    inline Vector3D Transform3::toLocal(const Vector3D &pointInWorld) const
    {
        Vector3D xmt = pointInWorld - _translation;
        return _invertOrientationMat3 * xmt;
    }

    inline Vector3D Transform3::toLocalDirection(const Vector3D &dirInWorld) const
    {
        return _invertOrientationMat3 * dirInWorld;
    }

    inline Ray3D Transform3::toLocal(const Ray3D &rayInWorld) const
    {
        return Ray3D(toLocal(rayInWorld.origin), toLocalDirection(rayInWorld.direction));
    }

    inline BoundingBox3D Transform3::toLocal(const BoundingBox3D &bboxInWorld) const
    {
        BoundingBox3D bboxInLocal;
        for (std::size_t i = 0; i < 8; ++i)
        {
            auto cornerInLocal = toLocal(bboxInWorld.corner(i));
            bboxInLocal.lowerCorner = ::big::min(bboxInLocal.lowerCorner, cornerInLocal);
            bboxInLocal.upperCorner = ::big::max(bboxInLocal.upperCorner, cornerInLocal);
        }
        return bboxInLocal;
    }

    inline Vector3D Transform3::toWorld(const Vector3D &pointInLocal) const
    {
        return (_orientationMat3 * pointInLocal + _translation);
    }

    inline Vector3D Transform3::toWorldDirection(const Vector3D &dirInLocal) const
    {
        return (_orientationMat3 * dirInLocal);
    }

    inline Ray3D Transform3::toWorld(const Ray3D &rayInLocal) const
    {
        Vector<double, 3> origin_new = _orientationMat3 * rayInLocal.origin + _translation;

        Vector<double, 3> direction_new = _orientationMat3 * rayInLocal.direction;

        return Ray3D(origin_new, direction_new);
    }

    inline BoundingBox3D Transform3::toWorld(const BoundingBox3D &bboxInLocal) const
    {
        BoundingBox3D bboxInworld;
        for (std::size_t i = 0; i < 8; ++i)
        {
            auto cornerInworld = toWorld(bboxInLocal.corner(i));
            bboxInworld.lowerCorner = ::big::min(bboxInworld.lowerCorner, cornerInworld);
            bboxInworld.upperCorner = ::big::max(bboxInworld.upperCorner, cornerInworld);
        }
        return bboxInworld;
    }

}

#endif