#ifndef INCLUDE_BIG_POINT2_H_
#define INCLUDE_BIG_POINT2_H_
#include "point.h"
namespace big
{
    template <typename T>
    class Point<T, 2>
    {
    public:
        static_assert(std::is_arithmetic<T>::value, "Point only can be instantiated with arithmetic types.");

        T x;
        T y;

        constexpr Point() : x(0), y(0) {}

        constexpr Point(T x_, T y_) : x(x_), y(y_) {}

        template <typename U>
        Point(const std::initializer_list<U> &lst);

        template <typename U>
        void set(const std::initializer_list<U> &lst);

        constexpr Point(const Point &v) : x(v.x), y(v.y) {} // copy construct.

        void set(T newX, T newY);

        void set(const Point &other);

        void setZero();

        Point add(T &val) const;

        Point add(const Point &other) const;

        Point sub(T &val) const;

        Point sub(const Point &other) const;

        Point mul(T &val) const;

        Point mul(const Point &other) const;

        Point div(T &val) const;

        Point div(const Point &other) const;

        Point rsub(T &val) const;

        Point rsub(T &&val) const;

        Point rsub(const Point &other) const;

        Point rdiv(T &val) const;

        Point rdiv(const Point &other) const;

        void iadd(T &val);

        void iadd(const Point &other);

        void isub(T &val);

        void isub(const Point &other);

        void imul(T &val);

        void imul(const Point &other);

        void idiv(T &val);

        void idiv(const Point &other);

        T &at(T i);

        const T &at(T i) const;

        T sum() const;

        T min() const;

        T max() const;

        T absmin() const;

        T absmax() const;

        T domintAxis() const;

        T subminanAxis() const;

        template <typename U>
        Point<U, 2> castTo() const;

        bool isEqual(const Point &other) const;

        T &operator[](T i);

        const T &operator[](T i) const;

        Point &operator=(const Point &other);

        template <typename U>
        Point &operator=(std::initializer_list<U> &lst);

        Point &operator+=(T &val);

        Point &operator+=(const Point &other);

        Point &operator-=(T &val);

        Point &operator-=(const Point &other);

        Point &operator*=(T &val);

        Point &operator*=(const Point &other);

        Point &operator/=(T &val);

        Point &operator/=(const Point &other);

        bool operator==(const Point &other) const;

        bool operator!=(const Point &other) const;

        // Point operator+(const Point &other);
    };

    template <typename T>
    using Point2 = Point<T, 2>;

    template <typename T>
    Point<T, 2> operator+(const Point<T, 2> &other1, const Point<T, 2> &other2);

    template <typename T>
    Point<T, 2> operator+(T val, const Point<T, 2> &other);

    template <typename T>
    Point<T, 2> operator+(const Point<T, 2> &other, T val);

    template <typename T>
    Point<T, 2> operator+(const Point<T, 2> &other);

    template <typename T>
    Point<T, 2> operator-(const Point<T, 2> &other1, const Point<T, 2> &other2);

    template <typename T>
    Point<T, 2> operator-(T val, const Point<T, 2> &other);

    template <typename T>
    Point<T, 2> operator-(const Point<T, 2> &other, T val);

    template <typename T>
    Point<T, 2> operator-(const Point<T, 2> &other);

    template <typename T>
    Point<T, 2> operator*(const Point<T, 2> &other1, const Point<T, 2> &other2);

    template <typename T>
    Point<T, 2> operator*(T val, const Point<T, 2> &other);

    template <typename T>
    Point<T, 2> operator*(const Point<T, 2> &other, T val);

    template <typename T>
    Point<T, 2> operator/(const Point<T, 2> &other1, const Point<T, 2> &other2);

    template <typename T>
    Point<T, 2> operator/(T val, const Point<T, 2> &other);

    template <typename T>
    Point<T, 2> operator/(const Point<T, 2> &other, T val);

    template <typename T>
    Point<T, 2> min(const Point<T, 2> &other1, const Point<T, 2> &other2);

    template <typename T>
    Point<T, 2> max(const Point<T, 2> &other1, const Point<T, 2> &other2);

    template <typename T>
    Point<T, 2> clamp(const Point<T, 2> &s, const Point<T, 2> &low, const Point<T, 2> &high);

    template <typename T>
    Point<T, 2> ceil(const Point<T, 2> &other);

    template <typename T>
    Point<T, 2> floor(const Point<T, 2> &other);

    typedef Point<float, 2> Point2F;
    typedef Point<double, 2> Point2D;
    typedef Point<std::size_t, 2> Point2UI;
    typedef Point<int , 2> Point2I; 


}
#include "detail/point2-inl.h"
#endif