#ifndef INCLUDE_BIG_MATRIX_H_
#define INCLUDE_BIG_MATRIX_H_
#include "matrix_expression.h"
#include <limits>
#include <cmath>
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
        // I don't know when the assert below will be called.
        static_assert(!(M == 2 && N == 2) && !(M == 3 && N == 3), "Use specialized matrix.");
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

        constexpr Size2 size() const;

        void set(const T &s);

        void setDiagonal(const T &s);

        void setOffDiagonal(const T &s);

        template <typename E>
        void setRow(std::size_t i, const VectorExpression<T, E> &row);

        template <typename E>
        void setCol(std::size_t j, const VectorExpression<T, E> &col);

        template <typename E>
        bool isEqual(const MatrixExpression<T, E> &other) const;

        template <typename E>
        bool isSimilar(const MatrixExpression<T, E> &other, double tol = std::numeric_limits<double>::epsilon()) const;

        constexpr bool isSquare() const;

        constexpr std::size_t rows() const;

        constexpr std::size_t cols() const;

        T *data();

        const T *const data() const;

        Iterator begin();

        ConstIterator begin() const;

        Iterator end();

        ConstIterator end() const;

        MatrixScalarAdd<T, Matrix> add(const T &s) const;

        template <typename E>
        MatrixAdd<T, Matrix, E> add(const E &m) const;

        MatrixScalarSub<T, Matrix> sub(const T &s) const;

        template <typename E>
        MatrixSub<T, Matrix, E> sub(const E &m) const;

        MatrixScalarMul<T, Matrix> mul(const T &s) const;

        template <typename VE>
        MatrixVectorMul<T, Matrix, VE> mul(const VectorExpression<T, VE> &v) const;

        template <std::size_t L>
        MatrixMul<T, Matrix, Matrix<T, N, L>> mul(const Matrix<T, N, L> &m) const;

        MatrixScalarDiv<T, Matrix> div(const T &s) const;

        MatrixScalarAdd<T, Matrix> radd(const T &s) const;

        template <typename E>
        MatrixAdd<T, Matrix, E> radd(const E &m) const;

        MatrixScalarRSub<T, Matrix> rsub(const T &s) const;

        template <typename E>
        MatrixSub<T, Matrix, E> rsub(const E &m) const;

        MatrixScalarMul<T, Matrix> rmul(const T &s) const;

        // m * this
        template <std::size_t L>
        MatrixMul<T, Matrix<T, L, M>, Matrix> rmul(const Matrix<T, L, M> &m) const;

        MatrixScalarDiv<T, Matrix> rdiv(const T &s) const;

        void iadd(const T &s);

        template <typename E>
        void iadd(const E &m);

        void isub(const T &s);

        template <typename E>
        void isub(const E &m);

        void imul(const T &s);

        template <typename E>
        void imul(const E &m);

        void idiv(const T &s);

        template <typename E>
        void idiv(const E &m);

        void transpose();

        void invert();

        T sum() const;

        T avg() const;

        T min() const;

        T max() const;

        T absmin() const;

        T absmax() const;

        T trace() const;

        T determinant() const;

        void show() const;

        MatrixDiagonal<T, Matrix> diagonal() const;

        MatrixDiagonal<T, Matrix> offDiagonal() const;

        MatrixTriangular<T, Matrix> strictLowerTri() const;

        MatrixTriangular<T, Matrix> stricitUpperTri() const;

        MatrixTriangular<T, Matrix> lowerTri() const;

        MatrixTriangular<T, Matrix> upperTri() const;

        Matrix<T, N, M> transposed() const;

        Matrix inverse() const;

        template <typename U>
        MatrixTypeCast<T, Matrix, U> castTo() const;

        template <typename E>
        Matrix &operator=(const MatrixExpression<T, E> &other);

        //! \brief I think the function below is same as above.
        Matrix &operator=(const Matrix &other);

        Matrix &operator+=(T &s);

        template <typename E>
        Matrix &operator+=(const E &m);

        Matrix &operator-=(T &s);
        template <typename E>
        Matrix &operator-=(const E &m);

        Matrix &operator*=(T &s);

        template <typename E>
        Matrix &operator*=(const E &m);

        Matrix &operator/=(T &s);

        template <typename E>
        bool operator==(const MatrixExpression<T, E> &m) const;

        template <typename E>
        bool operator!=(const E &other) const;

        T &operator[](std::size_t i);

        const T &operator[](std::size_t i) const;
        // return is T& while matrix_expression's ()() are all T
        T &operator()(std::size_t i, std::size_t j);

        const T &operator()(std::size_t i, std::size_t j) const;

        template <typename Callback>
        void forEach(Callback func) const;

        template <typename Callback>
        void forEachIndex(Callback func) const;

        static MatrixConstant<T> makeZero();

        static MatrixIdentity<T> makeIdentity();

    private:
        ContainerType _elements;

        template <typename... Params>
        void setRowAt(std::size_t i, T v, Params... params);

        void setRowAt(std::size_t i, T v);
    };

}
#include "detail/matrix-inl.h"
#endif