#ifndef INCLUDE_BIG_POINT3_INL_H_
#define INCLUDE_BIG_POINT3_INL_H_

#include "math_utils.h"
#include <math.h>
namespace big
{
    template <typename T>
    template <typename U>
    Point<T, 3>::Point(const std::initializer_list<U> &lst)
    {
        set(lst);
    }

    template <typename T>
    template <typename U>
    void Point<T, 3>::set(const std::initializer_list<U> &lst)
    {
        assert(lst.size() >= 3 && "initializer_list size is less than 3!");
        auto first_ptr = lst.begin();
        x = static_cast<T>(*first_ptr);
        y = static_cast<T>(*(++first_ptr));
        z = static_cast<T>(*(++first_ptr));
    }

    template <typename T>
    void Point<T, 3>::set(T newX, T newY, T newZ)
    {
        x = newX;
        y = newY;
        z = newZ;
    }

    template <typename T>
    void Point<T, 3>::set(const Point<T, 3> &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    template <typename T>
    void Point<T, 3>::set(const Point &pt, T z_)
    {
        x = pt.x;
        y = pt.y;
        z = z_;
    }

    template <typename T>
    void Point<T, 3>::setZero()
    {
        x = y = z = static_cast<T>(0);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::add(T &val) const
    {
        return Point(x + val, y + val, z + val);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::add(const Point &other) const
    {
        return Point(x + other.x, y + other.y, z + other.z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::sub(T &val) const
    {
        return Point(x - val, y - val, z - val);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::sub(const Point &other) const
    {
        return Point(x - other.x, y - other.y, z - other.z);
    }
    template <typename T>
    Point<T, 3> Point<T, 3>::mul(T &val) const
    {
        return Point(x * val, y * val, z * val);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::mul(const Point<T, 3> &other) const
    {
        return Point(x * other.x, y * other.y, z * other.z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::div(T &val) const
    {
        return Point(x / val, y / val, z / val);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::div(const Point<T, 3> &other) const
    {
        return Point(x / other.x, y / other.y, z / other.z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::rsub(T &val) const
    {
        return Point(val - x, val - y, val - z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::rsub(T &&val) const
    {
        return Point(val - x, val - y, val - z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::rsub(const Point<T, 3> &other) const
    {
        return Point(other.x - x, other.y - y, other.z - z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::rdiv(T &val) const
    {
        return Point(val / x, val / y, val / z);
    }

    template <typename T>
    Point<T, 3> Point<T, 3>::rdiv(const Point<T, 3> &other) const
    {
        return Point(other.x / x, other.y / y, other.z / z);
    }

    template <typename T>
    void Point<T, 3>::iadd(T &val)
    {
        x += val;
        y += val;
        z += val;
    }

    template <typename T>
    void Point<T, 3>::iadd(const Point &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    template <typename T>
    void Point<T, 3>::isub(T &val)
    {
        x -= val;
        y -= val;
        z -= val;
    }

    template <typename T>
    void Point<T, 3>::isub(const Point &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    template <typename T>
    void Point<T, 3>::imul(T &val)
    {
        x *= val;
        y *= val;
        z *= val;
    }

    template <typename T>
    void Point<T, 3>::imul(const Point &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

    template <typename T>
    void Point<T, 3>::idiv(T &val)
    {
        x /= val;
        y /= val;
        z /= val;
    }

    template <typename T>
    void Point<T, 3>::idiv(const Point &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }

    template <typename T>
    T &Point<T, 3>::at(T i)
    {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    const T &Point<T, 3>::at(T i) const
    {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    T Point<T, 3>::sum() const
    {
        return x + y;
    }

    template <typename T>
    T Point<T, 3>::min() const
    {
        return std::min(x, y, z);
    }
    template <typename T>
    T Point<T, 3>::max() const
    {
        return std::max(x, y, z);
    }

    template <typename T>
    T Point<T, 3>::absmin() const
    {
        return absmin(x, y, z);
    }

    template <typename T>
    T Point<T, 3>::absmax() const
    {
        return absmax(x, y, z);
    }

    template <typename T>
    T Point<T, 3>::domintAxis() const
    {
        return (std::abs(x) > std::abs(y)) ? (std::abs(x) > std::abs(z) ? 0 : 2) : (std::abs(y) > std::abs(z) ? 1 : 2);
    }

    template <typename T>
    T Point<T, 3>::subminanAxis() const
    {
        return (std::abs(x) > std::abs(y)) ? (std::abs(x) > std::abs(z) ? 0 : 2) : (std::abs(y) > std::abs(z) ? 1 : 2);
    }

    template <typename T>
    bool Point<T, 3>::isEqual(const Point &other) const
    {
        return (x == other.x && y == other.x && z == other.z);
    }

    template <typename T>
    template <typename U>
    Point<U, 3> Point<T, 3>::castTo() const
    {
        return Point<U, 3>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
    }

    template <typename T>
    T &Point<T, 3>::operator[](T i)
    {
        assert(i < 3);
        return (&x)[i];
    }
    template <typename T>
    const T &Point<T, 3>::operator[](T i) const
    {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    Point<T, 3> &Point<T, 3>::operator=(const Point &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    template <typename U>
    Point<T, 3> &Point<T, 3>::operator=(std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }

    template <typename T>
    Point<T, 3> &Point<T, 3>::operator+=(T &val)
    {
        iadd(val);
        return (*this);
    }

    template <typename T>
    Point<T, 3> &Point<T, 3>::operator+=(const Point &other)
    {
        iadd(other);
        return (*this);
    }

    template <typename T>
    Point<T, 3> &Point<T, 3>::operator-=(T &val)
    {
        isub(val);
        return (*this);
    }

    template <typename T>
    Point<T, 3> &Point<T, 3>::operator-=(const Point &other)
    {
        isub(other);
        return (*this);
    }

    template <typename T>
    Point<T, 3> &Point<T, 3>::operator*=(T &val)
    {
        imul(val);
        return (*this);
    }

    template <typename T>
    Point<T, 3> &Point<T, 3>::operator*=(const Point &other)
    {
        imul(other);
        return (*this);
    }

    template <typename T>
    Point<T, 3> &Point<T, 3>::operator/=(T &val)
    {
        idiv(val);
        return (*this);
    }

    template <typename T>
    Point<T, 3> &Point<T, 3>::operator/=(const Point &other)
    {
        idiv(other);
        return (*this);
    }

    template <typename T>
    bool Point<T, 3>::operator==(const Point &other) const
    {
        return isEqual(other);
    }

    template <typename T>
    bool Point<T, 3>::operator!=(const Point &other) const
    {
        return !isEqual(other);
    }




    template <typename T>
    Point<T, 3> operator+(const Point<T, 3> &other1, const Point<T, 3> &other2)
    {
        return other1.add(other2);
    }

    template <typename T>
    Point<T, 3> operator+(T val, const Point<T, 3> &other)
    {
        return other.add(val);
    }

    template <typename T>
    Point<T, 3> operator+(const Point<T, 3> &other, T val)
    {
        return other.add(val);
    }

    template <typename T>
    Point<T, 3> operator+(const Point<T, 3> &other)
    {
        return other;
    }

    template <typename T>
    Point<T, 3> operator-(const Point<T, 3> &other1, const Point<T, 3> &other2)
    {
        return other1.sub(other2);
    }

    template <typename T>
    Point<T, 3> operator-(T val, const Point<T, 3> &other)
    {
        return other.rsub(val);
    }

    template <typename T>
    Point<T, 3> operator-(const Point<T, 3> &other, T val)
    {
        return other.sub(val);
    }

    template <typename T>
    Point<T, 3> operator-(const Point<T, 3> &other)
    {
        return other.rsub(0);
    }

    template <typename T>
    Point<T, 3> operator*(const Point<T, 3> &other1, const Point<T, 3> &other2)
    {
        return other1.mul(other2);
    }

    template <typename T>
    Point<T, 3> operator*(T val, const Point<T, 3> &other)
    {
        return other.mul(val);
    }

    template <typename T>
    Point<T, 3> operator*(const Point<T, 3> &other, T val)
    {
        return other.mul(val);
    }

    template <typename T>
    Point<T, 3> operator/(const Point<T, 3> &other1, const Point<T, 3> &other2)
    {
        return other1.div(other2);
    }

    template <typename T>
    Point<T, 3> operator/(T val, const Point<T, 3> &other)
    {
        return other.rdiv(val);
    }

    template <typename T>
    Point<T, 3> operator/(const Point<T, 3> &other, T val)
    {
        return other.div(val);
    }
    template <typename T>
    Point<T, 3> min(const Point<T, 3> &other1, const Point<T, 3> &other2)
    {
        return Point<T, 3>(std::min(other1.x, other2.x), std::min(other1.y, other2.y),std::min(other1.z, other2.z));
    }
    template <typename T>
    Point<T, 3> max(const Point<T, 3> &other1, const Point<T, 3> &other2)
    {
        return Point<T, 3>(std::max(other1.x, other2.x), std::max(other1.y, other2.y),std::max(other1.z, other2.z));
    }
    template <typename T>
    Point<T, 3> clamp(const Point<T, 3> &s, const Point<T, 3> &low, const Point<T, 3> &high)
    {
        return Point<T, 3>(std::clamp(s.x, low.x, high.x), std::clamp(s.y, low.y, high.y),std::clamp(s.z, low.z, high.z));
    }
    template <typename T>
    Point<T, 3> ceil(const Point<T, 3> &other)
    {
        return Point<T, 3>(std::ceil(other.x), std::ceil(other.y), std::ceil(other.z));
    }
    template <typename T>
    Point<T, 3> floor(const Point<T, 3> &other)
    {
        return Point<T, 3>(std::floor(other.x), std::floor(other.y), std::floor(other.z));
    }
}

#endif