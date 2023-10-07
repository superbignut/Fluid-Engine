#ifndef INCLUDE_BIG_MATRIXCSR_INL_H_
#define INCLUDE_BIG_MATRIXCSR_INL_H_
namespace big
{
    template <typename T, typename VE>
    MatrixCsrVectorMul<T, VE>::MatrixCsrVectorMul(const MatrixCsr<T> &m, const VE &v) : _m(m), _v(v)
    {
        assert(_m.cols() == _v.size());
    }

    template <typename T, typename VE>
    MatrixCsrVectorMul<T, VE>::MatrixCsrVectorMul(const MatrixCsrVectorMul &other) : _m(other._m), _v(other._v) {}

    template <typename T, typename VE>
    std::size_t MatrixCsrVectorMul<T, VE>::size() const
    {
        return _m.rows();
    }

    template <typename T, typename VE>
    T MatrixCsrVectorMul<T, VE>::operator[](std::size_t i) const
    {
        auto nnz = _m.nonZeroBegin();
        auto rp = _m.rowPointerBegin();
        auto ci = _m.colIndexBegin();

        std::size_t colBegin = rp[i];
        std::size_t colEnd = rp[i + 1];
        T sum = 0;
        for (std::size_t j = colBegin; j < colEnd; ++j)
        {
            std::size_t jj = ci[j];
            sum += nnz[j] * _v[jj];
        }
        return sum;
    }

    template <typename T, typename ME>
    MatrixCsrMatrixMul<T, ME>::MatrixCsrMatrixMul(const MatrixCsr<T> &m1, const ME &m2)
        : _m1(m1),
          _m2(m2),
          _nnz(m1.nonZeroData()),
          _rp(m1.rowPointerData()),
          _ci(m1.colIndexData())
    {
        assert(m1.cols() == m2.rows());
    }

    template <typename T, typename ME>
    Size2 MatrixCsrMatrixMul<T, ME>::size() const
    {
        return Size2(_m1.rows(), _m2.cols());
    }

    template <typename T, typename ME>
    std::size_t MatrixCsrMatrixMul<T, ME>::rows() const
    {
        return _m1.rows();
    }

    template <typename T, typename ME>
    std::size_t MatrixCsrMatrixMul<T, ME>::cols() const
    {
        return _m2.cols();
    }

    template <typename T, typename ME>
    T MatrixCsrMatrixMul<T, ME>::operator()(std::size_t i, std::size_t j) const
    {
        std::size_t colBegin = _rp[i];
        std::size_t colEnd = _rp[i + 1];
        T sum = 0;
        for (std::size_t k = colBegin; k < colEnd; ++k)
        {
            std::size_t col = _ci[k];
            sum += _nnz[k] * _m2(col, j);
        }
        return sum;
    }

    template <typename T>
    MatrixCsr<T>::Element::Element()
        : i(0), j(0), value(0) {}

    template <typename T>
    MatrixCsr<T>::Element::Element(std::size_t i_, std::size_t j_, const T &value_)
        : i(i_), j(j_), value(value_) {}

    template <typename T>
    MatrixCsr<T>::MatrixCsr()
    {
        clear();
    }
    template <typename T>
    MatrixCsr<T>::MatrixCsr(const std::initializer_list<std::initializer_list<T>> &lst, T epslion)
    {
    }

    template <typename T>
    MatrixCsr<T>::MatrixCsr(const MatrixCsr &other, T epslion)
    {
    }

    template <typename T>
    MatrixCsr<T>::MatrixCsr(const MatrixCsr &&other)
    {
        *this = std::move(other);
    }

    template <typename T>
    void MatrixCsr<T>::clear()
    {
        _size = {0, 0};
        _nonZeros.clear();
        _colIndex.clear();
        _rowPtr.clear();
        _rowPtr.push_back(0);
    }
    template <typename T>
    void MatrixCsr<T>::set(T s)
    {
        std::fill(_nonZeros.begin(), _nonZeros.end(), s);
    }

    template <typename T>
    void MatrixCsr<T>::set(const MatrixCsr &other)
    {
        _size = other._size;
        _nonZeros = other._nonZeros;
        _colIndex = other._colIndex;
        _rowPtr = other._rowPtr;
    }
} // namespace big

#endif