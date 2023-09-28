#ifndef INCLUDE_BIG_VECTOR4_INL_H_
#define INCLUDE_BIG_VCETOR4_INL_H_
#include "math_utils.h"
namespace big
{

    template <typename T>
    template <typename U>
    Vector<T, 4>::Vector(const std::initializer_list<U> &lst)
    {
        set(lst);
    }

    template <typename T>
    void Vector<T, 4>::set(const Vector<T, 3> &other, T w_)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = w_;
    }

    template <typename T>
    template <typename U>
    void Vector<T, 4>::set(const std::initializer_list<U> &lst)
    {
        assert(lst.size() == 4 && "the size of initializer_list is invalid.");
        auto first_ptr = lst.begin();
        x = static_cast<T>(*first_ptr);
        y = static_cast<T>(*(++first_ptr));
        z = static_cast<T>(*(++first_ptr));
    }

    template <typename T>
    void Vector<T, 4>::set(T newX, T newY, T newZ, T newW)
    {
        x = newX;
        y = newY;
        z = newZ;
        w = newW;
    }

    template <typename T>
    void Vector<T, 4>::set(const Vector<T, 4> &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }

    template <typename T>
    void Vector<T, 4>::setZero()
    {
        x = y = z = w = static_cast<T>(0);
    }

    template <typename T>
    void Vector<T, 4>::normize()
    {
        idiv(length());
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::add(T val) const
    {
        return Vector(x + val, y + val, z + val, w + val);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::add(const Vector &other) const
    {
        return Vector(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::sub(T val) const
    {
        return Vector(x - val, y - val, z - val, w - val);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::sub(const Vector &other) const
    {
        return Vector(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    template <typename T>
    Vector<T, 4> Vector<T, 4>::mul(T val) const
    {
        // val = 1.0;
        return Vector(x * val, y * val, z * val, w * val);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::mul(const Vector<T, 4> &other) const
    {
        return Vector(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::div(T val) const
    {
        return Vector(x / val, y / val, z / val, w / val);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::div(const Vector<T, 4> &other) const
    {
        return Vector(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    template <typename T>
    T Vector<T, 4>::dot(const Vector &other) const
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    // template <typename T>
    // Vector<T, 4> Vector<T, 4>::cross(const Vector &other) const
    // {
    //     return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    // }
    // template <typename T>
    // Vector<T, 4> Vector<T, 4>::rcross(const Vector &other) const
    // {
    // return Vector(z * other.y - y * other.z, x * other.z - z * other.x, y * other.x - x * other.y);
    // }

    template <typename T>
    T Vector<T, 4>::length() const
    {
        return std::sqrt(lengthSquared());
    }

    template <typename T>
    T Vector<T, 4>::lengthSquared() const
    {
        return x * x + y * y + z * z + w * w;
    }
    template <typename T>
    Vector<T, 4> Vector<T, 4>::rsub(T val) const
    {
        return Vector(val - x, val - y, val - z, val - w);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::rsub(T &&val) const
    {
        return Vector(val - x, val - y, val - z, val - w);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::rsub(const Vector<T, 4> &other) const
    {
        return Vector(other.x - x, other.y - y, other.z - z, other.w - w);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::rdiv(T &val) const
    {
        return Vector(val / x, val / y, val / z, val / w);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::rdiv(const Vector<T, 4> &other) const
    {
        return Vector(other.x / x, other.y / y, other.z / z, other.w / w);
    }

    template <typename T>
    void Vector<T, 4>::iadd(T &val)
    {
        x += val;
        y += val;
        z += val;
        w += val;
    }

    template <typename T>
    void Vector<T, 4>::iadd(const Vector &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
    }

    template <typename T>
    void Vector<T, 4>::isub(T &val)
    {
        x -= val;
        y -= val;
        z -= val;
        w -= val;
    }

    template <typename T>
    void Vector<T, 4>::isub(const Vector &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
    }

    template <typename T>
    void Vector<T, 4>::imul(T &val)
    {
        x *= val;
        y *= val;
        z *= val;
        w *= val;
    }

    template <typename T>
    void Vector<T, 4>::imul(const Vector &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
    }

    template <typename T>
    void Vector<T, 4>::idiv(T &val)
    {
        x /= val;
        y /= val;
        z /= val;
        w /= val;
    }

    template <typename T>
    void Vector<T, 4>::idiv(const Vector &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
    }
    template <typename T>
    T &Vector<T, 4>::at(std::size_t i)
    {
        assert(i < 4);
        return (&x)[i];
    }

    template <typename T>
    const T &Vector<T, 4>::at(std::size_t i) const
    {
        assert(i < 4);
        return (&x)[i];
    }

    template <typename T>
    T Vector<T, 4>::sum() const
    {
        return x + y + z + w;
    }

    template <typename T>
    T Vector<T, 4>::avg() const
    {
        return (x + y + z + w) / 4;
    }

    template <typename T>
    T Vector<T, 4>::min() const
    {
        return stdstd::min(std::min(x, y), std::min(w, z));
    }
    template <typename T>
    T Vector<T, 4>::max() const
    {
        return std::max(std::max(x, y), std::max(z, w));
    }

    template <typename T>
    T Vector<T, 4>::absmin() const
    {
        return big::absmin(big::absmin(x, y), big::absmin(z, w));
    }

    template <typename T>
    T Vector<T, 4>::absmax() const
    {
        return big::absmax(big::absmax(x, y), big::absmax(z, w));
    }

    template <typename T>
    std::size_t Vector<T, 4>::domintAxis() const
    {
        return (std::abs(x) > std::abs(y))
                   ? (std::abs(x) > std::abs(z)
                        ? (std::abs(x) > std::abs(w) ? 0 : 3)
                        : (std::abs(z)) > std::abs(w) ? 2 : 3)
                   : (std::abs(y) > std::abs(z)
                        ? (std::abs(y) > std::abs(w) ? 1 : 3)
                        : (std::abs(z)) > std::abs(w) ? 2 : 3);
    }
    template <typename T>
    std::size_t Vector<T, 4>::subminanAxis() const
    {
        return (std::abs(x) < std::abs(y))
                   ? (std::abs(x) < std::abs(z)
                        ? (std::abs(x) < std::abs(w) ? 0 : 3)
                        : (std::abs(z)) < std::abs(w) ? 2 : 3)
                   : (std::abs(y) < std::abs(z)
                        ? (std::abs(y) < std::abs(w) ? 1 : 3)
                        : (std::abs(z)) < std::abs(w) ? 2 : 3);
    }

    template <typename T>
    Vector<T, 4> Vector<T, 4>::normalized() const
    {
        return div(length());
    }

    template <typename T>
    T Vector<T, 4>::distanceTo(const Vector &other) const
    {
        return sub(other).length()
    }

    template <typename T>
    T Vector<T, 4>::distanceSquaredTo(const Vector &other) const
    {
        return sub(other).lengthSquared();
    }
    // template <typename T>
    // Vector<T, 4> Vector<T, 4>::reflect(const Vector &normal) const
    // { // this - ( 2 * this * n ) n
    //     return sub(normal.mul(2 * dot(normal)));
    // }
    // template <typename T>
    // Vector<T, 4> Vector<T, 4>::project(const Vector &normal) const
    // {
    //     return sub(normal.mul(dot(normal)));
    // }
    // template <typename T>
    // Vector<T, 4> Vector<T, 4>::tangential() const
    // {
    //     // return Vector<T, 4>(-y, x);
    // }

    template <typename T>
    template <typename U>
    Vector<U, 4> Vector<T, 4>::castTo() const
    {
        return Vector<U, 4>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z), static_cast<U>(W));
    }

    template <typename T>
    constexpr bool Vector<T, 4>::isEqual(const Vector &other) const
    {
        return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
    }

    template <typename T>
    constexpr bool Vector<T, 4>::isSimilar(const Vector &other, T epsilon) const
    {
        return (std::abs(x - other.x) < epsilon) &&
               (std::abs(y - other.y) < epsilon) &&
               (std::abs(z - other.z) < epsilon) &&
               (std::abs(w - other.w) < epsilon);
    }

    template <typename T>
    T &Vector<T, 4>::operator[](T i)
    {
        assert(i < 4);
        return (&x)[i];
    }
    template <typename T>
    const T &Vector<T, 4>::operator[](T i) const
    {
        assert(i < 4);
        return (&x)[i];
    }

    template <typename T>
    Vector<T, 4> &Vector<T, 4>::operator=(const Vector &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    template <typename U>
    Vector<T, 4> &Vector<T, 4>::operator=(std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }

    template <typename T>
    Vector<T, 4> &Vector<T, 4>::operator+=(T &val)
    {
        iadd(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 4> &Vector<T, 4>::operator+=(const Vector &other)
    {
        iadd(other);
        return (*this);
    }

    template <typename T>
    Vector<T, 4> &Vector<T, 4>::operator-=(T &val)
    {
        isub(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 4> &Vector<T, 4>::operator-=(const Vector &other)
    {
        isub(other);
        return (*this);
    }

    template <typename T>
    Vector<T, 4> &Vector<T, 4>::operator*=(T &val)
    {
        imul(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 4> &Vector<T, 4>::operator*=(const Vector &other)
    {
        imul(other);
        return (*this);
    }

    template <typename T>
    Vector<T, 4> &Vector<T, 4>::operator/=(T &val)
    {
        idiv(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 4> &Vector<T, 4>::operator/=(const Vector &other)
    {
        idiv(other);
        return (*this);
    }

    template <typename T>
    bool Vector<T, 4>::operator==(const Vector &other) const
    {
        return isEqual(other);
    }

    template <typename T>
    bool Vector<T, 4>::operator!=(const Vector &other) const
    {
        return !isEqual(other);
    }

    template <typename T>
    Vector<T, 4> operator+(const Vector<T, 4> &other1, const Vector<T, 4> &other2)
    {
        return other1.add(other2);
    }

    template <typename T>
    Vector<T, 4> operator+(T val, const Vector<T, 4> &other)
    {
        return other.add(val);
    }

    template <typename T>
    Vector<T, 4> operator+(const Vector<T, 4> &other, T val)
    {
        return other.add(val);
    }

    template <typename T>
    Vector<T, 4> operator+(const Vector<T, 4> &other)
    {
        return other;
    }

    template <typename T>
    Vector<T, 4> operator-(const Vector<T, 4> &other1, const Vector<T, 4> &other2)
    {
        return other1.sub(other2);
    }

    template <typename T>
    Vector<T, 4> operator-(T val, const Vector<T, 4> &other)
    {
        return other.rsub(val);
    }

    template <typename T>
    Vector<T, 4> operator-(const Vector<T, 4> &other, T val)
    {
        return other.sub(val);
    }

    template <typename T>
    Vector<T, 4> operator-(const Vector<T, 4> &other)
    {
        return other.rsub(0);
    }

    template <typename T>
    Vector<T, 4> operator*(const Vector<T, 4> &other1, const Vector<T, 4> &other2)
    {
        return other1.mul(other2);
    }

    template <typename T>
    Vector<T, 4> operator*(T val, const Vector<T, 4> &other)
    {
        return other.mul(val);
    }

    template <typename T>
    Vector<T, 4> operator*(const Vector<T, 4> &other, T val)
    {
        return other.mul(val);
    }

    template <typename T>
    Vector<T, 4> operator/(const Vector<T, 4> &other1, const Vector<T, 4> &other2)
    {
        return other1.div(other2);
    }

    template <typename T>
    Vector<T, 4> operator/(T val, const Vector<T, 4> &other)
    {
        return other.rdiv(val);
    }

    template <typename T>
    Vector<T, 4> operator/(const Vector<T, 4> &other, T val)
    {
        return other.div(val);
    }
    template <typename T>
    Vector<T, 4> min(const Vector<T, 4> &other1, const Vector<T, 4> &other2)
    {
        return Vector<T, 4>(std::min(other1.x, other2.x), std::min(other1.y, other2.y), std::min(other1.z, other2.z), std::min(other1.w, other2.w));
    }
    template <typename T>
    Vector<T, 4> max(const Vector<T, 4> &other1, const Vector<T, 4> &other2)
    {
        return Vector<T, 4>(std::max(other1.x, other2.x), std::max(other1.y, other2.y), std::max(other1.z, other2.z), std::max(other1.w, other2.w));
    }
    template <typename T>
    Vector<T, 4> clamp(const Vector<T, 4> &s, const Vector<T, 4> &low, const Vector<T, 4> &high)
    {
        return Vector<T, 4>(std::clamp(s.x, low.x, high.x), std::clamp(s.y, low.y, high.y), std::clamp(s.z, low.z, high.z), std::clamp(s.w, low.w, high.w));
    }
    template <typename T>
    Vector<T, 4> ceil(const Vector<T, 4> &other)
    {
        return Vector<T, 4>(std::ceil(other.x), std::ceil(other.y), std::ceil(other.z), std::ceil(other.w));
    }
    template <typename T>
    Vector<T, 4> floor(const Vector<T, 4> &other)
    {
        return Vector<T, 4>(std::floor(other.x), std::floor(other.y), std::floor(other.z), std::floor(other.w));
    }

    // template <typename T>
    // Vector<T, 4> CatmullRom(const Vector<T, 4> &v0, const Vector<T, 4> &v1,
    //                         const Vector<T, 4> &v2, const Vector<T, 4> &v3, T f)
    // {
        // static const T two = static_cast<T>(2);
        // static const T three = static_cast<T>(3);

        // Vector<T, 4> d1 = (v2 - v0) / two;
        // Vector<T, 4> d2 = (v3 - v1) / two;
        // Vector<T, 4> D1 = v2 - v1;

        // Vector<T, 4> a3 = d1 - two * D1, + d2;
        // Vector<T, 4> a2 = - two * d1 + three * D1 - d2;
        // Vector<T ,3> a1 = d1;
        // Vector<T, 4> a0 = v1;

        // return a3 * cubic(f) + a2 * square(f) + a1 * f + a0;
    // }
}
#endif
