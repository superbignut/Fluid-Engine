#ifndef INCLUDE_BIG_VECTOR_H_
#define INCLUDE_BIG_VECTOR_H_
#include "array_accessor.h"
#include "constants.h"
#include "type_helpers.h"
#include "vector_expression.h"

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

        template <typename ...Params>
        explicit Vector(Params... params);

        void set(const T &s);

        template<typename U>
        Vector(std::initializer_list<U>& lst);

        template<typename U>
        void set(std::initializer_list<U>& lst);

    private:
        ContainerType _elements;

        template<typename ...Params>
        void setAt(std::size_t i, T v, Params... params);

        void setAt(std::size_t i, T v);
    };

} // namespace big
#include "detail/vector-inl.h"
#endif