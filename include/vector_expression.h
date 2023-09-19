#ifndef INCLUDE_BIG_VECTOR_EXPRESSION_H_
#define INCLUDE_BIG_VECTOR_EXPRESSION_H_
#include <stddef.h>
#include <functors.h>
namespace big
{
    ////////////////////////////////////////////
    //// Curiously Recurring Template Pattern///
    ////////////////////////////////////////////
    //！
    //! \brief base class for vector expression.
    //! \param T Real number type.
    //! \param E Subclass type.
    template <typename T, typename E>
    class VectorExpression
    {
    public:
        std::size_t size();
        const E &operator()() const;
    };

    //! \brief expression for unary operations.
    //! \param T Real number type.
    //! \param E Input expression type.
    //! \param Op Unary operation.
    template <typename T, typename E, typename Op>
    class VectorUnaryOp : public VectorExpression<T, VectorUnaryOp<T, E, Op>>
    {
    public:
        VectorUnaryOp(const E &other);

        std::size_t size() const;

        T operator[](std::size_t i) const;

    private:
        const E &_u;
        Op _op;
    };

    //! \brief Matrix expression for type casting.
    template <typename T, typename E, typename U>
    using VectorTypeCast = VectorUnaryOp<T, E, TypeCast<T, U>>;

    //! \brief Vector expression for binary operations.
    //! \param T Real number type.
    //! \param E1 First input expression type.
    //! \param E2 Second input expression type.
    //! \param Op Binary operation.
    template <typename T, typename E1, typename E2, typename Op>
    class VectorBinaryOp : public VectorExpression<T, VectorBinaryOp<T, E1, E2, Op>>
    {
    public:
        VectorBinaryOp(const E1 &u, const E2 &v);

        std::size_t size() const;

        T operator[](std::size_t i) const;

    private:
        const E1 &_u;
        const E2 &_v;
        Op _op;
    };

    //! \brief vector expression for matrix -scalar binary operations.
    //! \param T Real number type.
    //! \param E Input expression type.
    //! \param Op Binary operation.
    template <typename T, typename E, typename Op>
    class VectorScalarBinaryOp : public VectorExpression<T, VectorScalarBinaryOp<T, E, Op>>
    {
    public:
        VectorScalarBinaryOp(const E &u, const T &v);

        std::size_t size() const;

        T operator[](std::size_t i) const;

    private:
        const E &_u;
        T _v;
        Op _op;
    };

    template <typename T, typename E1, typename E2>
    using VectorAdd = VectorBinaryOp<T, E1, E2, std::plus<T>>;

    template <typename T, typename E>
    using VectorScalarAdd = VectorScalarBinaryOp<T, E, std::plus<T>>;

    template <typename T, typename E1, typename E2>
    using VectorSub = VectorBinaryOp<T, E1, E2, std::minus<T>>;

    template <typename T, typename E>
    using VectorScalarSub = VectorScalarBinaryOp<T, E, std::minus<T>>;

    template <typename T, typename E>
    using VectorScalarRSub = VectorScalarBinaryOp<T, E, RMinus<T>>;

    template <typename T, typename E1, typename E2>
    using VectorMul = VectorBinaryOp<T, E1, E2, std::multiplies<T>>;

    template <typename T, typename E>
    using VectorScalarMul = VectorScalarBinaryOp<T, E, std::multiplies<T>>;

    template <typename T, typename E1, typename E2>
    using VectorDiv = VectorBinaryOp<T, E1, E2, std::divides<T>>;

    template <typename T, typename E>
    using VectorScalarDiv = VectorScalarBinaryOp<T, E, std::divides<T>>;

    template <typename T, typename E>
    using VectorScalarRDiv = VectorScalarBinaryOp<T, E, RDivides<T>>;

// in order to use static Polymorphism,  all the params use VectorExpression<>. 
    template <typename T, typename E1, typename E2>
    VectorAdd<T, E1, E2> operator+(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b);

    template <typename T, typename E>
    VectorScalarAdd<T, E> operator+(const VectorExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    VectorScalarAdd<T, E> operator+(const T &a, const VectorExpression<T, E> &b);

    template <typename T, typename E1, typename E2>
    VectorSub<T, E1, E2> operator-(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b);

    template <typename T, typename E>
    VectorScalarSub<T, E> operator-(const VectorExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    VectorScalarRSub<T, E> operator-(const T &a, const VectorExpression<T, E> &b);

    template <typename T, typename E1, typename E2>
    VectorMul<T, E1, E2> operator*(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b);

    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const VectorExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const T &a, const VectorExpression<T, E> &b);

    template <typename T, typename E1, typename E2>
    VectorDiv<T, E1, E2> operator/(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b);

    template <typename T, typename E>
    VectorScalarDiv<T, E> operator/(const VectorExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    VectorScalarRDiv<T, E> operator/(const T &a, const VectorExpression<T, E> &b);

} // namespace big
#include <detail/vector_expression-inl.h>
#endif