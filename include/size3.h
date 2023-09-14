#ifndef INCLUDE_BIG_SIZE3_H_
#define INCLUDE_BIG_SIZE3_H_
#include <size2.h>
namespace big
{
    class Size3
    {
    public:
        std::size_t x;

        std::size_t y;

        std::size_t z;

        constexpr Size3() : x(0), y(0), z(0) {}

        constexpr Size3(std::size_t x_, std::size_t y_, std::size_t z_) : x(x_), y(y_), z(z_) {}

        constexpr Size3(const Size2 &other, std::size_t z_) : x(other.x), y(other.y), z(z_) {}

        template <typename U>
        Size3(const std::initializer_list<U> &lst);

        constexpr Size3(const Size3 &other) : x(other.x), y(other.y), z(other.z) {}

        // void set(std::size_t s);

        void set(std::size_t newX, std::size_t newY, std::size_t newZ);

        void set(const Size2 &other, std::size_t z_);

        template <typename U>
        void set(const std::initializer_list<U> &lst);

        void set(const Size3 &other);

        void setZero();

        Size3 add(std::size_t &val) const;

        Size3 add(const Size3 &other) const;

        Size3 sub(std::size_t &val) const;

        Size3 sub(const Size3 &other) const;

        Size3 mul(std::size_t &val) const;

        Size3 mul(const Size3 &other) const;

        Size3 div(std::size_t &val) const;

        Size3 div(const Size3 &other) const;

        Size3 rsub(std::size_t &val) const;

        Size3 rsub(std::size_t &&val) const;

        Size3 rsub(const Size3 &other) const;

        Size3 rdiv(std::size_t &val) const;

        Size3 rdiv(const Size3 &other) const;

        void iadd(std::size_t &val);

        void iadd(const Size3 &other);

        void isub(std::size_t &val);

        void isub(const Size3 &other);

        void imul(std::size_t &val);

        void imul(const Size3 &other);

        void idiv(std::size_t &val);

        void idiv(const Size3 &other);

        std::size_t &at(std::size_t i);

        const std::size_t &at(std::size_t i) const;

        std::size_t sum() const;

        std::size_t min() const;

        std::size_t max() const;

        // std::size_t absmin() const;

        // std::size_t absmax() const;

        std::size_t domintAxis() const;

        std::size_t subminanAxis() const;

        bool isEqual(const Size3 &other) const;

        std::size_t &operator[](std::size_t i);

        const std::size_t &operator[](std::size_t i) const;

        Size3 &operator=(const Size3 &other);

        template <typename U>
        Size3 &operator=(std::initializer_list<U> &lst);

        Size3 &operator+=(std::size_t &val);

        Size3 &operator+=(const Size3 &other);

        Size3 &operator-=(std::size_t &val);

        Size3 &operator-=(const Size3 &other);

        Size3 &operator*=(std::size_t &val);

        Size3 &operator*=(const Size3 &other);

        Size3 &operator/=(std::size_t &val);

        Size3 &operator/=(const Size3 &other);

        bool operator==(const Size3 &other) const;

        bool operator!=(const Size3 &other) const;

        // Size3 operator+(const Size3 &other);
    };

    Size3 operator+(const Size3 &other1, const Size3 &other2);

    Size3 operator+(std::size_t val, const Size3 &other);

    Size3 operator+(const Size3 &other, std::size_t val);

    Size3 operator+(const Size3 &other);

    Size3 operator-(const Size3 &other1, const Size3 &other2);

    Size3 operator-(std::size_t val, const Size3 &other);

    Size3 operator-(const Size3 &other, std::size_t val);

    Size3 operator-(const Size3 &other);

    Size3 operator*(const Size3 &other1, const Size3 &other2);

    Size3 operator*(std::size_t val, const Size3 &other);

    Size3 operator*(const Size3 &other, std::size_t val);

    Size3 operator/(const Size3 &other1, const Size3 &other2);

    Size3 operator/(std::size_t val, const Size3 &other);

    Size3 operator/(const Size3 &other, std::size_t val);

    Size3 min(const Size3 &other1, const Size3 &other2);

    Size3 max(const Size3 &other1, const Size3 &other2);

    Size3 clamp(const Size3 &s, const Size3 &low, const Size3 &high);

    // Size3 ceil(const Size3 &other);

    // Size3 floor(const Size3 &other);

}

#include <detail/size3-inl.h>
#endif