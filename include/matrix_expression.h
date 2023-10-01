#ifndef INCLUDE_BIG_MATRIX_EXPRESSION_H_
#define INCLUDE_BIG_MATRIX_EXPRESSION_H_
#include "size2.h"
#include "vector_expression.h"
namespace big
{
    template <typename T, typename E>
    class MatrixExpression
    {
    public:
        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        const E &operator()() const;
    };

    template <typename T>
    class MatrixConstant : MatrixExpression<T, MatrixConstant<T>>
    {
    public:
        MatrixConstant(std::size_t m, std::size_t n, const T &c);

        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        T operator()(std::size_t i, std::size_t j) const;

    private:
        std::size_t _m;
        std::size_t _n;
        T _c;
    };

    template <typename T>
    class MatrixIdentity : MatrixExpression<T, MatrixIdentity<T>>
    {
    public:
        MatrixIdentity(std::size_t m);

        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        T operator()(std::size_t i, std::size_t j) const;

    private:
        std::size_t _m;
    };

    template <typename T, typename E, typename Op>
    class MatrixUnaryOp : public MatrixExpression<T, MatrixUnaryOp<T, E, Op>>
    {
    public:
        MatrixUnaryOp(const E &u);

        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        T operator()(std::size_t i, std::size_t j) const;

    private:
        const E &_u;
        Op _op;
    };

    template <typename T, typename E>
    class MatrixDiagonal : public MatrixExpression<T, MatrixDiagonal<T, E>>
    {
    public:
        MatrixDiagonal(const E &u, bool isDiag);

        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        T operator()(std::size_t i, std::size_t j) const;

    private:
        const E &_u;
        bool _isDiag;
    };

    template <typename T, typename E>
    class MatrixTriangular : public MatrixExpression<T, MatrixTriangular<T, E>>
    {
    public:
        MatrixTriangular(const E &u, bool isUpper, bool isStrict);

        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        T operator()(std::size_t i, std::size_t j) const;

    private:
        const E &_u;
        bool _isUpper;
        bool _isStrict;
    };

    // T->U
    template <typename T, typename E, typename U>
    using MatrixTypeCast = MatrixUnaryOp<T, E, TypeCast<T, U>>;
    //

    template <typename T, typename E1, typename E2, typename Op>
    class MatrixBinaryOp : public MatrixExpression<T, MatrixBinaryOp<T, E1, E2, Op>>
    {
    public:
        MatrixBinaryOp(const E1 &u, const E2 &v);

        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        T operator()(std::size_t i, std::size_t j) const;

    private:
        const E1 &_u;
        const E2 &_v;
        Op _op;
    };

    template <typename T, typename E, typename Op>
    class MatrixScalarBinaryOp : public MatrixExpression<T, MatrixScalarBinaryOp<T, E, Op>>
    {
    public:
        MatrixScalarBinaryOp(const E &u, const T &v);

        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        T operator()(std::size_t i, std::size_t j) const;

    private:
        const E &_u;
        T _v;
        Op _op;
    };

    template <typename T, typename ME, typename VE>
    class MatrixVectorMul : public VectorExpression<T, MatrixVectorMul<T, ME, VE>> // Father is VectorExpression, because Matrix * Vector =VE
    {
    public:
        MatrixVectorMul(const ME &m, const VE &v);

        std::size_t size() const;

        T operator[](std::size_t i) const;

    private:
        const ME &_m;
        const VE &_v;
    };

    template <typename T, typename E1, typename E2>
    class MatrixMul : public MatrixExpression<T, MatrixMul<T, E1, E2>> // Father is VectorExpression, because Matrix * Vector =VE
    {
    public:
        MatrixMul(const E1 &u, const E2 &v);

        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        T operator()(std::size_t i, std::size_t j) const;

    private:
        const E1 &_u;
        const E2 &_v;
    };

    template <typename T, typename E1, typename E2>
    using MatrixAdd = MatrixBinaryOp<T, E1, E2, std::plus<T>>;

    template <typename T, typename E>
    using MatrixScalarAdd = MatrixScalarBinaryOp<T, E, std::plus<T>>;

    template <typename T, typename E1, typename E2>
    using MatrixSub = MatrixBinaryOp<T, E1, E2, std::minus<T>>;

    template <typename T, typename E>
    using MatrixScalarSub = MatrixScalarBinaryOp<T, E, std::minus<T>>;

    template <typename T, typename E>
    using MatrixScalarRSub = MatrixScalarBinaryOp<T, E, RMinus<T>>;

    template <typename T, typename E>
    using MatrixScalarMul = MatrixScalarBinaryOp<T, E, std::multiplies<T>>;

    template <typename T, typename E>
    using MatrixScalarDiv = MatrixScalarBinaryOp<T, E, std::divides<T>>;

    template <typename T, typename E>
    using MatrixScalarRDiv = MatrixScalarBinaryOp<T, E, RDivides<T>>;

    template <typename T, typename E1, typename E2>
    MatrixAdd<T, E1, E2> operator+(const MatrixExpression<T, E1> &a, const MatrixExpression<T, E2> &b);

    template <typename T, typename E>
    MatrixScalarAdd<T, E> operator+(const MatrixExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    MatrixScalarAdd<T, E> operator+(const T &a, const MatrixExpression<T, E> &b);

    template <typename T, typename E1, typename E2>
    MatrixSub<T, E1, E2> operator-(const MatrixExpression<T, E1> &a, const MatrixExpression<T, E2> &b);

    template <typename T, typename E>
    MatrixScalarSub<T, E> operator-(const MatrixExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    MatrixScalarRSub<T, E> operator-(const T &a, const MatrixExpression<T, E> &b);

    template <typename T, typename E>
    MatrixScalarRSub<T, E> operator-(const MatrixExpression<T, E> &a);

    template <typename T, typename E1, typename E2>
    MatrixMul<T, E1, E2> operator*(const MatrixExpression<T, E1> &a, const MatrixExpression<T, E2> &b);

    template <typename T, typename E>
    MatrixScalarMul<T, E> operator*(const MatrixExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    MatrixScalarMul<T, E> operator*(const T &a, const MatrixExpression<T, E> &b);

    template <typename T, typename E>
    MatrixScalarDiv<T, E> operator/(const MatrixExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    MatrixScalarRDiv<T, E> operator/(const T &a, const MatrixExpression<T, E> &b);

}

#include "detail/matrix_expression-inl.h"

#endif