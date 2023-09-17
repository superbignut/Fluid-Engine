#ifndef INCLUDE_BIG_POINT3_H_
#define INCLUDE_BIG_POINT3_H_
#include "point2.h"
namespace big
{
    template <typename T>
    class Point<T, 3>
    {
    public:
        static_assert(std::is_arithmetic<T>::value, "Point only can be instantiated with arithmetic types.");

        T x;
        T y;
        T z;

        constexpr Point() : x(0), y(0), z(0){}

        constexpr Point(T x_, T y_, T z_) : x(x_), y(y_), z(z_){}

        template <typename U>
        Point(const std::initializer_list<U> &lst);

        template <typename U>
        void set(const std::initializer_list<U> &lst);

        constexpr Point(const Point &v) : x(v.x), y(v.y), z(v.z) {} // copy construct.

        constexpr Point(const Point<T, 2> &pt, T z_) : x(pt.x), y(pt.y), z(z_){}

        void set(T newX, T newY, T newZ);

        void set(const Point &other);

        void set(const Point &pt, T z_);

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
        Point<U, 3> castTo() const;

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
    using Point3 = Point<T, 3>;

    template <typename T>
    Point<T, 3> operator+(const Point<T, 3> &other1, const Point<T, 3> &other2);

    template <typename T>
    Point<T, 3> operator+(T val, const Point<T, 3> &other);

    template <typename T>
    Point<T, 3> operator+(const Point<T, 3> &other, T val);

    template <typename T>
    Point<T, 3> operator+(const Point<T, 3> &other);

    template <typename T>
    Point<T, 3> operator-(const Point<T, 3> &other1, const Point<T, 3> &other2);

    template <typename T>
    Point<T, 3> operator-(T val, const Point<T, 3> &other);

    template <typename T>
    Point<T, 3> operator-(const Point<T, 3> &other, T val);

    template <typename T>
    Point<T, 3> operator-(const Point<T, 3> &other);

    template <typename T>
    Point<T, 3> operator*(const Point<T, 3> &other1, const Point<T, 3> &other2);

    template <typename T>
    Point<T, 3> operator*(T val, const Point<T, 3> &other);

    template <typename T>
    Point<T, 3> operator*(const Point<T, 3> &other, T val);

    template <typename T>
    Point<T, 3> operator/(const Point<T, 3> &other1, const Point<T, 3> &other2);

    template <typename T>
    Point<T, 3> operator/(T val, const Point<T, 3> &other);

    template <typename T>
    Point<T, 3> operator/(const Point<T, 3> &other, T val);

    template <typename T>
    Point<T, 3> min(const Point<T, 3> &other1, const Point<T, 3> &other2);

    template <typename T>
    Point<T, 3> max(const Point<T, 3> &other1, const Point<T, 3> &other2);

    template <typename T>
    Point<T, 3> clamp(const Point<T, 3> &s, const Point<T, 3> &low, const Point<T, 3> &high);

    template <typename T>
    Point<T, 3> ceil(const Point<T, 3> &other);

    template <typename T>
    Point<T, 3> floor(const Point<T, 3> &other);

    typedef Point<float, 3> Point3F;
    typedef Point<double, 3> Point3D;
    typedef Point<std::size_t, 3> Point3UI;
    typedef Point<int , 3> Point3I; 


}
#include "detail/point3-inl.h"
#endif