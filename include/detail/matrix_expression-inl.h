#ifndef INCLUDE_BIG_MATRIX_EXPRESSION_INL_H_
#define INCLUDE_BIG_MATRIX_EXPRESSION_INL_H_

namespace big
{

    template <typename T, typename E>
    Size2 MatrixExpression<T, E>::size() const
    {
        return static_cast<const E &>(*this).size();
    }

    template <typename T, typename E>
    std::size_t MatrixExpression<T, E>::rows() const
    {
        return static_cast<const E &>(*this).rows();
    }

    template <typename T, typename E>
    std::size_t MatrixExpression<T, E>::cols() const
    {
        return static_cast<const E &>(*this).cols();
    }

    template <typename T, typename E>
    const E &MatrixExpression<T, E>::operator()() const
    {
        return static_cast<const E &>(*this);
    }

    template <typename T>
    MatrixConstant<T>::MatrixConstant(std::size_t m, std::size_t n, const T &c) : _m(m), _n(n), _c(c) {}

    template <typename T>
    Size2 MatrixConstant<T>::size() const
    {
        return Size2(_m, _n);
    }

    template <typename T>
    std::size_t MatrixConstant<T>::rows() const
    {
        return _m;
    }
    template <typename T>
    std::size_t MatrixConstant<T>::cols() const
    {
        return _n;
    }

    template <typename T>
    T MatrixConstant<T>::operator()(std::size_t i, std::size_t j) const
    {
        return _c;
    }

    template <typename T>
    MatrixIdentity<T>::MatrixIdentity(std::size_t m) : _m(m) {}

    template <typename T>
    Size2 MatrixIdentity<T>::size() const
    {
        return Size2(_m, _m);
    }

    template <typename T>
    std::size_t MatrixIdentity<T>::rows() const
    {
        return _m;
    }
    template <typename T>
    std::size_t MatrixIdentity<T>::cols() const
    {
        return _m;
    }

    template <typename T>
    T MatrixIdentity<T>::operator()(std::size_t i, std::size_t j) const
    {
        return i == j ? static_cast<T>(1) : static_cast<T>(0);
    }

    template <typename T, typename E, typename Op>
    MatrixUnaryOp<T, E, Op>::MatrixUnaryOp(const E &u) : _u(u) {}

    template <typename T, typename E, typename Op>
    Size2 MatrixUnaryOp<T, E, Op>::size() const
    {
        return _u.size();
    }

    template <typename T, typename E, typename Op>
    std::size_t MatrixUnaryOp<T, E, Op>::rows() const
    {
        return _u.rows();
    }
    template <typename T, typename E, typename Op>
    std::size_t MatrixUnaryOp<T, E, Op>::cols() const
    {
        return _u.cols();
    }

    template <typename T, typename E, typename Op>
    T MatrixUnaryOp<T, E, Op>::operator()(std::size_t i, std::size_t j) const
    {
        return _op(_u(i, j));
    }

    template <typename T, typename E>
    MatrixDiagonal<T, E>::MatrixDiagonal(const E &u, bool isDiag) : _u(u), _isDiag(isDiag) {}

    template <typename T, typename E>
    Size2 MatrixDiagonal<T, E>::size() const
    {
        return _u.size();
    }

    template <typename T, typename E>
    std::size_t MatrixDiagonal<T, E>::rows() const
    {
        return _u.rows();
    }

    template <typename T, typename E>
    std::size_t MatrixDiagonal<T, E>::cols() const
    {
        return _u.cols();
    }

    template <typename T, typename E>
    T MatrixDiagonal<T, E>::operator()(std::size_t i, std::size_t j) const
    {
        if (_isDiag)
            return i == j ? _u(i, j) : 0;
        else
            return i != j ? _u(i, j) : 0;
    }

    template <typename T, typename E>
    MatrixTriangular<T, E>::MatrixTriangular(const E &u, bool isUpper, bool isStrict) : _u(u), _isUpper(isUpper), _isStrict(isStrict) {}

    template <typename T, typename E>
    Size2 MatrixTriangular<T, E>::size() const
    {
        return _u.size();
    }

    template <typename T, typename E>
    std::size_t MatrixTriangular<T, E>::rows() const
    {
        return _u.rows();
    }

    template <typename T, typename E>
    std::size_t MatrixTriangular<T, E>::cols() const
    {
        return _u.cols();
    }

    template <typename T, typename E>
    T MatrixTriangular<T, E>::operator()(std::size_t i, std::size_t j) const
    {
        if (i < j)
            return (_isUpper) ? _u(i, j) : 0;
        else if (i > j)
            return (!_isUpper) ? _u(i, j) : 0;
        else
            return (_isStrict) ? 0 : _u(i, j);
    }

    template <typename T, typename E1, typename E2, typename Op>
    MatrixBinaryOp<T, E1, E2, Op>::MatrixBinaryOp(const E1 &u, const E2 &v) : _u(u), _v(v), _op()
    {
        assert(_u.size() == _v.size() && "_u and _v have different size.");
    }

    template <typename T, typename E1, typename E2, typename Op>
    Size2 MatrixBinaryOp<T, E1, E2, Op>::size() const
    {

        return _u.size();
    }

    template <typename T, typename E1, typename E2, typename Op>
    std::size_t MatrixBinaryOp<T, E1, E2, Op>::rows() const
    {
        return _u.rows();
    }
    template <typename T, typename E1, typename E2, typename Op>
    std::size_t MatrixBinaryOp<T, E1, E2, Op>::cols() const
    {
        return _u.cols();
    }

    template <typename T, typename E1, typename E2, typename Op>
    T MatrixBinaryOp<T, E1, E2, Op>::operator()(std::size_t i, std::size_t j) const
    {
        return _op(_u(i, j), _v(i, j));
    }

    template <typename T, typename E, typename Op>
    MatrixScalarBinaryOp<T, E, Op>::MatrixScalarBinaryOp(const E &u, const T &v) : _u(u), _v(v), _op() {}

    template <typename T, typename E, typename Op>
    Size2 MatrixScalarBinaryOp<T, E, Op>::size() const
    {

        return _u.size();
    }

    template <typename T, typename E, typename Op>
    std::size_t MatrixScalarBinaryOp<T, E, Op>::rows() const
    {
        return _u.rows();
    }
    template <typename T, typename E, typename Op>
    std::size_t MatrixScalarBinaryOp<T, E, Op>::cols() const
    {
        return _u.cols();
    }

    template <typename T, typename E, typename Op>
    T MatrixScalarBinaryOp<T, E, Op>::operator()(std::size_t i, std::size_t j) const
    {
        return _op(_u(i, j), _v);
    }

    template <typename T, typename ME, typename VE>
    MatrixVectorMul<T, ME, VE>::MatrixVectorMul(const ME &m, const VE &v) : _m(m), _v(v)
    {
        assert(_m.cols() == _v.size() && "matrix columns diff with vector size.");
    }

    template <typename T, typename ME, typename VE>
    std::size_t MatrixVectorMul<T, ME, VE>::size() const
    {
        return _m.rows();
    }

    template <typename T, typename ME, typename VE>
    T MatrixVectorMul<T, ME, VE>::operator[](std::size_t i) const
    {
        T sum = 0;
        const std::size_t n = _m.cols();
        for (int j = 0; j < n; ++j)
        {
            sum += _m(i, j) * _v[j];
        }
        return sum;
    }

    template <typename T, typename E1, typename E2>
    MatrixMul<T, E1, E2>::MatrixMul(const E1 &u, const E2 &v) : _u(u), _v(v)
    {
        assert(_u.cols() == _v.rows() && "matrix1 cols diff with matrix2 rows.");
    }

    template <typename T, typename E1, typename E2>
    Size2 MatrixMul<T, E1, E2>::size() const
    {

        return Size2(_u.rows(), _v.cols());
    }

    template <typename T, typename E1, typename E2>
    std::size_t MatrixMul<T, E1, E2>::rows() const
    {
        return _u.rows();
    }
    template <typename T, typename E1, typename E2>
    std::size_t MatrixMul<T, E1, E2>::cols() const
    {
        return _v.cols();
    }

    template <typename T, typename E1, typename E2>
    T MatrixMul<T, E1, E2>::operator()(std::size_t i, std::size_t j) const
    {

        const std::size_t n = _u.cols();
        T sum = 0;
        for (int k = 0; k < n; ++k)
        {
            sum += _u(i, k) * _v(k, j);
        }
        return sum;
    }

    template <typename T, typename E1, typename E2>
    MatrixAdd<T, E1, E2> operator+(const MatrixExpression<T, E1> &a, const MatrixExpression<T, E2> &b)
    {
        return MatrixAdd<T, E1, E2>(a(), b());
    }
    template <typename T, typename E>
    MatrixScalarAdd<T, E> operator+(const MatrixExpression<T, E> &a, const T &b)
    {
        return MatrixScalarAdd<T, E>(a(), b);
    }

    template <typename T, typename E>
    MatrixScalarAdd<T, E> operator+(const T &a, const MatrixExpression<T, E> &b)
    {
        return MatrixScalarAdd<T, E>(b(), a);
    }

    template <typename T, typename E1, typename E2>
    MatrixSub<T, E1, E2> operator-(const MatrixExpression<T, E1> &a, const MatrixExpression<T, E2> &b)
    {
        return MatrixSub<T, E1, E2>(a(), b());
    }

    template <typename T, typename E>
    MatrixScalarSub<T, E> operator-(const MatrixExpression<T, E> &a, const T &b)
    {
        return MatrixScalarSub<T, E>(a(), b);
    }

    template <typename T, typename E>
    MatrixScalarRSub<T, E> operator-(const T &a, const MatrixExpression<T, E> &b)
    {
        return MatrixScalarRSub<T, E>(a(), b);
    }

    template <typename T, typename E>
    MatrixScalarRSub<T, E> operator-(const MatrixExpression<T, E> &a)
    {
        return MatrixScalarRSub<T, E>(a(), 0);
    }
    template <typename T, typename E1, typename E2>
    MatrixMul<T, E1, E2> operator*(const MatrixExpression<T, E1> &a, const MatrixExpression<T, E2> &b)
    {
        return MatrixMul<T, E1, E2>(a(), b());
    }

    template <typename T, typename E1, typename E2>
    MatrixVectorMul<T, E1, E2> operator*(const MatrixExpression<T, E1> &m, const VectorExpression<T, E2> &v)
    {
        return MatrixVectorMul<T, E1, E2>(m(), v());
    }

    template <typename T, typename E>
    MatrixScalarMul<T, E> operator*(const MatrixExpression<T, E> &a, const T &b)
    {
        return MatrixScalarMul<T, E>(a(), b);
    }

    template <typename T, typename E>
    MatrixScalarMul<T, E> operator*(const T &a, const MatrixExpression<T, E> &b)
    {
        return MatrixScalarMul<T, E>(b(), a);
    }
    template <typename T, typename E>
    MatrixScalarDiv<T, E> operator/(const MatrixExpression<T, E> &a, const T &b)
    {
        return MatrixScalarDiv<T, E>(a(), b);
    }
    template <typename T, typename E>
    MatrixScalarRDiv<T, E> operator/(const T &a, const MatrixExpression<T, E> &b)
    {
        return MatrixScalarRDiv<T, E>(b(), a);
    }

}

#endif