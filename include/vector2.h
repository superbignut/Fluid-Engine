#ifndef INCLUDE_BIG_VECTOR2_H_
#define INCLUDE_BIG_VECTOR2_H_
#include "vector.h"
namespace big
{

    template <typename T>
    class Vector<T, 2> final
    { // no son
    public:
        static_assert(std::is_arithmetic<T>::value, "Vector only can be instantiated with arithmetic types.");

        T x;
        T y;

        constexpr Vector() : x(0), y(0) {}

        constexpr Vector(T x_, T y_) : x(x_), y(y_) {}

        template <typename U>
        Vector(const std::initializer_list<U> &lst);

        template <typename U>
        void set(const std::initializer_list<U> &lst);

        constexpr Vector(const Vector &v) : x(v.x), y(v.y) {} // copy construct.

        void set(T newX, T newY);

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

        T cross(const Vector &other) const;

        T rcross(const Vector &other) const;

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

        std::size_t domintAxis() const;

        std::size_t subminanAxis() const;

        Vector normalized() const;

        T length() const;

        T lengthSquared() const;

        T distanceTo(const Vector &other) const;

        T distanceSquaredTo(const Vector &other) const;

        Vector reflect(const Vector &normal) const;

        Vector project(const Vector &normal) const;

        // Counterclockwise rotate 90 degree in 2-D.
        Vector tangential() const;

        template <typename U>
        Vector<U, 2> castTo() const;

        constexpr bool isEqual(const Vector &other) const;

        constexpr bool isSimilar(const Vector &other, T epsilon = std::numeric_limits<T>::epsilon()) const;

        T &operator[](std::size_t i);

        const T &operator[](std::size_t i) const;

        Vector &operator=(const Vector &other);

        template <typename U>
        Vector &operator=(std::initializer_list<U> &lst);

        Vector &operator+=(T &val);

        Vector &operator+=(const Vector &other);

        Vector &operator-=(T &val);

        Vector &operator-=(const Vector &other);

        Vector &operator*=(T &val);

        Vector &operator*=(const Vector &other);

        Vector &operator/=(T &val);

        Vector &operator/=(const Vector &other);

        bool operator==(const Vector &other) const;

        bool operator!=(const Vector &other) const;
    };

    template <typename T>
    using Vector2 = Vector<T, 2>;

    template <typename T>
    Vector<T, 2> operator+(const Vector<T, 2> &other1, const Vector<T, 2> &other2);

    template <typename T>
    Vector<T, 2> operator+(T val, const Vector<T, 2> &other);

    template <typename T>
    Vector<T, 2> operator+(const Vector<T, 2> &other, T val);

    template <typename T>
    Vector<T, 2> operator+(const Vector<T, 2> &other);

    template <typename T>
    Vector<T, 2> operator-(const Vector<T, 2> &other1, const Vector<T, 2> &other2);

    template <typename T>
    Vector<T, 2> operator-(T val, const Vector<T, 2> &other);

    template <typename T>
    Vector<T, 2> operator-(const Vector<T, 2> &other, T val);

    template <typename T>
    Vector<T, 2> operator-(const Vector<T, 2> &other);

    template <typename T>
    Vector<T, 2> operator*(const Vector<T, 2> &other1, const Vector<T, 2> &other2);

    template <typename T>
    Vector<T, 2> operator*(T val, const Vector<T, 2> &other);

    template <typename T>
    Vector<T, 2> operator*(const Vector<T, 2> &other, T val);

    template <typename T>
    Vector<T, 2> operator/(const Vector<T, 2> &other1, const Vector<T, 2> &other2);

    template <typename T>
    Vector<T, 2> operator/(T val, const Vector<T, 2> &other);

    template <typename T>
    Vector<T, 2> operator/(const Vector<T, 2> &other, T val);

    template <typename T>
    Vector<T, 2> min(const Vector<T, 2> &other1, const Vector<T, 2> &other2);

    template <typename T>
    Vector<T, 2> max(const Vector<T, 2> &other1, const Vector<T, 2> &other2);

    template <typename T>
    Vector<T, 2> clamp(const Vector<T, 2> &s, const Vector<T, 2> &low, const Vector<T, 2> &high);

    template <typename T>
    Vector<T, 2> ceil(const Vector<T, 2> &other);

    template <typename T>
    Vector<T, 2> floor(const Vector<T, 2> &other);

    typedef Vector<float, 2> Vector2F;
    typedef Vector<double, 2> Vector2D;

    template <>
    constexpr Vector2F zero<Vector2F>()
    {
        return Vector2F(0.f, 0.f);
    }
    template <>
    constexpr Vector2D zero<Vector2D>()
    {
        return Vector2D(0.0, 0.0);
    };

    template <typename T>
    struct ScalarType<Vector2<T>>
    {
        typedef T value;
    };
    template <typename T>
    Vector<T, 2> monotonicCatmullRom(const Vector<T, 2>& v0, const Vector<T, 2>& v1,
                                     const Vector<T, 2>& v2, const Vector<T, 2>& v3, T f);
    
}

#include "detail/vector2-inl.h"
#endif
