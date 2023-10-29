#ifndef INCLUDE_BIG_QUATERNION_H_
#define INCLUDE_BIG_QUATERNION_H_

#include <matrix4x4.h>

namespace big
{
    //! \brief Quaternion class define as q = w + xi + yj+ zk

    template <typename T>
    class Quaternion
    {

    public:
        static_assert(std::is_floating_point<T>::value, "Quaternion only can be instantiated with floating point types.");

        T _w;
        T _x;
        T _y;
        T _z;

        Quaternion();

        Quaternion(T newW, T newX, T newY, T newZ);

        Quaternion(const std::initializer_list<T> &lst);

        Quaternion(const Vector<T, 3> &axis, T angle);

        Quaternion(const Vector<T, 3> &from, const Vector<T, 3> &to);

        Quaternion(const Vector<T, 3> &axis0, const Vector<T, 3> &axis1, const Vector<T, 3> &axis2);

        explicit Quaternion(const Matrix3x3<T> &m33);

        Quaternion(const Quaternion &other);

        void set(const Quaternion &other);

        void set(T newW, T newX, T newY, T newZ);

        void set(const std::initializer_list<T> &lst);

        void set(const Vector<T, 3> &axis, T angle);

        void set(const Vector<T, 3> &from, const Vector<T, 3> &to);

        //! \brief three basic vectors
        //! \details I don't know what this means?
        void set(const Vector<T, 3> &axis0, const Vector<T, 3> &axis1, const Vector<T, 3> &axis2);

        void set(const Matrix3x3<T> &m33);

        void show() const;

        template <typename U>
        Quaternion<U> castTo() const;

        Quaternion normalized() const;

        Vector<T, 3> mul(const Vector<T, 3> &v) const;

        Quaternion mul(const Quaternion &other) const;

        T dot(const Quaternion &other) const;

        Quaternion rmul(const Quaternion &other) const;

        void imul(const Quaternion &other);

        void setIdentity();

        void rotate(T angleInRadians);

        void normalize();

        Vector<T, 3> axis() const;

        T angle() const;

        void getAxisAngle(Vector<T, 3> *axis, T *angle) const;

        Quaternion inverse() const;

        Matrix<T, 3, 3>  matrix3() const;

        Matrix<T, 4, 4> matrix4() const;

        T l2Norm() const;

        Quaternion &operator=(const Quaternion &other);

        Quaternion &operator*=(const Quaternion &other);

        T &operator[](std::size_t i);

        T &operator[](std::size_t i) const;

        T &operator==(const Quaternion &other) const;

        T &operator!=(const Quaternion &other) const;

        static Quaternion makeIdentity();
    };

    //! \param a  unit quaternion
    //! \param b  unit quaternion
    //! \param t  interpolation param
    //! \param threshold default param in algorithm
    template <typename T>
    Quaternion<T> slerp(const Quaternion<T> &a, const Quaternion<T> &b, T t, double threshold=0.01);

    template <typename T>
    Vector<T, 3> operator*(const Quaternion<T> &a, const Vector<T, 3> &v);

    template <typename T>
    Vector<T, 3> operator*(const Quaternion<T> &a, const Quaternion<T> &b);

    typedef Quaternion<float> QuaternionF;

    typedef Quaternion<double> QuaternionD;
}

#include "detail/quaternion-inl.h"
#endif