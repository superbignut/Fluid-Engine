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
        // Matrix3x3<T> matrix3;
        // matrix3.setColum(0, axis0.normalized());
        // matrix3.setColum(1, axis1.normalized());
        // matrix3.setColum(2, axis2.normalized());
        // set(matrix3);
    }

    template <typename T>
    Quaternion<T>::Quaternion(const Matrix3x3<T> &m33)
    {
        set(m33);
    }
    template <typename T>
    Quaternion<T>::Quaternion(const Quaternion &other)
        : _w(other._w), _x(other._x), _y(other._y), _z(other._z)
    {
    }

    template <typename T>
    void Quaternion<T>::set(const Quaternion &other)
    {
        _w = other._w;
        _x = other._x;
        _y = other._y;
        _z = other._z;
    }
    template <typename T>
    void Quaternion<T>::set(const Matrix3x3<T> &m33)
    {
        static const T eps = std::numeric_limits<T>::epsilon();
        static const T quater = static_cast<T>(0.25);

        T onePlusTrace = m33.trace() + 1; // 4cos^2(\theta / 2)

        if (onePlusTrace > eps) // \theta != \pi
        {
            T S = std::sqrt(onePlusTrace) * 2; // 4 cos(\theta / 2) , cos(\theta / 2) > 0

            _w = S * quater;                  // cos(\theta / 2)
            _x = (m33(2, 1) - m33(1, 2)) / S; // sin(\theta / 2) * u_x
            _y = (m33(0, 2) - m33(2, 0)) / S;
            _z = (m33(1, 0) - m33(0, 1)) / S;
        }
        else if (m33(0, 0) > m33(1, 1) && m33(0, 0) > m33(2, 2)) // max|u_x, u_y , u_z| = |u_x|
        {
            T S = std::sqrt(m33(0, 0) - m33(1, 1) - m33(2, 2) + 1) * 2; // 4|u_x|
            _w = 0.0;
            _x = S * quater;                  // |u_x|
            _y = (m33(1, 0) + m33(0, 1)) / S; // u_x * u_y / |u_x|
            _z = (m33(2, 0) + m33(0, 2)) / S; // u_x * u_z / |u_x|
        }
        else if (m33(1, 1) > m33(2, 2)) // max|x, y , z| = |y|
        {
            T S = std::sqrt(m33(1, 1) - m33(0, 0) - m33(2, 2) + 1) * 2; // 4|u_y|
            _w = 0.0;
            _x = (m33(1, 0) + m33(0, 1)) / S; // u_x * u_y / |u_y|
            _y = S * quater;                  // |u_y|
            _z = (m33(2, 1) + m33(1, 2)) / S; // u_y * u_z / |u_y|
        }
        else // max|x, y , z| = |z|
        {
            T S = std::sqrt(m33(2, 2) - m33(1, 1) - m33(0, 0) + 1) * 2; // 4|u_z|
            _w = 0.0;
            _x = (m33(2, 0) + m33(0, 2)) / S; // u_z * u_x / |u_z|
            _y = (m33(2, 1) + m33(1, 2)) / S;
            _z = S * quater; // |u_z|
        }
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
                axis = std::get<0>(from.tangential()).normalized();
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
    Quaternion<T> Quaternion<T>::normalized() const
    {
        Quaternion temp(*this);
        temp.normalize();
        return temp;
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
    template <typename U>
    Quaternion<U> Quaternion<T>::castTo() const
    {
        return Quaternion<U>(
            static_cast<U>(_w),
            static_cast<U>(_x),
            static_cast<U>(_y),
            static_cast<U>(_z));
    }
    template <typename T>
    Vector<T, 3> Quaternion<T>::mul(const Vector<T, 3> &v) const
    {
        T _2xx = 2 * _x * _x;
        T _2yy = 2 * _y * _y;
        T _2zz = 2 * _z * _z;
        T _2wx = 2 * _w * _x;
        T _2wy = 2 * _w * _y;
        T _2wz = 2 * _w * _z;
        T _2xy = 2 * _x * _y;
        T _2xz = 2 * _x * _z;
        T _2yz = 2 * _y * _z;

        return Vector<T, 3>((1 - _2yy - _2zz) * v[0] + (_2xy - _2wz) * v[1] + (_2wy + _2xz) * v[2],
                            (_2xy + _2wz) * v[0] + (1 - _2xx - _2zz) * v[1] + (_2yz - _2wx) * v[2],
                            (_2xz - _2wy) * v[0] + (_2wx + _2yz) * v[1] + (1 - _2xx - _2yy) * v[2]);
    }
    template <typename T>
    Quaternion<T> Quaternion<T>::mul(const Quaternion &other) const
    {
        Vector<T, 3> v(_x, _y, _z);
        Vector<T, 3> other_v(other._x, other._y, other._z);

        T Q_a = _w * other._w - v.dot(other_v);

        Vector<T, 3> Q_v = _w * other_v + other._w * v + v.cross(other_v);

        return Quaternion(Q_a, Q_v.x, Q_v.y, Q_v.z);
    }
    template <typename T>
    T Quaternion<T>::dot(const Quaternion &other) const
    {
        return Quaternion(_w * other._w, _x * other._x, _y * other._y, _z * other._z);
    }
    template <typename T>
    Quaternion<T> Quaternion<T>::rmul(const Quaternion &other) const
    {
        return other.mul(*this);
    }
    template <typename T>
    void Quaternion<T>::imul(const Quaternion &other)
    {
        set(mul(other));
    }

    template <typename T>
    void Quaternion<T>::setIdentity()
    {
        set(1, 0, 0, 0);
    }
    template <typename T>
    void Quaternion<T>::rotate(T angleInRadians)
    {
        // Quaternion temp(Vector<T, 3>(_x, _y, _z), angleInRadians);
        // imul(temp);
    }

    template <typename T>
    Vector<T, 3> Quaternion<T>::axis() const
    {
        Vector<T, 3> temp(_x, _y, _z);
        temp.normalize();
        T angle = 2 * std::acos(temp._w);
        if (angle < pi<T>())
        {
            return temp;
        }
        else
        {
            return -temp;
        }
    }

    template <typename T>
    T Quaternion<T>::angle() const
    {
        Vector<T, 3> temp(_x, _y, _z);
        temp.normalize();
        T angle = 2 * std::acos(temp._w);
        if (angle < pi<T>())
        {
            return angle;
        }
        else
        {
            return 2 * pi<T>() - angle;
        }
    }
    template <typename T>
    void Quaternion<T>::getAxisAngle(Vector<T, 3> *axis, T *angle) const
    {
        Vector<T, 3> temp(_x, _y, _z);
        temp.normalize();
        *angle = 2 * std::acos(temp._w);
        if (angle < pi<T>())
        {
            *axis = temp;
        }
        else
        {
            *axis = -temp;
            *angle = 2 * pi<T>() - angle;
        }
    }
    template <typename T>
    Quaternion<T> Quaternion<T>::inverse() const
    {
        T norm2 = _w * _w + _x * _x + _y * _y + _z * _z;
        return Quaternion(_w / norm2, -_x / norm2, -_y / norm2, _z / norm2);
    }
    template <typename T>
    Matrix<T, 3, 3> Quaternion<T>::matrix3() const
    {
        T _2xx = 2 * _x * _x;
        T _2yy = 2 * _y * _y;
        T _2zz = 2 * _z * _z;
        T _2wx = 2 * _w * _x;
        T _2wy = 2 * _w * _y;
        T _2wz = 2 * _w * _z;
        T _2xy = 2 * _x * _y;
        T _2xz = 2 * _x * _z;
        T _2yz = 2 * _y * _z;

        return Matrix<T, 3, 3>(1 - _2yy - _2zz, _2xy - _2wz, _2wy + _2xz,
                               _2xy + _2wz, 1 - _2xx - _2zz, _2yz - _2wx,
                               _2xz - _2wy, _2wx + _2yz, 1 - _2xx - _2yy);
    }
    template <typename T>
    Matrix<T, 4, 4> Quaternion<T>::matrix4() const
    {
        T _2xx = 2 * _x * _x;
        T _2yy = 2 * _y * _y;
        T _2zz = 2 * _z * _z;
        T _2wx = 2 * _w * _x;
        T _2wy = 2 * _w * _y;
        T _2wz = 2 * _w * _z;
        T _2xy = 2 * _x * _y;
        T _2xz = 2 * _x * _z;
        T _2yz = 2 * _y * _z;

        return Matrix<T, 4, 4>(1, 0, 0, 0,
                               0, 1 - _2yy - _2zz, _2xy - _2wz, _2wy + _2xz,
                               0, _2xy + _2wz, 1 - _2xx - _2zz, _2yz - _2wx,
                               0, _2xz - _2wy, _2wx + _2yz, 1 - _2xx - _2yy);
    }

    template <typename T>
    Quaternion<T> &Quaternion<T>::operator=(const Quaternion &other)
    {
        set(other);
        return (*this);
    }
    template <typename T>
    Quaternion<T> &Quaternion<T>::operator*=(const Quaternion &other)
    {
        imul(other);
        return this;
    }
    template <typename T>
    T &Quaternion<T>::operator[](std::size_t i)
    {
        return (&_w)[i];
    }
    template <typename T>
    T &Quaternion<T>::operator[](std::size_t i) const
    {
        return (&_w)[i];
    }
    template <typename T>
    T &Quaternion<T>::operator==(const Quaternion &other) const
    {
        return (_w == other._w && _x == other._x && _y == other._y && _z == other._z);
    }
    template <typename T>
    T &Quaternion<T>::operator!=(const Quaternion &other) const
    {
        return (_w != other._w || _x != other._x || _y != other._y || _z != other._z);
    }
    template <typename T>
    Quaternion<T> Quaternion<T>::makeIdentity()
    {
        return Quaternion(1, 0, 0, 0);
    }

    template <typename T>
    Quaternion<T> slerp(const Quaternion<T> &a, const Quaternion<T> &b, T t, double threshold)
    {
        // static const double threshold = 0.01;
        static const T eps = std::numeric_limits<T>::epsilon();

        T cosHalfAngle = dot(a, b);
        T weightA, weightB;

        if (1 - std::fabs(cosHalfAngle) < threshold)
        {
            weightA = 1.0 - t;
            weightB = t;
        }
        else
        {
            T halfAngle = std::acos(cosHalfAngle);
            T sinHalfAngle = std::sin(halfAngle);

            weightA = std::sin((1 - t) * halfAngle) / sinHalfAngle;
            weightB = std::sin(t * halfAngle) / sinHalfAngle;
        }
        return Quaternion(weightA * a._w + weightB * b._w,
                          weightA * a._x + weightB * b._x,
                          weightA * a._y + weightB * b._y,
                          weightA * a._z + weightB * b._z);
    }

    template <typename T>
    Vector<T, 3> operator*(const Quaternion<T> &a, const Vector<T, 3> &v)
    {
        return a.mul(v);
    }

    template <typename T>
    Vector<T, 3> operator*(const Quaternion<T> &a, const Quaternion<T> &b)
    {
        return a.mul(b);
    }
}

#endif