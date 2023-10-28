#ifndef INCLUDE_BIG_QUATERNION_INL_H_
#define INCLUDE_BIG_QUATERNION_INL_H_

namespace big
{

    template <typename T>
    Quaternion<T>::Quaternion()
    {
        setIdentity();
    }

    template <typename T>
    Quaternion<T>::Quaternion(T newW, T newX, T newY, T newZ)
    {
        set(newW, newX, newY, newZ);
    }

    template <typename T>
    Quaternion<T>::Quaternion(const std::initializer_list<T> &lst)
    {
        set(lst);
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Vector<T, 3> &axis, T angle)
    {
        set(axis, angle);
    }
    template <typename T>
    Quaternion<T>::Quaternion(const Vector<T, 3> &from, const Vector<T, 3> &to)
    {
        set(from, to);
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Vector<T, 3> &axis0, const Vector<T, 3> &axis1, const Vector<T, 3> &axis2)
    {
        set(axis0, axis1, axis2);
    }

    template <typename T>
    void Quaternion<T>::set(const Vector<T, 3> &axis0, const Vector<T, 3> &axis1, const Vector<T, 3> &axis2)
    {
        Matrix3x3<T> matrix3;
        matrix3.setColum(0, axis0.normalized());
        matrix3.setColum(1, axis1.normalized());
        matrix3.setColum(2, axis2.normalized());
        set(matrix3);
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Matrix3x3<T> &m33)
    {
        set(m33);
    }

    template <typename T>
    void Quaternion<T>::set(const Matrix3x3<T> &m33)
    {

    }

    template <typename T>
    void Quaternion<T>::set(const Vector<T, 3> &from, const Vector<T, 3> &to)
    {
        static const T eps = std::numeric_limits<T>::epsilon();

        Vector<T, 3> axis = from.cross(to);

        T fromLengthSquared = from.lengthSquared();
        T toLengthSquared = to.lengthSquared();
        // one is error. q can't be calculate.
        if (fromLengthSquared < eps || toLengthSquared < eps)
        {
            setIdentity();
        }
        else
        {
            T axisLengthSquared = axis.lengthSquared();
            // from = - to
            if (axisLengthSquared < eps)
            {
                axis = std::get<0>(from.tangential());
                set(0, axis.x, axis.y, axis.z);
            }
            else
            {
                set(from.dot(to), axis.x, axis.y, axis.z); // (a * b, a x b)
                normalize();                               // => (cos(\theta), sin(\theta) * \vec{e})          where \vec{e} is the unit vector of axis
                _w += 1;                                   // => (cos(\theta) + 1, sin * \vec{e})     =>      (2cos^2(\theta/2), 2sin(\theta/2)cos(\theta/2) * \vec{e})
                normalize();                               // => (cos(\theta / 2), sin(\theta / 2) * \vec{e})
            }
        }
    }

    template <typename T>
    void Quaternion<T>::normalize()
    {
        T norm = l2Norm();
        assert(norm != 0 && "Norm is 0!!!");
        set(_w / norm, _x / norm, _y / norm, _z / norm);
    }
    template <typename T>
    T Quaternion<T>::l2Norm() const
    {
        return std::sqrt(_w * _w + _x * _x + _y * _y + _z * _z);
    }

    template <typename T>
    void Quaternion<T>::set(const Vector<T, 3> &axis, T angle)
    {
        static const T eps = std::numeric_limits<T>::epsilon();

        T axisLengthSquared = axis.lengthSquared();

        if (axisLengthSquared < eps)
        {
            setIdentity();
        }
        else
        {
            Vector<T, 3> normalizedAxis = axis.normalized();
            T s = std::sin(angle / 2);
            _x = normalizedAxis.x * s;
            _y = normalizedAxis.y * s;
            _z = normalizedAxis.z * s;

            _w = std::cos(angle / 2);
        }
    }

    template <typename T>
    void Quaternion<T>::set(const std::initializer_list<T> &lst)
    {
        assert(lst.size() == 4 && "lst of Quaterion is invalid.");
        auto Elem = lst.begin();
        _w = *Elem;
        _x = *(++Elem);
        _y = *(++Elem);
        _z = *(++Elem);
    }

    template <typename T>
    void Quaternion<T>::set(T newW, T newX, T newY, T newZ)
    {
        _w = newW;
        _x = newX;
        _y = newY;
        _z = newZ;
    }

    template <typename T>
    void Quaternion<T>::show() const
    {
        std::cout << _w << " " << _x << " " << _y << " " << _z << std::endl;
    }

    template <typename T>
    void Quaternion<T>::setIdentity()
    {
        set(1, 0, 0, 0);
    }

}

#endif