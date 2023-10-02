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
        const E &expression = other(); // other() call ()()
        // 遍历foreachindex()
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
    void Matrix<T, M, N>::set(const Matrix &other)
    {
    }

    template <typename T, std::size_t M, std::size_t N>
    constexpr Size2 Matrix<T, M, N>::size() const
    {
        return Size2(M, N);
    }

    template <typename T, std::size_t M, std::size_t N>
    void Matrix<T, M, N>::set(const T &s)
    {
        _elements.fill(s);
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