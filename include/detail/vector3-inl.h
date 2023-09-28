#ifndef INCLUDE_BIG_VECTOR3_INL_H_
#define INCLUDE_BIG_VCETOR3_INL_H_
#include "math_utils.h"
namespace big
{

    template <typename T>
    template <typename U>
    Vector<T, 3>::Vector(const std::initializer_list<U> &lst)
    {
        set(lst);
    }

    template <typename T>
    void Vector<T, 3>::set(const Vector<T, 2> &other, T z_)
    {
        x = other.x;
        y = other.y;
        z = z_;
    }

    template <typename T>
    template <typename U>
    void Vector<T, 3>::set(const std::initializer_list<U> &lst)
    {
        assert(lst.size() == 3 && "the size of initializer_list is invalid.");
        auto first_ptr = lst.begin();
        x = static_cast<T>(*first_ptr);
        y = static_cast<T>(*(++first_ptr));
        z = static_cast<T>(*(++first_ptr));
    }

    template <typename T>
    void Vector<T, 3>::set(T newX, T newY, T newZ)
    {
        x = newX;
        y = newY;
        z = newZ;
    }

    template <typename T>
    void Vector<T, 3>::set(const Vector<T, 3> &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    template <typename T>
    void Vector<T, 3>::setZero()
    {
        x = y = z = static_cast<T>(0);
    }

    template <typename T>
    void Vector<T, 3>::normize()
    {
        idiv(length());
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::add(T val) const
    {
        return Vector(x + val, y + val, z + val);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::add(const Vector &other) const
    {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::sub(T val) const
    {
        return Vector(x - val, y - val, z - val);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::sub(const Vector &other) const
    {
        return Vector(x - other.x, y - other.y, z - other.z);
    }
    template <typename T>
    Vector<T, 3> Vector<T, 3>::mul(T val) const
    {
        // val = 1.0;
        return Vector(x * val, y * val, z * val);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::mul(const Vector<T, 3> &other) const
    {
        return Vector(x * other.x, y * other.y, z * other.z);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::div(T val) const
    {
        return Vector(x / val, y / val, z / val);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::div(const Vector<T, 3> &other) const
    {
        return Vector(x / other.x, y / other.y, z / other.z);
    }

    template <typename T>
    T Vector<T, 3>::dot(const Vector &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }
    template <typename T>
    Vector<T, 3> Vector<T, 3>::cross(const Vector &other) const
    {
        return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }
    template <typename T>
    Vector<T, 3> Vector<T, 3>::rcross(const Vector &other) const
    {
        return Vector(z * other.y - y * other.z, x * other.z - z * other.x, y * other.x - x * other.y);
    }

    template <typename T>
    T Vector<T, 3>::length() const
    {
        return std::sqrt(lengthSquared());
    }

    template <typename T>
    T Vector<T, 3>::lengthSquared() const
    {
        return x * x + y * y + z * z;
    }
    template <typename T>
    Vector<T, 3> Vector<T, 3>::rsub(T val) const
    {
        return Vector(val - x, val - y, val - z);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::rsub(T &&val) const
    {
        return Vector(val - x, val - y, val - z);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::rsub(const Vector<T, 3> &other) const
    {
        return Vector(other.x - x, other.y - y, other.z - z);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::rdiv(T &val) const
    {
        return Vector(val / x, val / y, val / z);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::rdiv(const Vector<T, 3> &other) const
    {
        return Vector(other.x / x, other.y / y), other.z / z;
    }

    template <typename T>
    void Vector<T, 3>::iadd(T &val)
    {
        x += val;
        y += val;
        z += val;
    }

    template <typename T>
    void Vector<T, 3>::iadd(const Vector &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    template <typename T>
    void Vector<T, 3>::isub(T &val)
    {
        x -= val;
        y -= val;
        z -= val;
    }

    template <typename T>
    void Vector<T, 3>::isub(const Vector &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    template <typename T>
    void Vector<T, 3>::imul(T &val)
    {
        x *= val;
        y *= val;
        z *= val;
    }

    template <typename T>
    void Vector<T, 3>::imul(const Vector &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

    template <typename T>
    void Vector<T, 3>::idiv(T &val)
    {
        x /= val;
        y /= val;
        z /= val;
    }

    template <typename T>
    void Vector<T, 3>::idiv(const Vector &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }
    template <typename T>
    T &Vector<T, 3>::at(std::size_t i)
    {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    const T &Vector<T, 3>::at(std::size_t i) const
    {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    T Vector<T, 3>::sum() const
    {
        return x + y + z;
    }

    template <typename T>
    T Vector<T, 3>::avg() const
    {
        return (x + y + z) / 3;
    }

    template <typename T>
    T Vector<T, 3>::min() const
    {
        return std::min(std::min(x, y), z);
    }
    template <typename T>
    T Vector<T, 3>::max() const
    {
        return std::max(std::max(x, y), z);
    }

    template <typename T>
    T Vector<T, 3>::absmin() const
    {
        return big::absmin(x, y, z);
    }

    template <typename T>
    T Vector<T, 3>::absmax() const
    {
        return big::absmax(x, y, z);
    }

    template <typename T>
    std::size_t Vector<T, 3>::domintAxis() const
    {
        return (std::abs(x) > std::abs(y)) ? (std::abs(x) > std::abs(z) ? 0 : 2) : (std::abs(y) > std::abs(z) ? 1 : 2);
    }

    template <typename T>
    std::size_t Vector<T, 3>::subminanAxis() const
    {
        return (std::abs(x) < std::abs(y)) ? (std::abs(x) < std::abs(z) ? 0 : 2) : (std::abs(y) < std::abs(z) ? 1 : 2);
    }

    template <typename T>
    Vector<T, 3> Vector<T, 3>::normalized() const
    {
        return div(length());
    }

    template <typename T>
    T Vector<T, 3>::distanceTo(const Vector &other) const
    {
        return sub(other).length()
    }

    template <typename T>
    T Vector<T, 3>::distanceSquaredTo(const Vector &other) const
    {
        return sub(other).lengthSquared();
    }
    template <typename T>
    Vector<T, 3> Vector<T, 3>::reflect(const Vector &normal) const
    { // this - ( 2 * this * n ) n
        return sub(normal.mul(2 * dot(normal)));
    }
    template <typename T>
    Vector<T, 3> Vector<T, 3>::project(const Vector &normal) const
    {
        return sub(normal.mul(dot(normal)));
    }
    template <typename T>
    Vector<T, 3> Vector<T, 3>::tangential() const
    {
        // return Vector<T, 3>(-y, x);
    }

    template <typename T>
    template <typename U>
    Vector<U, 3> Vector<T, 3>::castTo() const
    {
        return Vector<U, 3>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
    }

    template <typename T>
    constexpr bool Vector<T, 3>::isEqual(const Vector &other) const
    {
        return (x == other.x) && (y == other.y) && (z = other.z);
    }

    template <typename T>
    constexpr bool Vector<T, 3>::isSimilar(const Vector &other, T epsilon) const
    {
        return (std::abs(x - other.x) < epsilon) &&
               (std::abs(y - other.y) < epsilon) &&
               (std::abs(z - other.z) < epsilon);
    }

    template <typename T>
    T &Vector<T, 3>::operator[](T i)
    {
        assert(i < 3);
        return (&x)[i];
    }
    template <typename T>
    const T &Vector<T, 3>::operator[](T i) const
    {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    Vector<T, 3> &Vector<T, 3>::operator=(const Vector &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    template <typename U>
    Vector<T, 3> &Vector<T, 3>::operator=(std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }

    template <typename T>
    Vector<T, 3> &Vector<T, 3>::operator+=(T &val)
    {
        iadd(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 3> &Vector<T, 3>::operator+=(const Vector &other)
    {
        iadd(other);
        return (*this);
    }

    template <typename T>
    Vector<T, 3> &Vector<T, 3>::operator-=(T &val)
    {
        isub(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 3> &Vector<T, 3>::operator-=(const Vector &other)
    {
        isub(other);
        return (*this);
    }

    template <typename T>
    Vector<T, 3> &Vector<T, 3>::operator*=(T &val)
    {
        imul(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 3> &Vector<T, 3>::operator*=(const Vector &other)
    {
        imul(other);
        return (*this);
    }

    template <typename T>
    Vector<T, 3> &Vector<T, 3>::operator/=(T &val)
    {
        idiv(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 3> &Vector<T, 3>::operator/=(const Vector &other)
    {
        idiv(other);
        return (*this);
    }

    template <typename T>
    bool Vector<T, 3>::operator==(const Vector &other) const
    {
        return isEqual(other);
    }

    template <typename T>
    bool Vector<T, 3>::operator!=(const Vector &other) const
    {
        return !isEqual(other);
    }

    template <typename T>
    Vector<T, 3> operator+(const Vector<T, 3> &other1, const Vector<T, 3> &other2)
    {
        return other1.add(other2);
    }

    template <typename T>
    Vector<T, 3> operator+(T val, const Vector<T, 3> &other)
    {
        return other.add(val);
    }

    template <typename T>
    Vector<T, 3> operator+(const Vector<T, 3> &other, T val)
    {
        return other.add(val);
    }

    template <typename T>
    Vector<T, 3> operator+(const Vector<T, 3> &other)
    {
        return other;
    }

    template <typename T>
    Vector<T, 3> operator-(const Vector<T, 3> &other1, const Vector<T, 3> &other2)
    {
        return other1.sub(other2);
    }

    template <typename T>
    Vector<T, 3> operator-(T val, const Vector<T, 3> &other)
    {
        return other.rsub(val);
    }

    template <typename T>
    Vector<T, 3> operator-(const Vector<T, 3> &other, T val)
    {
        return other.sub(val);
    }

    template <typename T>
    Vector<T, 3> operator-(const Vector<T, 3> &other)
    {
        return other.rsub(0);
    }

    template <typename T>
    Vector<T, 3> operator*(const Vector<T, 3> &other1, const Vector<T, 3> &other2)
    {
        return other1.mul(other2);
    }

    template <typename T>
    Vector<T, 3> operator*(T val, const Vector<T, 3> &other)
    {
        return other.mul(val);
    }

    template <typename T>
    Vector<T, 3> operator*(const Vector<T, 3> &other, T val)
    {
        return other.mul(val);
    }

    template <typename T>
    Vector<T, 3> operator/(const Vector<T, 3> &other1, const Vector<T, 3> &other2)
    {
        return other1.div(other2);
    }

    template <typename T>
    Vector<T, 3> operator/(T val, const Vector<T, 3> &other)
    {
        return other.rdiv(val);
    }

    template <typename T>
    Vector<T, 3> operator/(const Vector<T, 3> &other, T val)
    {
        return other.div(val);
    }
    template <typename T>
    Vector<T, 3> min(const Vector<T, 3> &other1, const Vector<T, 3> &other2)
    {
        return Vector<T, 3>(std::min(other1.x, other2.x), std::min(other1.y, other2.y), std::min(other1.z, other2.z));
    }
    template <typename T>
    Vector<T, 3> max(const Vector<T, 3> &other1, const Vector<T, 3> &other2)
    {
        return Vector<T, 3>(std::max(other1.x, other2.x), std::max(other1.y, other2.y), std::max(other1.z, other2.z));
    }
    template <typename T>
    Vector<T, 3> clamp(const Vector<T, 3> &s, const Vector<T, 3> &low, const Vector<T, 3> &high)
    {
        return Vector<T, 3>(std::clamp(s.x, low.x, high.x), std::clamp(s.y, low.y, high.y), std::clamp(s.z, low.z, high.z));
    }
    template <typename T>
    Vector<T, 3> ceil(const Vector<T, 3> &other)
    {
        return Vector<T, 3>(std::ceil(other.x), std::ceil(other.y), std::ceil(other.z));
    }
    template <typename T>
    Vector<T, 3> floor(const Vector<T, 3> &other)
    {
        return Vector<T, 3>(std::floor(other.x), std::floor(other.y), std::floor(other.z));
    }
    template <typename T>
    Vector<T, 3> CatmullRom(const Vector<T, 3> &v0, const Vector<T, 3> &v1,
                            const Vector<T, 3> &v2, const Vector<T, 3> &v3, T f)
    {
        static const T two = static_cast<T>(2);
        static const T three = static_cast<T>(3);

        Vector<T, 3> d1 = (v2 - v0) / two;
        Vector<T, 3> d2 = (v3 - v1) / two;
        Vector<T, 3> D1 = v2 - v1;

        Vector<T, 3> a3 = d1 - two * D1, + d2;
        Vector<T, 3> a2 = - two * d1 + three * D1 - d2;
        Vector<T ,3> a1 = d1;
        Vector<T, 3> a0 = v1;

        return a3 * cubic(f) + a2 * square(f) + a1 * f + a0;
    }
}
#endif
