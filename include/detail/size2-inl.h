#ifndef INCLUDE_BIG_SIZE2_INL_H_
#define INCLUDE_BIG_SIZE2_INL_H_

#include <algorithm>
// #include 
namespace big
{
    template <typename U>
    inline Size2::Size2(const std::initializer_list<U> &lst)
    {
        set(lst);
    }

    inline void Size2::set(std::size_t newX, std::size_t newY)
    {
        x = newX;
        y = newY;
    }

    inline void Size2::set(const Size2 &other)
    {
        x = other.x;
        y = other.y;
    }

    inline void Size2::setZero()
    {
        x = 0;
        y = 0;
    }
    inline Size2 Size2::add(std::size_t &val) const
    {
        return Size2(x + val, y + val);
    }

    inline Size2 Size2::add(const Size2 &other) const
    {
        return Size2(x + other.x, y + other.y);
    }

    inline Size2 Size2::sub(std::size_t &val) const
    {
        return Size2(x - val, y - val);
    }

    inline Size2 Size2::sub(const Size2 &other) const
    {
        return Size2(x - other.x, y - other.y);
    }
    inline Size2 Size2::mul(std::size_t &val) const
    {
        return Size2(x * val, y * val);
    }

    inline Size2 Size2::mul(const Size2 &other) const
    {
        return Size2(x * other.x, y * other.y);
    }

    inline Size2 Size2::div(std::size_t &val) const
    {
        return Size2(x / val, y / val);
    }

    inline Size2 Size2::div(const Size2 &other) const
    {
        return Size2(x / other.x, y / other.y);
    }

    inline Size2 Size2::rsub(std::size_t &val) const
    {
        return Size2(val - x, val - y);
    }

    inline Size2 Size2::rsub(const Size2 &other) const
    {
        return Size2(other.x - x, other.y - y);
    }

    inline Size2 Size2::rdiv(std::size_t &val) const
    {
        return Size2(val / x, val / y);
    }

    inline Size2 Size2::rdiv(const Size2 &other) const
    {
        return Size2(other.x / x, other.y / y);
    }

    inline void Size2::iadd(std::size_t &val)
    {
        x += val;
        y += val;
    }

    inline void Size2::iadd(const Size2 &other)
    {
        x += other.x;
        y += other.y;
    }

    inline void Size2::isub(std::size_t &val)
    {
        x -= val;
        y -= val;
    }

    inline void Size2::isub(const Size2 &other)
    {
        x -= other.x;
        y -= other.y;
    }

    inline void Size2::imul(std::size_t &val)
    {
        x *= val;
        y *= val;
    }

    inline void Size2::imul(const Size2 &other)
    {
        x *= other.x;
        y *= other.y;
    }

    inline void Size2::idiv(std::size_t &val)
    {
        x /= val;
        y /= val;
    }

    inline void Size2::idiv(const Size2 &other)
    {
        x /= other.x;
        y /= other.y;
    }

    std::size_t &Size2::at(std::size_t i)
    {
        assert(i < 2);
        return (&x)[i];
    }

    const std::size_t &Size2::at(std::size_t i) const
    {
        assert(i < 2);
        return (&x)[i];
    }

    inline std::size_t Size2::sum() const
    {
        return x + y;
    }

    inline std::size_t Size2::min() const
    {
        return std::min(x, y);
    }
    inline std::size_t Size2::max() const
    {
        return std::max(x, y);
    }
    // std::size_t Size2::absmin() const
    // {
    //     return std::max(x, y);
    // }

    // std::size_t Size2::absmax() const
    // {
    //     return  x+y;
    // }

    inline std::size_t Size2::domintAxis() const
    {
        return (x > y) ? 0 : 1;
    }

    inline std::size_t Size2::subminanAxis() const
    {
        return (x < y) ? 0 : 1;
    }

    inline bool Size2::isEqual(const Size2 &other) const
    {
        return (x == other.x && y == other.x);
    }

    inline std::size_t &Size2::operator[](std::size_t i)
    {
        assert(i < 2);
        return (&x)[i];
    }
    inline const std::size_t &Size2::operator[](std::size_t i) const
    {
        assert(i < 2);
        return (&x)[i];
    }

    inline Size2 &Size2::operator=(const Size2 &other)
    {
        set(other);
        return *this;
    }
    template <typename U>
    inline Size2 &Size2::operator=(std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }

    inline Size2 &Size2::operator+=(std::size_t &val)
    {
        iadd(val);
        return (*this);
    }

    inline Size2 &Size2::operator+=(const Size2 &other)
    {
        iadd(other);
        return (*this);
    }

    inline Size2 &Size2::operator-=(std::size_t &val)
    {
        isub(val);
        return (*this);
    }

    inline Size2 &Size2::operator-=(const Size2 &other)
    {
        isub(other);
        return (*this);
    }

    inline Size2 &Size2::operator*=(std::size_t &val)
    {
        imul(val);
        return (*this);
    }

    inline Size2 &Size2::operator*=(const Size2 &other)
    {
        imul(other);
        return (*this);
    }

    inline Size2 &Size2::operator/=(std::size_t &val)
    {
        idiv(val);
        return (*this);
    }

    inline Size2 &Size2::operator/=(const Size2 &other)
    {
        idiv(other);
        return (*this);
    }

    inline bool Size2::operator==(const Size2 &other) const
    {
        return isEqual(other);
    }

    inline bool Size2::operator!=(const Size2 &other) const
    {
        return !isEqual(other);
    }
    template <typename U>
    inline void Size2::set(const std::initializer_list<U> &lst)
    {
        auto input = lst.begin();
        x = static_cast<std::size_t>(*input);
        y = static_cast<std::size_t>(*(++input));
    }
    inline Size2 operator+(const Size2 &other1, const Size2 &other2)
    {
        return other1.add(other2);
    }

    inline Size2 operator+(std::size_t val, const Size2 &other)
    {
        return other.add(val);
    }

    inline Size2 operator+(const Size2 &other, std::size_t val)
    {
        return other.add(val);
    }

    inline Size2 operator+(const Size2 &other)
    {
        return other;
    }

    inline Size2 operator-(const Size2 &other1, const Size2 &other2)
    {
        return other1.sub(other2);
    }

    inline Size2 operator-(std::size_t val, const Size2 &other)
    {
        return other.rsub(val);
    }

    inline Size2 operator-(const Size2 &other, std::size_t val)
    {
        return other.sub(val);
    }

    inline Size2 operator-(const Size2 &other)
    {
        // return other.rsub(0);
    }

    inline Size2 operator*(const Size2 &other1, const Size2 &other2)
    {
        return other1.mul(other2);
    }

    inline Size2 operator*(std::size_t val, const Size2 &other)
    {
        return other.mul(val);
    }

    inline Size2 operator*(const Size2 &other, std::size_t val)
    {
        return other.mul(val);
    }

    inline Size2 operator/(const Size2 &other1, const Size2 &other2)
    {
        return other1.div(other2);
    }

    inline Size2 operator/(std::size_t val, const Size2 &other)
    {
        return other.rdiv(val);
    }

    inline Size2 operator/(const Size2 &other, std::size_t val)
    {
        return other.div(val);
    }

    inline Size2 min(const Size2 &other1, const Size2 &other2)
    {
        return Size2(std::min(other1.x, other2.x), std::min(other1.y, other2.y));
    }

    inline Size2 max(const Size2 &other1, const Size2 &other2)
    {
        return Size2(std::max(other1.x, other2.x), std::max(other1.y, other2.y));
    }

    // Size2 clamp(const Size2 &s, const Size2 &low, const Size2 &high)
    // {
    //     return Size2(clamp(s.x, low.x, high.x), clamp(s.y, low.y, high.y));
    // }

    inline Size2 ceil(const Size2 &other);

    inline Size2 floor(const Size2 &other);
}
#endif