#ifndef INCLUDE_BIG_SIZE2_H_
#define INCLUDE_BIG_SIZE2_H_
#include <size.h>
namespace big
{
    class Size2
    {
    public:
        std::size_t x;

        std::size_t y;

        constexpr Size2() : x(0), y(0) {}

        constexpr Size2(std::size_t x_, std::size_t y_) : x(x_), y(y_) {}

        template <typename U>
        Size2(const std::initializer_list<U> &lst);

        constexpr Size2(const Size2 &other) : x(other.x), y(other.y) {}

        // void set(std::size_t s);

        void set(std::size_t newX, std::size_t newY);

        template <typename U>
        void set(const std::initializer_list<U> &lst);

        void set(const Size2 &other);

        void setZero();

        Size2 add(std::size_t &val) const;

        Size2 add(const Size2 &other) const;

        Size2 sub(std::size_t &val) const;

        Size2 sub(const Size2 &other) const;

        Size2 mul(std::size_t &val) const;

        Size2 mul(const Size2 &other) const;

        Size2 div(std::size_t &val) const;

        Size2 div(const Size2 &other) const;

        Size2 rsub(std::size_t &val) const;

        Size2 rsub(const Size2 &other) const;

        Size2 rdiv(std::size_t &val) const;

        Size2 rdiv(const Size2 &other) const;

        void iadd(std::size_t &val);

        void iadd(const Size2 &other);

        void isub(std::size_t &val);

        void isub(const Size2 &other);

        void imul(std::size_t &val);

        void imul(const Size2 &other);

        void idiv(std::size_t &val);

        void idiv(const Size2 &other);

        std::size_t &at(std::size_t i);

        const std::size_t &at(std::size_t i) const;

        std::size_t sum() const;

        std::size_t min() const;

        std::size_t max() const;

        std::size_t absmin() const;

        std::size_t absmax() const;

        std::size_t domintAxis() const;

        std::size_t subminanAxis() const;

        bool isEqual(const Size2 &other) const;

        std::size_t &operator[](std::size_t i);

        const std::size_t &operator[](std::size_t i) const;

        Size2 &operator=(const Size2 &other);

        template <typename U>
        Size2 &operator=(std::initializer_list<U> &lst);

        Size2 &operator+=(std::size_t &val);

        Size2 &operator+=(const Size2 &other);

        Size2 &operator-=(std::size_t &val);

        Size2 &operator-=(const Size2 &other);

        Size2 &operator*=(std::size_t &val);

        Size2 &operator*=(const Size2 &other);

        Size2 &operator/=(std::size_t &val);

        Size2 &operator/=(const Size2 &other);

        bool operator==(const Size2 &other) const;

        bool operator!=(const Size2 &other) const;

        // Size2 operator+(const Size2 &other);
    };

    Size2 operator+(const Size2 &other1, const Size2 &other2);

    Size2 operator+(std::size_t val, const Size2 &other);

    Size2 operator+( const Size2 &other, std::size_t val);

    Size2 operator+(const Size2 &other);


    Size2 operator-(const Size2 &other1, const Size2 &other2);

    Size2 operator-(std::size_t val, const Size2 &other);

    Size2 operator-(const Size2 &other,std::size_t val);

    Size2 operator-(const Size2 &other);


    Size2 operator*(const Size2 &other1, const Size2 &other2);

    Size2 operator*(std::size_t val, const Size2 &other);

    Size2 operator*(const Size2 &other, std::size_t val);

    Size2 operator/(const Size2 &other1, const Size2 &other2);

    Size2 operator/(std::size_t val, const Size2 &other);

    Size2 operator/(const Size2 &other, std::size_t val);

    Size2 min(const Size2 &other1, const Size2 &other2);

    Size2 max(const Size2 &other1, const Size2 &other2);

    Size2 clamp(const Size2 &s, const Size2 &low, const Size2 &high);

    Size2 ceil(const Size2 &other);

    Size2 floor(const Size2 &other);

}

#include <detail/size2-inl.h>
#endif