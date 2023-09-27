#ifndef INCLUDE_BIG_POINT2_INL_H_
#define INCLUDE_BIG_POINT2_INL_H_

#include "math_utils.h"
#include <math.h>
namespace big
{
    template <typename T>
    template <typename U>
    Point<T, 2>::Point(const std::initializer_list<U> &lst)
    {
        set(lst);
    }

    template <typename T>
    template <typename U>
    void Point<T, 2>::set(const std::initializer_list<U> &lst)
    {
        assert(lst.size() >= 2 && "initializer_list size is less than 2!");
        auto first_ptr = lst.begin();
        x = static_cast<T>(*first_ptr);
        y = static_cast<T>(*(++first_ptr));
    }

    template <typename T>
    void Point<T, 2>::set(T newX, T newY)
    {
        x = newX;
        y = newY;
    }

    template <typename T>
    void Point<T, 2>::set(const Point<T, 2> &other)
    {
        x = other.x;
        y = other.y;
    }

    template <typename T>
    void Point<T, 2>::setZero()
    {
        x = y = static_cast<T>(0);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::add(T &val) const
    {
        return Point(x + val, y + val);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::add(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::sub(T &val) const
    {
        return Point(x - val, y - val);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::sub(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }
    template <typename T>
    Point<T, 2> Point<T, 2>::mul(T &val) const
    {
        return Point(x * val, y * val);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::mul(const Point<T, 2> &other) const
    {
        return Point(x * other.x, y * other.y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::div(T &val) const
    {
        return Point(x / val, y / val);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::div(const Point<T, 2> &other) const
    {
        return Point(x / other.x, y / other.y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::rsub(T &val) const
    {
        return Point(val - x, val - y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::rsub(T &&val) const
    {
        return Point(val - x, val - y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::rsub(const Point<T, 2> &other) const
    {
        return Point(other.x - x, other.y - y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::rdiv(T &val) const
    {
        return Point(val / x, val / y);
    }

    template <typename T>
    Point<T, 2> Point<T, 2>::rdiv(const Point<T, 2> &other) const
    {
        return Point(other.x / x, other.y / y);
    }

    template <typename T>
    void Point<T, 2>::iadd(T &val)
    {
        x += val;
        y += val;
    }

    template <typename T>
    void Point<T, 2>::iadd(const Point &other)
    {
        x += other.x;
        y += other.y;
    }

    template <typename T>
    void Point<T, 2>::isub(T &val)
    {
        x -= val;
        y -= val;
    }

    template <typename T>
    void Point<T, 2>::isub(const Point &other)
    {
        x -= other.x;
        y -= other.y;
    }

    template <typename T>
    void Point<T, 2>::imul(T &val)
    {
        x *= val;
        y *= val;
    }

    template <typename T>
    void Point<T, 2>::imul(const Point &other)
    {
        x *= other.x;
        y *= other.y;
    }

    template <typename T>
    void Point<T, 2>::idiv(T &val)
    {
        x /= val;
        y /= val;
    }

    template <typename T>
    void Point<T, 2>::idiv(const Point &other)
    {
        x /= other.x;
        y /= other.y;
    }

    template <typename T>
    T &Point<T, 2>::at(std::size_t i)
    {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    const T &Point<T, 2>::at(std::size_t i) const
    {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    T Point<T, 2>::sum() const
    {
        return x + y;
    }

    template <typename T>
    T Point<T, 2>::min() const
    {
        return std::min(x, y);
    }
    template <typename T>
    T Point<T, 2>::max() const
    {
        return std::max(x, y);
    }

    template <typename T>
    T Point<T, 2>::absmin() const
    {
        return absmin(x, y);
    }

    template <typename T>
    T Point<T, 2>::absmax() const
    {
        return absmax(x, y);
    }

    template <typename T>
    std::size_t Point<T, 2>::domintAxis() const
    {
        return (std::abs(x) > std::abs(y)) ? 0 : 1;
    }

    template <typename T>
    std::size_t Point<T, 2>::subminanAxis() const
    {
        return (std::abs(x) < std::abs(y)) ? 0 : 1;
    }

    template <typename T>
    bool Point<T, 2>::isEqual(const Point &other) const
    {
        return (x == other.x && y == other.x);
    }

    template <typename T>
    template <typename U>
    Point<U, 2> Point<T, 2>::castTo() const
    {
        return Point<U, 2>(static_cast<U>(x), static_cast<U>(y));
    }

    template <typename T>
    T &Point<T, 2>::operator[](T i)
    {
        assert(i < 2);
        return (&x)[i];
    }
    template <typename T>
    const T &Point<T, 2>::operator[](T i) const
    {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    Point<T, 2> &Point<T, 2>::operator=(const Point &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    template <typename U>
    Point<T, 2> &Point<T, 2>::operator=(std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }

    template <typename T>
    Point<T, 2> &Point<T, 2>::operator+=(T &val)
    {
        iadd(val);
        return (*this);
    }

    template <typename T>
    Point<T, 2> &Point<T, 2>::operator+=(const Point &other)
    {
        iadd(other);
        return (*this);
    }

    template <typename T>
    Point<T, 2> &Point<T, 2>::operator-=(T &val)
    {
        isub(val);
        return (*this);
    }

    template <typename T>
    Point<T, 2> &Point<T, 2>::operator-=(const Point &other)
    {
        isub(other);
        return (*this);
    }

    template <typename T>
    Point<T, 2> &Point<T, 2>::operator*=(T &val)
    {
        imul(val);
        return (*this);
    }

    template <typename T>
    Point<T, 2> &Point<T, 2>::operator*=(const Point &other)
    {
        imul(other);
        return (*this);
    }

    template <typename T>
    Point<T, 2> &Point<T, 2>::operator/=(T &val)
    {
        idiv(val);
        return (*this);
    }

    template <typename T>
    Point<T, 2> &Point<T, 2>::operator/=(const Point &other)
    {
        idiv(other);
        return (*this);
    }

    template <typename T>
    bool Point<T, 2>::operator==(const Point &other) const
    {
        return isEqual(other);
    }

    template <typename T>
    bool Point<T, 2>::operator!=(const Point &other) const
    {
        return !isEqual(other);
    }

    template <typename T>
    Point<T, 2> operator+(const Point<T, 2> &other1, const Point<T, 2> &other2)
    {
        return other1.add(other2);
    }

    template <typename T>
    Point<T, 2> operator+(T val, const Point<T, 2> &other)
    {
        return other.add(val);
    }

    template <typename T>
    Point<T, 2> operator+(const Point<T, 2> &other, T val)
    {
        return other.add(val);
    }

    template <typename T>
    Point<T, 2> operator+(const Point<T, 2> &other)
    {
        return other;
    }

    template <typename T>
    Point<T, 2> operator-(const Point<T, 2> &other1, const Point<T, 2> &other2)
    {
        return other1.sub(other2);
    }

    template <typename T>
    Point<T, 2> operator-(T val, const Point<T, 2> &other)
    {
        return other.rsub(val);
    }

    template <typename T>
    Point<T, 2> operator-(const Point<T, 2> &other, T val)
    {
        return other.sub(val);
    }

    template <typename T>
    Point<T, 2> operator-(const Point<T, 2> &other)
    {
        return other.rsub(0);
    }

    template <typename T>
    Point<T, 2> operator*(const Point<T, 2> &other1, const Point<T, 2> &other2)
    {
        return other1.mul(other2);
    }

    template <typename T>
    Point<T, 2> operator*(T val, const Point<T, 2> &other)
    {
        return other.mul(val);
    }

    template <typename T>
    Point<T, 2> operator*(const Point<T, 2> &other, T val)
    {
        return other.mul(val);
    }

    template <typename T>
    Point<T, 2> operator/(const Point<T, 2> &other1, const Point<T, 2> &other2)
    {
        return other1.div(other2);
    }

    template <typename T>
    Point<T, 2> operator/(T val, const Point<T, 2> &other)
    {
        return other.rdiv(val);
    }

    template <typename T>
    Point<T, 2> operator/(const Point<T, 2> &other, T val)
    {
        return other.div(val);
    }
    template <typename T>
    Point<T, 2> min(const Point<T, 2> &other1, const Point<T, 2> &other2)
    {
        return Point<T, 2>(std::min(other1.x, other2.x), std::min(other1.y, other2.y));
    }
    template <typename T>
    Point<T, 2> max(const Point<T, 2> &other1, const Point<T, 2> &other2)
    {
        return Point<T, 2>(std::max(other1.x, other2.x), std::max(other1.y, other2.y));
    }
    template <typename T>
    Point<T, 2> clamp(const Point<T, 2> &s, const Point<T, 2> &low, const Point<T, 2> &high)
    {
        return Point<T, 2>(std::clamp(s.x, low.x, high.x), std::clamp(s.y, low.y, high.y));
    }
    template <typename T>
    Point<T, 2> ceil(const Point<T, 2> &other)
    {
        return Point<T, 2>(std::ceil(other.x), std::ceil(other.y));
    }
    template <typename T>
    Point<T, 2> floor(const Point<T, 2> &other)
    {
        return Point<T, 2>(std::floor(other.x), std::floor(other.y));
    }
}

#endif