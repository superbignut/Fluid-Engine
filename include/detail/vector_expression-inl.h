#ifndef INCLUDE_BIG_VECTOR_EXPRESSION_INL_H_
#define INCLUDE_BIG_VECTOR_EXPRESSION_INL_H_

namespace big
{

    template <typename T, typename E>
    std::size_t VectorExpression<T, E>::size()const
    {
        return static_cast<const E &>(*this).size();
        // 这里实现了静态多态，看上去是使用基类的size()实际上使用的是子类的size()
    }

    template <typename T, typename E>
    const E &VectorExpression<T, E>::operator()() const
    {
        return static_cast<const E &>(*this);
    }

    template <typename T, typename E, typename Op>
    VectorUnaryOp<T, E, Op>::VectorUnaryOp(const E &other) : _u(other), _op() {}

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
        return _v.size();// _v i different with _u 
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
        return VectorScalarAdd<T, E>(b(), a); // constructor(operator(), T).
    }

    template <typename T, typename E1, typename E2>
    VectorAdd<T, E1, E2> operator+(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b)
    {
        return VectorAdd<T, E1, E2>(a(), b()); // operator()
    }

    template <typename T, typename E>
    VectorScalarAdd<T, E> operator+(const VectorExpression<T, E> &a, const T &b)
    {
        return VectorScalarAdd<T, E>(a(), b); // constructor(operator(), T).
    }

    template <typename T, typename E1, typename E2>
    VectorSub<T, E1, E2> operator-(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b)
    {
        return VectorSub<T, E1, E2>(a(), b());
    }

    template <typename T, typename E>
    VectorScalarSub<T, E> operator-(const VectorExpression<T, E> &a, const T &b)
    {
        return VectorScalarSub<T, E>(a(), b);
    }

    template <typename T, typename E>
    VectorScalarRSub<T, E> operator-(const T &a, const VectorExpression<T, E> &b)
    {
        return VectorScalarRSub<T, E>(b(), a);
    }
    template <typename T, typename E>
    VectorScalarRSub<T, E> operator-(const VectorExpression<T, E> &a)
    {
        return VectorScalarRSub<T, E>(a(), 0);
    }
    template <typename T, typename E1, typename E2>
    VectorMul<T, E1, E2> operator*(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b)
    {
        return VectorMul<T, E1, E2>(a(), b());
    }

    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const VectorExpression<T, E> &a, const T &b)
    {
        return VectorScalarMul(a(), b);
    }

    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const T &a, const VectorExpression<T, E> &b)
    {
        return VectorScalarMul<T, E>(b(), a);
    }
    template <typename T, typename E1, typename E2>
    VectorDiv<T, E1, E2> operator/(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b)
    {
        return VectorDiv<T, E1, E2>(a(), b());
    }

    template <typename T, typename E>
    VectorScalarDiv<T, E> operator/(const VectorExpression<T, E> &a, const T &b)
    {
        return VectorScalarDiv<T, E>(a(), b);
    }

    template <typename T, typename E>
    VectorScalarRDiv<T, E> operator/(const T &a, const VectorExpression<T, E> &b)
    {
        return VectorScalarRDiv<T, E>(b(), a);
    }

} // namespace big

#endif