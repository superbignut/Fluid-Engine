#ifndef INCLUDE_BIG_MATRIX_H_
#define INCLUDE_BIG_MATRIX_H_
#include "matrix_expression.h"
namespace big
{
  //! datas were stored in an array j + cols * i =(i, j)
  //! cols is the inner size
  //! rows is the outer size
  //! which is diff with array2
    template <typename T, std::size_t M, std::size_t N>
    class Matrix final : public MatrixExpression<T, Matrix<T, M, N>>
    {
    public:
        static_assert(M > 0, "row number need to be > 0.");
        static_assert(N > 0, "col number need to be > 0.");
        //static_assert(!(M == 2 && N == 2) && !(M == 3 && N == 3) && !(M == 4 && N == 4), "Use specialized matrix.");
        static_assert(std::is_floating_point<T>::value, "Matrix only can be instantiated with float point types.");

        typedef std::array<T, M * N> ContainerType;
        typedef typename ContainerType::iterator Iterator;
        typedef typename ContainerType::const_iterator ConstIterator;

        Matrix();

        template <typename... Params>
        explicit Matrix(Params... params);

        Matrix(const std::initializer_list<std::initializer_list<T>> &lst);

        void set(const std::initializer_list<std::initializer_list<T>> &lst);

        template <typename E>
        Matrix(const MatrixExpression<T, E> &other);

        template <typename E>
        void set(const MatrixExpression<T, E> &other);

        Matrix(const Matrix &other);

        void set(const Matrix &other);

        constexpr Size2 size() const;

        void set(const T &s);




        T &operator()(std::size_t i, std::size_t j);

        const T&operator()(std::size_t i , std::size_t j) const;


    private:
        ContainerType _elements;
        template <typename... Params>
        void setRowAt(std::size_t i, T v, Params... params);

        void setRowAt(std::size_t i, T v);
    };

}
#include "detail/matrix-inl.h"
#endif