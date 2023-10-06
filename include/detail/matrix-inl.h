#ifndef INCLUDE_BIG_MATRIX_INL_H_
#define INCLUDE_BIG_MATRIX_INL_H_
#include <stddef.h>

namespace big
{

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N>::Matrix()
    {
        _elements.fill(0);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename... Params>
    Matrix<T, M, N>::Matrix(Params... params)
    {
        static_assert(sizeof...(params) == M * N, "Invalid number of params.");
        setRowAt(0, params...);
    }

    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    Matrix<T, M, N>::Matrix(const MatrixExpression<T, E> &other)
    {
        assert(size() == other.size() && "matrix have diff size.");
        set(other);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    void Matrix<T, M, N>::set(const MatrixExpression<T, E> &other)
    {
        const E &expression = other();
        // forEachIndex is const member function, but *this is still been changed.
        forEachIndex([&](std::size_t i, std::size_t j)
                     { (*this)(i, j) = expression(i, j); });
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N>::Matrix(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        set(lst);
    }

    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::set(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        std::size_t rows = lst.size();
        std::size_t cols = (rows != 0) ? lst.begin()->size() : 0;

        assert(rows == M && cols == N && "row and col size can't match define.");
        auto rowIter = lst.begin();
        for (std::size_t i = 0; i < rows; ++i)
        {
            auto colIter = rowIter->begin();
            assert(cols == rowIter->size() && "Error width size in iniitalizer_list."); // because each inner initialize_list can have diff size.

            for (std::size_t j = 0; j < cols; ++j)
            {
                (*this)(i, j) = *colIter;
                ++colIter;
            }
            ++rowIter;
        }
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N>::Matrix(const Matrix &other)
    {
        set(other);
    }

    template <typename T, std::size_t M, std::size_t N>
    constexpr Size2 Matrix<T, M, N>::size() const
    {
        return Size2(rows(), cols());
    }

    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::set(const T &s)
    {
        _elements.fill(s);
    }

    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::setDiagonal(const T &s)
    {
        const std::size_t l = std::min(M, N);
        for (std::size_t i = 0; i < l; ++i)
        {
            (*this)(i, i) = s;
        }
    }
    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::setOffDiagonal(const T &s)
    {
        forEachIndex([&](std::size_t i, std::size_t j)
                     {
            if(i != j)
            {
                (*this)(i, j) = s;
            } });
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    void Matrix<T, M, N>::setRow(std::size_t i, const VectorExpression<T, E> &row)
    {
        const E &e = row();
        for (std::size_t j = 0; j < cols(); ++j)
        {
            (*this)(i, j) = e[j];
        }
    }

    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    void Matrix<T, M, N>::setCol(std::size_t j, const VectorExpression<T, E> &row)
    {
        const E &e = row();
        for (std::size_t i = 0; i < rows(); ++i)
        {
            (*this)(i, j) = e[i];
        }
    }

    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    bool Matrix<T, M, N>::isEqual(const MatrixExpression<T, E> &other) const
    {
        if (size() != other.size())
            return false;
        const E &e = other();
        for (std::size_t i = 0; i < M; ++i)
        {
            for (std::size_t j = 0; j < N; ++j)
            {
                if ((*this)(i, j) != e(i, j))
                    return false;
            }
        }
        return true;
    }

    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    bool Matrix<T, M, N>::isSimilar(const MatrixExpression<T, E> &other, double tol) const
    {
        if (size() != other.size())
            return false;
        for (std::size_t i = 0; i < M; ++i)
        {
            for (std::size_t j = 0; j < N; ++j)
            {
                if (std::fabs((*this)(i, j) - other(i, j)) > tol)
                    return false;
            }
        }
        return true;
    }

    template <typename T, std::size_t M, std::size_t N>
    constexpr bool Matrix<T, M, N>::isSquare() const
    {
        return M == N;
    }

    template <typename T, std::size_t M, std::size_t N>
    T *Matrix<T, M, N>::data()
    {
        return _elements.data();
    }

    template <typename T, std::size_t M, std::size_t N>
    const T *const Matrix<T, M, N>::data() const
    {
        return _elements.data();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename Matrix<T, M, N>::Iterator Matrix<T, M, N>::begin()
    {
        return _elements.begin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename Matrix<T, M, N>::ConstIterator Matrix<T, M, N>::begin() const
    {
        return _elements.begin();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename Matrix<T, M, N>::Iterator Matrix<T, M, N>::end()
    {
        return _elements.end();
    }

    template <typename T, std::size_t M, std::size_t N>
    typename Matrix<T, M, N>::ConstIterator Matrix<T, M, N>::end() const
    {
        return _elements.end();
    }

    template <typename T, std::size_t M, std::size_t N>
    MatrixScalarAdd<T, Matrix<T, M, N>> Matrix<T, M, N>::add(const T &s) const
    {
        return MatrixScalarAdd<T, Matrix>(*this, s);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    MatrixAdd<T, Matrix<T, M, N>, E> Matrix<T, M, N>::add(const E &m) const
    {
        return MatrixAdd<T, Matrix, E>(*this, m);
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixScalarSub<T, Matrix<T, M, N>> Matrix<T, M, N>::sub(const T &s) const
    {
        return MatrixScalarSub<T, Matrix>(*this, s);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    MatrixSub<T, Matrix<T, M, N>, E> Matrix<T, M, N>::sub(const E &m) const
    {
        return MatrixSub<T, Matrix, E>(*this, m);
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixScalarMul<T, Matrix<T, M, N>> Matrix<T, M, N>::mul(const T &s) const
    {
        return MatrixScalarMul<T, Matrix>(*this, s);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename VE>
    MatrixVectorMul<T, Matrix<T, M, N>, VE> Matrix<T, M, N>::mul(const VectorExpression<T, VE> &v) const
    {
        return MatrixVectorMul<T, Matrix, VE>(*this, v);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <std::size_t L>
    MatrixMul<T, Matrix<T, M, N>, Matrix<T, N, L>> Matrix<T, M, N>::mul(const Matrix<T, N, L> &m) const
    {
        return MatrixMul<T, Matrix<T, M, N>, Matrix<T, N, L>>(*this, m);
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixScalarDiv<T, Matrix<T, M, N>> Matrix<T, M, N>::div(const T &s) const
    {
        return MatrixScalarDiv<T, Matrix>(*this, s);
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixScalarAdd<T, Matrix<T, M, N>> Matrix<T, M, N>::radd(const T &s) const
    {
        return MatrixScalarAdd<T, Matrix>(*this, s);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    MatrixAdd<T, Matrix<T, M, N>, E> Matrix<T, M, N>::radd(const E &m) const
    {
        return MatrixAdd<T, Matrix, E>(*this, m);
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixScalarRSub<T, Matrix<T, M, N>> Matrix<T, M, N>::rsub(const T &s) const
    {
        return MatrixScalarRSub<T, Matrix>(*this, s);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    MatrixSub<T, Matrix<T, M, N>, E> Matrix<T, M, N>::rsub(const E &m) const
    {
        return MatrixSub<T, Matrix, Matrix>(m, *this);
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixScalarMul<T, Matrix<T, M, N>> Matrix<T, M, N>::rmul(const T &s) const
    {
        return MatrixScalarMul<T, Matrix>(*this, s);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <std::size_t L>
    MatrixMul<T, Matrix<T, L, M>, Matrix<T, M, N>> Matrix<T, M, N>::rmul(const Matrix<T, L, M> &m) const
    {
        return MatrixMul(m, *this);
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixScalarDiv<T, Matrix<T, M, N>> Matrix<T, M, N>::rdiv(const T &s) const
    {
        return MatrixScalarRDiv<T, Matrix>(*this, s);
    }

    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::iadd(const T &s)
    {
        return set(add(s));
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    void Matrix<T, M, N>::iadd(const E &m)
    {
        return set(add(m));
    }
    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::isub(const T &s)
    {
        return set(sub(s));
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    void Matrix<T, M, N>::isub(const E &m)
    {
        return set(sub(m));
    }
    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::imul(const T &s)
    {
        return set(mul(s));
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    void Matrix<T, M, N>::imul(const E &m)
    {
        return set(mul(m));
    }
    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::idiv(const T &s)
    {
        return set(div(s));
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    void Matrix<T, M, N>::idiv(const E &m)
    {
        return set(div(m));
    }

    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::transpose()
    {
        set(transposed());
    }

    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::invert()
    {
        // Computes inverse matrix using Gaussian elimination method.
        // https://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/
        assert(isSquare());
        std::size_t n = rows();
        Matrix &a = *this;
        Matrix rhs = makeIdentity(); // copy construct
        for (std::size_t i = 0; i < n; ++i)
        {
            // Search maxinum in column[i]
            T maxEl = std::fabs(a(i, i));
            std::size_t maxRow = i;
            for (int j = i + 1; j < n; ++j)
            {
                if (std::fabs(a(j, i)) > maxEl)
                {
                    maxEl = std::fabs(a(j, i));
                    maxRow = j;
                }
            }
            // swap
            if (maxRow != i)
            {
                for (std::size_t j = i; j < n; ++j)
                {
                    std::swap(a(maxRow, j), a(i, j));
                }
                for (std::size_t j = 0; j < n; ++j)
                {
                    std::swap(rhs(maxRow, j), rhs(i, j));
                }
            }
            //  compute :j iterates all the rows except ith
            for (std::size_t j = 0; j < n; ++j)
            {
                if (j == i)
                    continue;
                T c = -a(j, i) / a(i, i);
                for (std::size_t k = 0; k < n; ++k) // N * N * N = N^3
                {
                    rhs(j, k) += rhs(i, k) * c;
                    if (k == i)
                        a(j, k) = 0;
                    else if (k > i) // just calculate k > i
                        a(j, k) += a(i, k) * c;
                }
            }
        }
        // scale
        for (std::size_t j = 0; j < n; ++j)
        {
            assert(a(j,j) == 0 && "There is an error in Matrix inverse!!!");
            T c = 1 / a(j, j);
            for (std::size_t k = 0; k < n; ++k)
            {
                rhs(j, k) *= c;
            }
        }

        set(rhs);
    }
    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::show() const
    {
        forEachIndex([this](std::size_t i, std::size_t j)
                     {std::cout<< (*this)(i ,j);
            if(j < N - 1)
                std::cout<<"&";
            else
                std::cout<<std::endl; });
    }

    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::sum() const
    {
        T sum = 0;
        forEach([&](const T &s)
                { sum += s; });
        return sum;
    }
    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::avg() const
    {
        return sum() / (rows() * cols());
    }
    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::min() const
    {
        T ret = _elements.front();
        for (auto v : _elements)
        {
            ret = std::min(ret, v);
        }
        return ret;
    }
    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::max() const
    {
        T ret = _elements.front();
        for (auto v : _elements)
        {
            ret = std::max(ret, v);
        }
        return ret;
    }
    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::absmin() const
    {
        T ret = _elements.front();
        for (auto v : _elements)
        {
            ret = big::absmin(ret, v);
        }
        return ret;
    }
    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::absmax() const
    {
        T ret = _elements.front();
        for (auto v : _elements)
        {
            ret = big::absmax(ret, v);
        }
        return ret;
    }
    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::trace() const
    {
        assert(isSquare());
        T ret = 0;
        for (std::size_t i = 0; i < M; ++i)
        {
            ret += (*this)(i, i);
        }
    }
    template <typename T, std::size_t M, std::size_t N>
    T Matrix<T, M, N>::determinant() const
    {
        assert(isSquare());
        T ret = 1;
        std::size_t n = rows();
        Matrix a = *this;
        // Matrix rhs = makeIdentity(); // copy construct
        for (std::size_t i = 0; i < n; ++i)
        {
            // Search maxinum in column[i]
            T maxEl = std::fabs(a(i, i));
            std::size_t maxRow = i;
            for (int j = i + 1; j < n; ++j)
            {
                if (std::fabs(a(j, i)) > maxEl)
                {
                    maxEl = std::fabs(a(j, i));
                    maxRow = j;
                }
            }
            // swap
            if (maxRow != i)
            {
                for (std::size_t j = i; j < n; ++j)
                {
                    std::swap(a(maxRow, j), a(i, j));
                }
                ret *= -1;
                // for (std::size_t j = 0; j < n; ++j)
                // {
                //     std::swap(rhs(maxRow, j), rhs(i, j));
                // }
            }
            //  compute :j iterates all the rows except ith
            for (std::size_t j = 0; j < n; ++j)
            {
                if (j == i)
                    continue;
                T c = -a(j, i) / a(i, i);
                for (std::size_t k = 0; k < n; ++k)
                {
                    // rhs(j, k) += rhs(i, k) * c;
                    if (k == i)
                        a(j, k) = 0;
                    else if (k > i) // just calculate k > i
                        a(j, k) += a(i, k) * c;
                }
            }
        }
        for (std::size_t i = 0; i < M; ++i)
        {
            ret *= a(i, i);
        }
        return ret;
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixDiagonal<T, Matrix<T, M, N>> Matrix<T, M, N>::diagonal() const
    {
        return MatrixDiagonal<T, Matrix>(*this, true);
    }

    template <typename T, std::size_t M, std::size_t N>
    MatrixDiagonal<T, Matrix<T, M, N>> Matrix<T, M, N>::offDiagonal() const
    {
        return MatrixDiagonal<T, Matrix>(*this, false);
    }

    template <typename T, std::size_t M, std::size_t N>
    MatrixTriangular<T, Matrix<T, M, N>> Matrix<T, M, N>::strictLowerTri() const
    {
        // MatrixTriangular(const E &u, bool isUpper, bool isStrict);
        return MatrixTriangular<T, Matrix>(*this, false, true);
    }

    template <typename T, std::size_t M, std::size_t N>
    MatrixTriangular<T, Matrix<T, M, N>> Matrix<T, M, N>::stricitUpperTri() const
    {
        return MatrixTriangular<T, Matrix>(*this, true, true);
    }

    template <typename T, std::size_t M, std::size_t N>
    MatrixTriangular<T, Matrix<T, M, N>> Matrix<T, M, N>::lowerTri() const
    {
        return MatrixTriangular<T, Matrix>(*this, false, false);
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixTriangular<T, Matrix<T, M, N>> Matrix<T, M, N>::upperTri() const
    {
        return MatrixTriangular<T, Matrix>(*this, true, false);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename U>
    MatrixTypeCast<T, Matrix<T, M, N>, U> Matrix<T, M, N>::castTo() const
    {
        return MatrixTypeCast<T, Matrix, U>(*this);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    Matrix<T, M, N> &Matrix<T, M, N>::operator=(const MatrixExpression<T, E> &other)
    {
        set(other);
        return *this;
    }

    // template <typename T, std::size_t M, std::size_t N>
    // Matrix<T, M, N> &Matrix<T, M, N>::operator=(const Matrix &other)
    // {
    //     set(other);
    //     return *this;
    // }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> &Matrix<T, M, N>::operator+=(T &s)
    {
        iadd(s);
        return *this;
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    Matrix<T, M, N> &Matrix<T, M, N>::operator+=(const E &m)
    {
        iadd(m);
        return *this;
    }
    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> &Matrix<T, M, N>::operator-=(T &s)
    {
        isub(s);
        return *this;
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    Matrix<T, M, N> &Matrix<T, M, N>::operator-=(const E &m)
    {
        isub(m);
        return *this;
    }
    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> &Matrix<T, M, N>::operator*=(T &s)
    {
        imul(s);
        return *this;
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    Matrix<T, M, N> &Matrix<T, M, N>::operator*=(const E &m)
    {
        imul(m);
        return *this;
    }
    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> &Matrix<T, M, N>::operator/=(T &s)
    {
        idiv(s);
        return *this;
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    bool Matrix<T, M, N>::operator==(const MatrixExpression<T, E> &m) const
    {
        return isEqual(m);
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename E>
    bool Matrix<T, M, N>::operator!=(const E &other) const
    {
        return !isEqual(other);
    }
    template <typename T, std::size_t M, std::size_t N>
    T &Matrix<T, M, N>::operator()(std::size_t i, std::size_t j)
    {
        return _elements[j + i * N];
    }
    template <typename T, std::size_t M, std::size_t N>
    const T &Matrix<T, M, N>::operator()(std::size_t i, std::size_t j) const
    {
        return _elements[j + i * N];
    }

    template <typename T, std::size_t M, std::size_t N>
    constexpr std::size_t Matrix<T, M, N>::rows() const
    {
        return M;
    }
    template <typename T, std::size_t M, std::size_t N>
    constexpr std::size_t Matrix<T, M, N>::cols() const
    {
        return N;
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, N, M> Matrix<T, M, N>::transposed() const
    {
        Matrix<T, N, M> temp;
        forEachIndex([&](std::size_t i, std::size_t j)
                     { temp(j, i) = (*this)(i, j); });
        return temp;
    }

    template <typename T, std::size_t M, std::size_t N>
    Matrix<T, M, N> Matrix<T, M, N>::inverse() const
    {
        Matrix inv(*this);
        inv.invert();
        return inv;
    }

    template <typename T, std::size_t M, std::size_t N>
    template <typename Callback>
    void Matrix<T, M, N>::forEach(Callback func) const
    {
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                func((*this)(i, j));
            }
        }
    }
    template <typename T, std::size_t M, std::size_t N>
    template <typename Callback>
    void Matrix<T, M, N>::forEachIndex(Callback func) const
    {
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                func(i, j);
            }
        }
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixConstant<T> Matrix<T, M, N>::makeZero()
    {
        return MatrixConstant<T>(M, N, 0);
    }
    template <typename T, std::size_t M, std::size_t N>
    MatrixIdentity<T> Matrix<T, M, N>::makeIdentity()
    {
        static_assert(M == N, "M != N.");
        return MatrixIdentity<T>(M);
    }

    template <typename T, std::size_t M, std::size_t N>
    template <typename... Params>
    void Matrix<T, M, N>::setRowAt(std::size_t i, T v, Params... params)
    {
        _elements[i] = v;
        setRowAt(i + 1, params...);
    }
    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::setRowAt(std::size_t i, T v)
    {
        _elements[i] = v;
    }
}

#endif