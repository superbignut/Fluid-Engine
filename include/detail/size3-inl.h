#ifndef INCLUDE_BIG_SIZE3_INL_H_
#define INCLUDE_BIG_SIZE3_INL_H_

#include <algorithm>
// #include
namespace big
{
    template <typename U>
    inline Size3::Size3(const std::initializer_list<U> &lst)
    {
        set(lst);
    }

    inline void Size3::set(std::size_t newX, std::size_t newY, std::size_t newZ)
    {
        x = newX;
        y = newY;
        z = newZ;
    }

    inline void Size3::set(const Size2 &other, std::size_t z_)
    {
        x = other.x;
        y = other.y;
        z = z_;
    }

    inline void Size3::set(const Size3 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    inline void Size3::setZero()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    inline Size3 Size3::add(std::size_t &val) const
    {
        return Size3(x + val, y + val, z + val);
    }

    inline Size3 Size3::add(const Size3 &other) const
    {
        return Size3(x + other.x, y + other.y, z + other.z);
    }

    inline Size3 Size3::sub(std::size_t &val) const
    {
        return Size3(x - val, y - val, z - val);
    }

    inline Size3 Size3::sub(const Size3 &other) const
    {
        return Size3(x - other.x, y - other.y, z - other.z);
    }
    inline Size3 Size3::mul(std::size_t &val) const
    {
        return Size3(x * val, y * val, z * val);
    }

    inline Size3 Size3::mul(const Size3 &other) const
    {
        return Size3(x * other.x, y * other.y, z * other.z);
    }

    inline Size3 Size3::div(std::size_t &val) const
    {
        return Size3(x / val, y / val, z / val);
    }

    inline Size3 Size3::div(const Size3 &other) const
    {
        return Size3(x / other.x, y / other.y, z / other.z);
    }

    inline Size3 Size3::rsub(std::size_t &val) const
    {
        return Size3(val - x, val - y, val - z);
    }

    inline Size3 Size3::rsub(std::size_t &&val) const
    {
        return Size3(val - x, val - y, val - z);
    }

    inline Size3 Size3::rsub(const Size3 &other) const
    {
        return Size3(other.x - x, other.y - y, other.z - z);
    }

    inline Size3 Size3::rdiv(std::size_t &val) const
    {
        return Size3(val / x, val / y, val / z);
    }

    inline Size3 Size3::rdiv(const Size3 &other) const
    {
        return Size3(other.x / x, other.y / y, other.z / z);
    }

    inline void Size3::iadd(std::size_t &val)
    {
        x += val;
        y += val;
        z += val;
    }

    inline void Size3::iadd(const Size3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    inline void Size3::isub(std::size_t &val)
    {
        x -= val;
        y -= val;
        z -= val;
    }

    inline void Size3::isub(const Size3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    inline void Size3::imul(std::size_t &val)
    {
        x *= val;
        y *= val;
        z *= val;
    }

    inline void Size3::imul(const Size3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }

    inline void Size3::idiv(std::size_t &val)
    {
        x /= val;
        y /= val;
        z /= val;
    }

    inline void Size3::idiv(const Size3 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
    }

    std::size_t &Size3::at(std::size_t i)
    {
        assert(i < 3);
        return (&x)[i];
    }

    const std::size_t &Size3::at(std::size_t i) const
    {
        assert(i < 3);
        return (&x)[i];
    }

    inline std::size_t Size3::sum() const
    {
        return x + y + z;
    }

    inline std::size_t Size3::min() const
    {
        return std::min(std::min(x, y), z);
    }
    inline std::size_t Size3::max() const
    {
        return std::max(std::max(x, y), z);
    }
    // std::size_t Size3::absmin() const
    // {
    //     return std::max(x, y);
    // }

    // std::size_t Size3::absmax() const
    // {
    //     return  x+y;
    // }

    inline std::size_t Size3::domintAxis() const
    {
        return (x > y) ? (x > z ? 0 : 2) : (y > z ? 1 : 2);
    }

    inline std::size_t Size3::subminanAxis() const
    {
        return (x < y) ? (x < z ? 0 : 2) : (y < z ? 1 : 2);
    }

    inline bool Size3::isEqual(const Size3 &other) const
    {
        return (x == other.x && y == other.x && z == other.z);
    }

    inline std::size_t &Size3::operator[](std::size_t i)
    {
        assert(i < 3);
        return (&x)[i];
    }
    inline const std::size_t &Size3::operator[](std::size_t i) const
    {
        assert(i < 3);
        return (&x)[i];
    }

    inline Size3 &Size3::operator=(const Size3 &other)
    {
        set(other);
        return *this;
    }
    template <typename U>
    inline Size3 &Size3::operator=(std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }

    inline Size3 &Size3::operator+=(std::size_t &val)
    {
        iadd(val);
        return (*this);
    }

    inline Size3 &Size3::operator+=(const Size3 &other)
    {
        iadd(other);
        return (*this);
    }

    inline Size3 &Size3::operator-=(std::size_t &val)
    {
        isub(val);
        return (*this);
    }

    inline Size3 &Size3::operator-=(const Size3 &other)
    {
        isub(other);
        return (*this);
    }

    inline Size3 &Size3::operator*=(std::size_t &val)
    {
        imul(val);
        return (*this);
    }

    inline Size3 &Size3::operator*=(const Size3 &other)
    {
        imul(other);
        return (*this);
    }

    inline Size3 &Size3::operator/=(std::size_t &val)
    {
        idiv(val);
        return (*this);
    }

    inline Size3 &Size3::operator/=(const Size3 &other)
    {
        idiv(other);
        return (*this);
    }

    inline bool Size3::operator==(const Size3 &other) const
    {
        return isEqual(other);
    }

    inline bool Size3::operator!=(const Size3 &other) const
    {
        return !isEqual(other);
    }
    template <typename U>
    inline void Size3::set(const std::initializer_list<U> &lst)
    {
        auto input = lst.begin();
        x = static_cast<std::size_t>(*input);
        y = static_cast<std::size_t>(*(++input));
        z = static_cast<std::size_t>(*(++input));
    }
    inline Size3 operator+(const Size3 &other1, const Size3 &other2)
    {
        return other1.add(other2);
    }

    inline Size3 operator+(std::size_t val, const Size3 &other)
    {
        return other.add(val);
    }

    inline Size3 operator+(const Size3 &other, std::size_t val)
    {
        return other.add(val);
    }

    inline Size3 operator+(const Size3 &other)
    {
        return other;
    }

    inline Size3 operator-(const Size3 &other1, const Size3 &other2)
    {
        return other1.sub(other2);
    }

    inline Size3 operator-(std::size_t val, const Size3 &other)
    {
        return other.rsub(val);
    }

    inline Size3 operator-(const Size3 &other, std::size_t val)
    {
        return other.sub(val);
    }

    inline Size3 operator-(const Size3 &other)
    {
        return other.rsub(0);
    }

    inline Size3 operator*(const Size3 &other1, const Size3 &other2)
    {
        return other1.mul(other2);
    }

    inline Size3 operator*(std::size_t val, const Size3 &other)
    {
        return other.mul(val);
    }

    inline Size3 operator*(const Size3 &other, std::size_t val)
    {
        return other.mul(val);
    }

    inline Size3 operator/(const Size3 &other1, const Size3 &other2)
    {
        return other1.div(other2);
    }

    inline Size3 operator/(std::size_t val, const Size3 &other)
    {
        return other.rdiv(val);
    }

    inline Size3 operator/(const Size3 &other, std::size_t val)
    {
        return other.div(val);
    }

    inline Size3 min(const Size3 &other1, const Size3 &other2)
    {
        return Size3(std::min(other1.x, other2.x), std::min(other1.y, other2.y), std::min(other1.z, other2.z));
    }

    inline Size3 max(const Size3 &other1, const Size3 &other2)
    {
        return Size3(std::max(other1.x, other2.x), std::max(other1.y, other2.y), std::max(other1.z, other2.z));
    }

    Size3 clamp(const Size3 &s, const Size3 &low, const Size3 &high)
    {
        return Size3(std::clamp(s.x, low.x, high.x), std::clamp(s.y, low.y, high.y), std::clamp(s.z, low.z, high.z));
    }

    // inline Size3 ceil(const Size3 &other);

    // inline Size3 floor(const Size3 &other);
}
#endif