#ifndef INCLUDE_BIG_VECTOR3_H_
#define INCLUDE_BIG_VECTOR3_H_
#include "vector2.h"
#include <tuple>
namespace big
{

    template <typename T>
    class Vector<T, 3> final
    { // no father
    public:
        static_assert(std::is_arithmetic<T>::value, "Vector only can be instantiated with arithmetic types.");

        T x;
        T y;
        T z;

        constexpr Vector() : x(0), y(0), z(0) {}

        constexpr Vector(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

        template <typename U>
        Vector(const std::initializer_list<U> &lst);

        template <typename U>
        void set(const std::initializer_list<U> &lst);

        constexpr Vector(const Vector &v) : x(v.x), y(v.y), z(v.z) {} // copy construct.

        constexpr Vector(const Vector<T, 2> &other, T z_) : x(other.x), y(other.y), z(z_) {}

        void set(const Vector<T, 2> &other, T z_);

        void set(T newX, T newY, T newZ);

        void set(const Vector &other);

        void setZero();

        void normalize();

        Vector add(T val) const;

        Vector add(const Vector &other) const;

        Vector sub(T val) const;

        Vector sub(const Vector &other) const;

        Vector mul(T val) const;

        Vector mul(const Vector &other) const;

        Vector div(T val) const;

        Vector div(const Vector &other) const;

        T dot(const Vector &other) const;

        Vector cross(const Vector &other) const;

        Vector rcross(const Vector &other) const;

        Vector rsub(T val) const;

        Vector rsub(T &&val) const;

        Vector rsub(const Vector &other) const;

        Vector rdiv(const T &val) const;

        Vector rdiv(const Vector &other) const;

        void iadd(T &val);

        void iadd(const Vector &other);

        void isub(T &val);

        void isub(const Vector &other);

        void imul(T &val);

        void imul(const Vector &other);

        void idiv(T &val);

        void idiv(const Vector &other);

        T &at(std::size_t i);

        const T &at(std::size_t i) const;

        T sum() const;

        T min() const;

        T max() const;

        T avg() const;

        T absmin() const;

        T absmax() const;

        void show() const;

        std::size_t domintAxis() const;

        std::size_t subminanAxis() const;

        Vector normalized() const;

        T length() const;

        T lengthSquared() const;

        T distanceTo(const Vector &other) const;

        T distanceSquaredTo(const Vector &other) const;

        Vector reflect(const Vector &normal) const;

        Vector project(const Vector &normal) const;

        // tuple are normalized()
        std::tuple<Vector<T, 3>, Vector<T, 3>> tangential() const;

        template <typename U>
        Vector<U, 3> castTo() const;

        constexpr bool isEqual(const Vector &other) const;

        constexpr bool isSimilar(const Vector &other, T epsilon = std::numeric_limits<T>::epsilon()) const;

        T &operator[](std::size_t i);

        const T &operator[](std::size_t i) const;

        Vector &operator=(const Vector &other);

        template <typename U>
        Vector &operator=(std::initializer_list<U> &lst);

        Vector &operator+=(T val);

        Vector &operator+=(const Vector &other);

        Vector &operator-=(T val);

        Vector &operator-=(const Vector &other);

        Vector &operator*=(T val);

        Vector &operator*=(const Vector &other);

        Vector &operator/=(T val);

        Vector &operator/=(const Vector &other);

        bool operator==(const Vector &other) const;

        bool operator!=(const Vector &other) const;
    };

    template <typename T>
    using Vector3 = Vector<T, 3>;

    template <typename T>
    Vector<T, 3> operator+(const Vector<T, 3> &other1, const Vector<T, 3> &other2);

    template <typename T>
    Vector<T, 3> operator+(T val, const Vector<T, 3> &other);

    template <typename T>
    Vector<T, 3> operator+(const Vector<T, 3> &other, T val);

    template <typename T>
    Vector<T, 3> operator+(const Vector<T, 3> &other);

    template <typename T>
    Vector<T, 3> operator-(const Vector<T, 3> &other1, const Vector<T, 3> &other2);

    template <typename T>
    Vector<T, 3> operator-(T val, const Vector<T, 3> &other);

    template <typename T>
    Vector<T, 3> operator-(const Vector<T, 3> &other, T val);

    template <typename T>
    Vector<T, 3> operator-(const Vector<T, 3> &other);

    template <typename T>
    Vector<T, 3> operator*(const Vector<T, 3> &other1, const Vector<T, 3> &other2);

    template <typename T>
    Vector<T, 3> operator*(T val, const Vector<T, 3> &other);

    template <typename T>
    Vector<T, 3> operator*(const Vector<T, 3> &other, T val);

    template <typename T>
    Vector<T, 3> operator/(const Vector<T, 3> &other1, const Vector<T, 3> &other2);

    template <typename T>
    Vector<T, 3> operator/(T val, const Vector<T, 3> &other);

    template <typename T>
    Vector<T, 3> operator/(const Vector<T, 3> &other, T val);

    template <typename T>
    Vector<T, 3> min(const Vector<T, 3> &other1, const Vector<T, 3> &other2);

    template <typename T>
    Vector<T, 3> max(const Vector<T, 3> &other1, const Vector<T, 3> &other2);

    template <typename T>
    Vector<T, 3> clamp(const Vector<T, 3> &s, const Vector<T, 3> &low, const Vector<T, 3> &high);

    template <typename T>
    Vector<T, 3> ceil(const Vector<T, 3> &other);

    template <typename T>
    Vector<T, 3> floor(const Vector<T, 3> &other);

    typedef Vector<float, 3> Vector3F;
    typedef Vector<double, 3> Vector3D;

    template <>
    constexpr Vector3F zero<Vector3F>()
    {
        return Vector3F(0.f, 0.f, 0.f);
    }
    template <>
    constexpr Vector3D zero<Vector3D>()
    {
        return Vector3D(0.0, 0.0, 0.0);
    };

    template <typename T>
    struct ScalarType<Vector3<T>>
    {
        typedef T value;
    };
    template <typename T>
    Vector<T, 3> CatmullRom(const Vector<T, 3> &v0, const Vector<T, 3> &v1,
                            const Vector<T, 3> &v2, const Vector<T, 3> &v3, T f);

}

#include "detail/vector3-inl.h"
#endif
