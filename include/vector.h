#ifndef INCLUDE_BIG_VECTOR_H_
#define INCLUDE_BIG_VECTOR_H_
#include "array_accessor1.h"
#include "constants.h"
#include "type_helpers.h"
#include "vector_expression.h"
#include "math_utils.h"
#include <array>
#include <type_traits>
namespace big
{

    template <typename T, std::size_t N>
    class Vector final : public VectorExpression<T, Vector<T, N>>
    {
    public:
        static_assert(N > 0, "Size of static-sized vector should be greater than 0.");
        static_assert(std::is_floating_point<T>::value, "Vector only can be instantiated with float point types.");

        typedef std::array<T, N> ContainerType;

        Vector();

        template <typename... Params>
        explicit Vector(Params... params);

        void set(const T &s);

        template <typename U>
        Vector(std::initializer_list<U> &lst);

        template <typename U>
        void set(std::initializer_list<U> &lst);

        template <typename E>
        Vector(const VectorExpression<T, E> &other);

        template <typename E>
        void set(const VectorExpression<T, E> &other);

        constexpr std::size_t size() const;

        Vector(const Vector &other);

        void swap(Vector &other);

        void setZero();

        void normalize();

        T *data();

        const T *const data() const;

        typename ContainerType::iterator begin();

        typename ContainerType::const_iterator begin() const;

        typename ContainerType::iterator end();

        typename ContainerType::const_iterator end() const;

        ArrayAccessor<T, 1> accessor();

        ConstArrayAccessor<T, 1> ConstAccessor() const;

        T &at(std::size_t i);

        const T &at(std::size_t i) const;

        T sum() const;

        T avg() const;

        T min() const;

        T max() const;

        T absmin() const;

        T absmax() const;

        std::size_t dominantAxis() const;

        std::size_t subminantAxis() const;

        VectorScalarDiv<T, Vector> normalized() const;

        T length() const;

        T lengthSquared() const;

        // U is the type convert to, T is origin
        template <typename U>
        VectorTypeCast<U, Vector, T> castTo() const;

        template <typename E>
        bool isEqual(const E &other) const;

        template <typename E>
        bool isSimilar(const E &other, T epsilon = std::numeric_limits<T>::epsilon()) const;

        template <typename E>
        T distanceTo(const E &other) const;

        template <typename E>
        T distanceSquaredTo(const E &other) const;

        template <typename E>
        T dot(const E &v) const;

        template <typename Callback>
        void forEach(Callback func) const;

        template <typename Callback>
        void forEachIndex(Callback func) const;

        template <typename E>
        VectorAdd<T, Vector, E> add(const E &v) const;

        VectorScalarAdd<T, Vector> add(const T &s) const;

        template <typename E>
        VectorSub<T, Vector, E> sub(const E &v) const;

        VectorScalarSub<T, Vector> sub(const T &s) const;

        template <typename E>
        VectorMul<T, Vector, E> mul(const E &v) const;

        VectorScalarMul<T, Vector> mul(const T &s) const;

        template <typename E>
        VectorDiv<T, Vector, E> div(const E &v) const;

        VectorScalarDiv<T, Vector> div(const T &s) const;

        template <typename E>
        VectorSub<T, Vector, E> rsub(const E &v) const;

        VectorScalarRSub<T, Vector> rsub(const T &s) const;

        template <typename E>
        VectorDiv<T, Vector, E> rdiv(const E &v) const;

        VectorScalarRDiv<T, Vector> rdiv(const T &s) const;

        void iadd(const T &s);

        template <typename E>
        void iadd(const E &v);

        void isub(const T &s);

        template <typename E>
        void isub(const E &v);

        void imul(const T &s);

        template <typename E>
        void imul(const E &v);

        void idiv(const T &s);

        template <typename E>
        void idiv(const E &v);

        T &operator[](std::size_t i);

        const T &operator[](std::size_t i) const;

        template <typename E>
        Vector &operator=(const VectorExpression<T, E> &other);

        template <typename U>
        Vector &operator=(const std::initializer_list<U> &lst);

        Vector &operator+=(T &val);

        template <typename E>
        Vector &operator+=(const E &other);

        Vector &operator-=(T &val);
        template <typename E>
        Vector &operator-=(const E &other);

        Vector &operator*=(T &val);

        template <typename E>
        Vector &operator*=(const E &other);

        Vector &operator/=(T &val);

        template <typename E>
        Vector &operator/=(const E &other);

        template <typename E>
        bool operator==(const E &other) const;

        template <typename E>
        bool operator!=(const E &other) const;

    private:
        ContainerType _elements;

        template <typename... Params>
        void setAt(std::size_t i, T v, Params... params);

        void setAt(std::size_t i, T v);
    };

    
    template <typename T, std::size_t N>
    struct ScalarType<Vector<T, N>>
    {
        typedef T value;
    };

} // namespace big
#include "detail/vector-inl.h"
#endif