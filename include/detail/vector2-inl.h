#ifndef INCLUDE_BIG_VECTOR2_INL_H_
#define INCLUDE_BIG_VCETOR2_INL_H_
#include "math_utils.h"
namespace big
{

    template <typename T>
    template <typename U>
    Vector<T, 2>::Vector(const std::initializer_list<U> &lst)
    {
        set(lst);
    }

    template <typename T>
    template <typename U>
    void Vector<T, 2>::set(const std::initializer_list<U> &lst)
    {
        assert(lst.size() == 2 && "the size of initializer_list is invalid.");
        auto first_ptr = lst.begin();
        x = static_cast<T>(*first_ptr);
        first_ptr++;
        y = static_cast<T>(*first_ptr);
    }

    template <typename T>
    void Vector<T, 2>::set(T newX, T newY)
    {
        x = newX;
        y = newY;
    }

    template <typename T>
    void Vector<T, 2>::set(const Vector<T, 2> &other)
    {
        x = other.x;
        y = other.y;
    }

    template <typename T>
    void Vector<T, 2>::setZero()
    {
        x = y = static_cast<T>(0);
    }

    template <typename T>
    void Vector<T, 2>::normize()
    {
        idiv(length());
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::add(T val) const
    {
        return Vector(x + val, y + val);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::add(const Vector &other) const
    {
        return Vector(x + other.x, y + other.y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::sub(T val) const
    {
        return Vector(x - val, y - val);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::sub(const Vector &other) const
    {
        return Vector(x - other.x, y - other.y);
    }
    template <typename T>
    Vector<T, 2> Vector<T, 2>::mul(T val) const
    {
        // val = 1.0;
        return Vector(x * val, y * val);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::mul(const Vector<T, 2> &other) const
    {
        return Vector(x * other.x, y * other.y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::div(T val) const
    {
        return Vector(x / val, y / val);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::div(const Vector<T, 2> &other) const
    {
        return Vector(x / other.x, y / other.y);
    }

    template <typename T>
    T Vector<T, 2>::dot(const Vector &other) const
    {
        return x * other.x + y * other.y;
    }
    template <typename T>
    T Vector<T, 2>::cross(const Vector &other) const
    {
        return x * other.y - y * other.x;
    }
    template <typename T>
    T Vector<T, 2>::rcross(const Vector &other) const
    {
        return other.x * y - other.y * x;
    }

    template <typename T>
    T Vector<T, 2>::length() const
    {
        return std::sqrt(lengthSquared());
    }

    template <typename T>
    T Vector<T, 2>::lengthSquared() const
    {
        return x * x + y * y;
    }
    template <typename T>
    Vector<T, 2> Vector<T, 2>::rsub(T val) const
    {
        return Vector(val - x, val - y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::rsub(T &&val) const
    {
        return Vector(val - x, val - y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::rsub(const Vector<T, 2> &other) const
    {
        return Vector(other.x - x, other.y - y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::rdiv(T &val) const
    {
        return Vector(val / x, val / y);
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::rdiv(const Vector<T, 2> &other) const
    {
        return Vector(other.x / x, other.y / y);
    }

    template <typename T>
    void Vector<T, 2>::iadd(T &val)
    {
        x += val;
        y += val;
    }

    template <typename T>
    void Vector<T, 2>::iadd(const Vector &other)
    {
        x += other.x;
        y += other.y;
    }

    template <typename T>
    void Vector<T, 2>::isub(T &val)
    {
        x -= val;
        y -= val;
    }

    template <typename T>
    void Vector<T, 2>::isub(const Vector &other)
    {
        x -= other.x;
        y -= other.y;
    }

    template <typename T>
    void Vector<T, 2>::imul(T &val)
    {
        x *= val;
        y *= val;
    }

    template <typename T>
    void Vector<T, 2>::imul(const Vector &other)
    {
        x *= other.x;
        y *= other.y;
    }

    template <typename T>
    void Vector<T, 2>::idiv(T &val)
    {
        x /= val;
        y /= val;
    }

    template <typename T>
    void Vector<T, 2>::idiv(const Vector &other)
    {
        x /= other.x;
        y /= other.y;
    }
    template <typename T>
    T &Vector<T, 2>::at(std::size_t i)
    {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    const T &Vector<T, 2>::at(std::size_t i) const
    {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    T Vector<T, 2>::sum() const
    {
        return x + y;
    }

    template <typename T>
    T Vector<T, 2>::min() const
    {
        return std::min(x, y);
    }
    template <typename T>
    T Vector<T, 2>::max() const
    {
        return std::max(x, y);
    }

    template <typename T>
    T Vector<T, 2>::absmin() const
    {
        return big::absmin(x, y);
    }

    template <typename T>
    T Vector<T, 2>::absmax() const
    {
        return big::absmax(x, y);
    }

    template <typename T>
    std::size_t Vector<T, 2>::domintAxis() const
    {
        return (std::abs(x) > std::abs(y)) ? 0 : 1;
    }

    template <typename T>
    std::size_t Vector<T, 2>::subminanAxis() const
    {
        return (std::abs(x) < std::abs(y)) ? 0 : 1;
    }

    template <typename T>
    Vector<T, 2> Vector<T, 2>::normalized() const
    {
        return div(length());
    }

    template <typename T>
    T Vector<T, 2>::distanceTo(const Vector &other) const
    {
        return sub(other).length()
    }

    template <typename T>
    T Vector<T, 2>::distanceSquaredTo(const Vector &other) const
    {
        return sub(other).lengthSquared();
    }
    template <typename T>
    Vector<T, 2> Vector<T, 2>::reflect(const Vector &normal) const
    { // this - ( 2 * this * n ) n
        return sub(normal.mul(2 * dot(normal)));
    }
    template <typename T>
    Vector<T, 2> Vector<T, 2>::project(const Vector &normal) const
    {
        return sub(normal.mul(dot(normal)));
    }
    template <typename T>
    Vector<T, 2> Vector<T, 2>::tangential() const
    {
        return Vector<T, 2>(-y, x);
    }

    template <typename T>
    template <typename U>
    Vector<U, 2> Vector<T, 2>::castTo() const
    {
        return Vector<U, 2>(static_cast<U>(x), static_cast<U>(y));
    }

    template <typename T>
    constexpr bool Vector<T, 2>::isEqual(const Vector &other) const
    {
        return x == other.x && y == other.y ? true : false;
    }

    template <typename T>
    constexpr bool Vector<T, 2>::isSimilar(const Vector &other, T epsilon) const
    {
        return std::abs(x - other.x) < epsilon && std::abs(y - other.y) < epsilon ? true : false;
    }

    template <typename T>
    T &Vector<T, 2>::operator[](T i)
    {
        assert(i < 2);
        return (&x)[i];
    }
    template <typename T>
    const T &Vector<T, 2>::operator[](T i) const
    {
        assert(i < 2);
        return (&x)[i];
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator=(const Vector &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    template <typename U>
    Vector<T, 2> &Vector<T, 2>::operator=(std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator+=(T &val)
    {
        iadd(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator+=(const Vector &other)
    {
        iadd(other);
        return (*this);
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator-=(T &val)
    {
        isub(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator-=(const Vector &other)
    {
        isub(other);
        return (*this);
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator*=(T &val)
    {
        imul(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator*=(const Vector &other)
    {
        imul(other);
        return (*this);
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator/=(T &val)
    {
        idiv(val);
        return (*this);
    }

    template <typename T>
    Vector<T, 2> &Vector<T, 2>::operator/=(const Vector &other)
    {
        idiv(other);
        return (*this);
    }

    template <typename T>
    bool Vector<T, 2>::operator==(const Vector &other) const
    {
        return isEqual(other);
    }

    template <typename T>
    bool Vector<T, 2>::operator!=(const Vector &other) const
    {
        return !isEqual(other);
    }

    template <typename T>
    Vector<T, 2> operator+(const Vector<T, 2> &other1, const Vector<T, 2> &other2)
    {
        return other1.add(other2);
    }

    template <typename T>
    Vector<T, 2> operator+(T val, const Vector<T, 2> &other)
    {
        return other.add(val);
    }

    template <typename T>
    Vector<T, 2> operator+(const Vector<T, 2> &other, T val)
    {
        return other.add(val);
    }

    template <typename T>
    Vector<T, 2> operator+(const Vector<T, 2> &other)
    {
        return other;
    }

    template <typename T>
    Vector<T, 2> operator-(const Vector<T, 2> &other1, const Vector<T, 2> &other2)
    {
        return other1.sub(other2);
    }

    template <typename T>
    Vector<T, 2> operator-(T val, const Vector<T, 2> &other)
    {
        return other.rsub(val);
    }

    template <typename T>
    Vector<T, 2> operator-(const Vector<T, 2> &other, T val)
    {
        return other.sub(val);
    }

    template <typename T>
    Vector<T, 2> operator-(const Vector<T, 2> &other)
    {
        return other.rsub(0);
    }

    template <typename T>
    Vector<T, 2> operator*(const Vector<T, 2> &other1, const Vector<T, 2> &other2)
    {
        return other1.mul(other2);
    }

    template <typename T>
    Vector<T, 2> operator*(T val, const Vector<T, 2> &other)
    {
        return other.mul(val);
    }

    template <typename T>
    Vector<T, 2> operator*(const Vector<T, 2> &other, T val)
    {
        return other.mul(val);
    }

    template <typename T>
    Vector<T, 2> operator/(const Vector<T, 2> &other1, const Vector<T, 2> &other2)
    {
        return other1.div(other2);
    }

    template <typename T>
    Vector<T, 2> operator/(T val, const Vector<T, 2> &other)
    {
        return other.rdiv(val);
    }

    template <typename T>
    Vector<T, 2> operator/(const Vector<T, 2> &other, T val)
    {
        return other.div(val);
    }
    template <typename T>
    Vector<T, 2> min(const Vector<T, 2> &other1, const Vector<T, 2> &other2)
    {
        return Vector<T, 2>(std::min(other1.x, other2.x), std::min(other1.y, other2.y));
    }
    template <typename T>
    Vector<T, 2> max(const Vector<T, 2> &other1, const Vector<T, 2> &other2)
    {
        return Vector<T, 2>(std::max(other1.x, other2.x), std::max(other1.y, other2.y));
    }
    template <typename T>
    Vector<T, 2> clamp(const Vector<T, 2> &s, const Vector<T, 2> &low, const Vector<T, 2> &high)
    {
        return Vector<T, 2>(std::clamp(s.x, low.x, high.x), std::clamp(s.y, low.y, high.y));
    }
    template <typename T>
    Vector<T, 2> ceil(const Vector<T, 2> &other)
    {
        return Vector<T, 2>(std::ceil(other.x), std::ceil(other.y));
    }
    template <typename T>
    Vector<T, 2> floor(const Vector<T, 2> &other)
    {
        return Vector<T, 2>(std::floor(other.x), std::floor(other.y));
    }
}
#endif
