#ifndef INCLUDE_BIG_VECTOR_EXPRESSION_INL_H_
#define INCLUDE_BIG_VECTOR_EXPRESSION_INL_H_

namespace big
{

    template <typename T, typename E>
    std::size_t VectorExpression<T, E>::size()
    {
        return static_cast<const E &>(*this).size();
        std::cout << "father size\n"<<std::endl;
        // 这里实现了静态多态，看上去是使用基类的size()实际上使用的是子类的size()
    }

    template <typename T, typename E>
    const E &VectorExpression<T, E>::operator()() const
    {
        return static_cast<const E &>(*this);
    }

    template <typename T, typename E, typename Op>
    VectorUnaryOp<T, E, Op>::VectorUnaryOp(const E &other) : _u(other._u), _op() {}

    template <typename T, typename E, typename Op>
    std::size_t VectorUnaryOp<T, E, Op>::size() const
    {
        return _u.size();
    }

    template <typename T, typename E, typename Op>
    T VectorUnaryOp<T, E, Op>::operator[](std::size_t i) const
    {
        return _op(_u[i]);
    }

    template <typename T, typename E1, typename E2, typename Op>
    VectorBinaryOp<T, E1, E2, Op>::VectorBinaryOp(const E1 &u, const E2 &v) : _u(u), _v(v), _op()
    {
        assert(_u.size() == _v.size() && "input expressions have different size.");
    }

    template <typename T, typename E1, typename E2, typename Op>
    std::size_t VectorBinaryOp<T, E1, E2, Op>::size() const
    {
        return _u.size();
    }

    template <typename T, typename E1, typename E2, typename Op>
    T VectorBinaryOp<T, E1, E2, Op>::operator[](std::size_t i) const
    {
        return _op(_u[i], _v[i]);
    }

    template <typename T, typename E, typename Op>
    VectorScalarBinaryOp<T, E, Op>::VectorScalarBinaryOp(const E &u, const T &v) : _u(u), _v(v), _op() {}

    template <typename T, typename E, typename Op>
    std::size_t VectorScalarBinaryOp<T, E, Op>::size() const
    {
        return _u.size();
    }

    template <typename T, typename E, typename Op>
    T VectorScalarBinaryOp<T, E, Op>::operator[](std::size_t i) const
    {
        return _op(_u[i], _v);
    }

    template <typename T, typename E>
    VectorScalarAdd<T, E> operator+(const T &a, const VectorExpression<T, E> &b)
    {
        return VectorScalarAdd(b(), a); // constructor(operator(), T).
    }

    template <typename T, typename E1, typename E2>
    VectorAdd<T, E1, E2> operator+(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b)
    {
        return VectorAdd(a(), b()); // operator()
    }

    template <typename T, typename E>
    VectorScalarAdd<T, E> operator+(const VectorExpression<T, E> &a, const T &b)
    {
        return VectorScalarAdd(a(), b); // constructor(operator(), T).
    }

    template <typename T, typename E1, typename E2>
    VectorSub<T, E1, E2> operator-(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b)
    {
        return VectorSub(a(), b());
    }

    template <typename T, typename E>
    VectorScalarSub<T, E> operator-(const VectorExpression<T, E> &a, const T &b)
    {
        return VectorScalarSub(a(), b);
    }

    template <typename T, typename E>
    VectorScalarRSub<T, E> operator-(const T &a, const VectorExpression<T, E> &b)
    {
        return VectorScalarSub(b(), a);
    }

    template <typename T, typename E1, typename E2>
    VectorMul<T, E1, E2> operator*(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b)
    {
        return VectorMul(a(), b());
    }

    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const VectorExpression<T, E> &a, const T &b)
    {
        return VectorScalarMul(a(), b);
    }

    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const T &a, const VectorExpression<T, E> &b)
    {
        return VectorScalarMul(b(), a);
    }
    template <typename T, typename E1, typename E2>
    VectorDiv<T, E1, E2> operator/(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b)
    {
        return VectorDiv(a(), b());
    }

    template <typename T, typename E>
    VectorScalarDiv<T, E> operator/(const VectorExpression<T, E> &a, const T &b)
    {
        return VectorScalarDiv(a(), b);
    }

    template <typename T, typename E>
    VectorScalarRDiv<T, E> operator/(const T &a, const VectorExpression<T, E> &b)
    {
        return VectorScalarRDiv(b(), a);
    }

} // namespace big

#endif