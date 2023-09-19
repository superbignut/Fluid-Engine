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
        
        template <typename E>
        T dot(const E &v) const;

    private:
        ContainerType _elements;

        template <typename... Params>
        void setAt(std::size_t i, T v, Params... params);

        void setAt(std::size_t i, T v);
    };

} // namespace big
#include "detail/vector-inl.h"
#endif