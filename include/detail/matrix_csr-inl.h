#ifndef INCLUDE_BIG_MATRIXCSR_INL_H_
#define INCLUDE_BIG_MATRIXCSR_INL_H_
#include <numeric>//iota
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
        compress(lst, epslion);
    }

    template <typename T>
    template <typename E>
    MatrixCsr<T>::MatrixCsr(const MatrixExpression<T, E> &other, T epslion)
    {
        compress(other, epslion);
    }

    template <typename T>
    MatrixCsr<T>::MatrixCsr(const MatrixCsr &other)
    {
        set(other);
    }

    template <typename T>
    MatrixCsr<T>::MatrixCsr(MatrixCsr &&other)
    {
        *this = std::move(other); // call move assignment operator.
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

    template <typename T>
    void MatrixCsr<T>::reserve(std::size_t rows, std::size_t cols, std::size_t numNonZeros)
    {
        _size = {rows, cols};
        _nonZeros.resize(numNonZeros);
        _colIndex.resize(numNonZeros);
        _rowPtr.resize(rows + 1);
    }

    template <typename T>
    void MatrixCsr<T>::compress(const std::initializer_list<std::initializer_list<T>> &lst, T epslion)
    {
        std::size_t numRows = lst.size();
        std::size_t numCols = numRows != 0 ? lst.begin()->size() : 0;

        _size = {numRows, numCols};
        _nonZeros.clear();
        _colIndex.clear();
        _rowPtr.clear();

        auto rowIter = lst.begin();
        for (std::size_t i = 0; i < numRows; ++i)
        {
            assert(rowIter->size() == numCols && "lst has different columns.");
            _rowPtr.push_back(_nonZeros.size());
            auto col_ptr = rowIter->begin();
            for (std::size_t j = 0; j < numCols; ++j)
            {
                if (std::fabs(*col_ptr) > epslion)
                {
                    _nonZeros.push_back(*col_ptr);
                    _colIndex.push_back(j);
                }
                ++col_ptr;
            }
            ++rowIter;
        }
        _rowPtr.push_back(_nonZeros.size()); // which is seted for colEnd = _rp[i + 1];
    }

    template <typename T>
    template <typename E>
    void MatrixCsr<T>::compress(const MatrixExpression<T, E> &other, T epslion)
    {
        const E &m = other();
        std::size_t numRows = m.rows();
        std::size_t numCols = m.cols();

        _size = {numRows, numCols};
        _nonZeros.clear();
        _colIndex.clear();
        _rowPtr.clear();
        for (std::size_t i = 0; i < numRows; ++i)
        {
            _rowPtr.push_back(_nonZeros.size());
            for (std::size_t j = 0; j < numCols; ++j)
            {
                if (std::fabs(m(i, j)) > epslion)
                {
                    _nonZeros.push_back(m(i, j));
                    _colIndex.push_back(j);
                }
            }
        }
        _rowPtr.push_back(_nonZeros.size()); // which is seted for colEnd = _rp[i + 1];
    }

    template <typename T>
    void MatrixCsr<T>::show(std::size_t i, std::size_t j) const
    {
        std::cout << _nonZeros.size() << std::endl;
        std::cout << _size.x << _size.y << std::endl;
        for (int i = 0; i < _nonZeros.size(); ++i)
            std::cout << _nonZeros[i] << " ";
        std::cout << std::endl;
        std::cout << (hasElement(i, j) != kMaxSize ? "have this one." : "don't have this one.") << std::endl;
        std::cout << _rowPtr.size() << std::endl;
    }

    template <typename T>
    void MatrixCsr<T>::addElement(std::size_t i, std::size_t j, T value)
    {
        addElement({i, j, value});
    }

    template <typename T>
    void MatrixCsr<T>::addElement(const Element &element)
    {
        ssize_t numRowsToAdd = (ssize_t)element.i - (ssize_t)_size.x + 1;
        if (numRowsToAdd > 0)
        {
            for (ssize_t i = 0; i < numRowsToAdd; ++i)
            {
                addRow({}, {});
            }
        }

        _size.y = std::max(_size.y, element.j + 1);
        std::size_t rowBegin = _rowPtr[element.i];
        std::size_t rowEnd = _rowPtr[element.i + 1];

        auto colIndexIter = std::lower_bound(_colIndex.begin() + rowBegin, _colIndex.begin() + rowEnd, element.j);
        auto offset = colIndexIter - _colIndex.begin();
        _colIndex.insert(colIndexIter, element.j);
        _nonZeros.insert(_nonZeros.begin() + offset, element.value);
        for (std::size_t i = element.i + 1; i < _rowPtr.size(); ++i)
        {
            ++_rowPtr[i];
        }
    }

    template <typename T>
    void MatrixCsr<T>::addRow(const NonZeroContainterType &nonZeros, const IndexContainterType &columnIndex)
    {
        assert(nonZeros.size() == columnIndex.size());
        ++_size.x;
        std::vector<std::pair<T, std::size_t>> zipped;
        for (std::size_t i = 0; i < nonZeros.size(); ++i)
        {
            zipped.emplace_back(nonZeros[i], columnIndex[i]);
            _size.y = std::max(_size.y, columnIndex[i] + 1); // columnIndex[i] + 1 represent the max ColunmIndex
        }
        std::sort(zipped.begin(), zipped.end(), [](std::pair<T, std::size_t> a, std::pair<T, std::size_t> b)
                  { return a.second < b.second; });
        for (std::size_t i = 0; i < zipped.size(); ++i)
        {
            _nonZeros.push_back(zipped[i].first);
            _colIndex.push_back(zipped[i].second);
        }
        _rowPtr.push_back(_nonZeros.size());
    }

    template <typename T>
    void MatrixCsr<T>::setElement(std::size_t i, std::size_t j, T value)
    {
        setElement({i, j, value});
    }
    template <typename T>
    void MatrixCsr<T>::setElement(const Element &element)
    {
        std::size_t nzIndex = hasElement(element.i, element.j);
        if (nzIndex == kMaxSize)
        {
            addElement(element);
        }
        else
        {
            _nonZeros[nzIndex] = element.value;
        }
    }

    template <typename T>
    std::size_t MatrixCsr<T>::hasElement(std::size_t i, std::size_t j) const
    {
        if (i >= _size.x || j >= _size.y)
        {
            return kMaxSize;
        }

        auto rowBegin = _rowPtr[i];
        auto rowEnd = _rowPtr[i + 1];
        auto colIndexIter = std::lower_bound(_colIndex.begin() + rowBegin, _colIndex.begin() + rowEnd, j);
        if (colIndexIter != (rowBegin, _colIndex.begin() + rowEnd) && *colIndexIter == j)
        {
            return static_cast<std::size_t>(colIndexIter - _colIndex.begin());
        }
        else
            return kMaxSize;
    }

    template <typename T>
    template <typename Op>
    MatrixCsr<T> MatrixCsr<T>::binaryOp(const MatrixCsr &m, Op op) const
    {
        assert(_size == m._size);
        MatrixCsr ret;

        for (std::size_t i = 0; i < _size.x; ++i)
        {
            std::vector<std::size_t> col;
            std::vector<T> nnz;

            auto colIterA = _colIndex.begin() + _rowPtr[i];
            auto colIterB = m._colIndex.begin() + m._rowPtr[i];

            auto colEndA = _colIndex.begin() + _rowPtr[i + 1];
            auto colEndB = m._colIndex.begin() + m._rowPtr[i + 1];

            auto nnzIterA = _nonZeros.begin() + _rowPtr[i];
            auto nnzIterB = m._nonZeros.begin() + m._rowPtr[i];

            while (colIterA != colEndA || colIterB != colEndB) // any col exits will loop
            {
                if ((*colIterA < *colIterB || colIterB == colEndB) && colIterA != colEndA)
                {
                    nnz.push_back(op(*nnzIterA, 0));
                    col.push_back(*colIterA);
                    ++nnzIterA;
                    ++colIterA;
                }
                else if ((*colIterB < *colIterA || colIterA == colEndA) && colIterB != colEndB)
                {
                    nnz.push_back(op(0, *nnzIterB));
                    col.push_back(*colIterB);
                    ++nnzIterB;
                    ++colIterB;
                }
                else
                {
                    assert(*colIterA == *colIterB);
                    nnz.push_back(op(*nnzIterA, *nnzIterB));
                    col.push_back(*colIterA);
                    ++nnzIterA;
                    ++colIterA;
                    ++nnzIterB;
                    ++colIterB;
                }
            }
            ret.addRow(nnz, col);
        }
        return ret;
    }

    template <typename T>
    bool MatrixCsr<T>::isEqual(const MatrixCsr &other) const
    {
        if (_size != other._size)
            return false;
        if (_nonZeros.size() != other._nonZeros.size())
            return false;
        if (_nonZeros != other._nonZeros)
            return false;
        if (_colIndex != other._colIndex)
            return false;
        if (_rowPtr != other._rowPtr)
            return false;
        return true;
    }
    template <typename T>
    bool MatrixCsr<T>::isSimilar(const MatrixCsr &other, double tol) const
    {
        if (_size != other._size)
            return false;
        if (_nonZeros.size() != other._nonZeros.size())
            return false;

        for (std::size_t i = 0; i < _nonZeros.size(); ++i)
        {
            if (std::fabs(_nonZeros[i] - other._nonZeros[i]) > tol)
                return false;
            if (_colIndex[i] != other._colIndex[i])
                return false;
        }
        if (_rowPtr != other._rowPtr)
            return false;
        return true;
    }
    template <typename T>
    constexpr bool MatrixCsr<T>::isSquare() const
    {
        return _size.x == _size.y;
    }
    template <typename T>
    constexpr std::size_t MatrixCsr<T>::rows() const
    {
        return _size.x;
    }
    template <typename T>
    constexpr std::size_t MatrixCsr<T>::cols() const
    {
        return _size.y;
    }

    template <typename T>
    Size2 MatrixCsr<T>::size() const
    {
        return _size;
    }
    template <typename T>
    std::size_t MatrixCsr<T>::numberNonZeros() const
    {
        return _nonZeros.size();
    }
    template <typename T>
    T &MatrixCsr<T>::nonZero(std::size_t i)
    {
        return _nonZeros[i];
    }
    template <typename T>
    const T &MatrixCsr<T>::nonZero(std::size_t i) const
    {
        return _nonZeros[i];
    }
    template <typename T>
    const std::size_t &MatrixCsr<T>::rowPointer(std::size_t i) const
    {
        return _rowPtr[i];
    }
    template <typename T>
    const std::size_t &MatrixCsr<T>::colIndex(std::size_t i) const
    {
        return _colIndex[i];
    }
    template <typename T>
    T *MatrixCsr<T>::nonZeroData()
    {
        return _nonZeros.data();
    }
    template <typename T>
    const T *const MatrixCsr<T>::nonZeroData() const
    {
        return _nonZeros.data();
    }
    template <typename T>
    const std::size_t *const MatrixCsr<T>::rowPointerData() const
    {
        return _rowPtr.data();
    }
    template <typename T>
    const std::size_t *const MatrixCsr<T>::colIndexData() const
    {
        return _colIndex.data();
    }

    template <typename T>
    MatrixCsr<T>::NonZeroIterator MatrixCsr<T>::nonZeroBegin()
    {
        return _nonZeros.begin();
    }
    template <typename T>
    MatrixCsr<T>::NonZeroIterator MatrixCsr<T>::nonZeroEnd()
    {
        return _nonZeros.end();
    }
    template <typename T>
    MatrixCsr<T>::IndexIterator MatrixCsr<T>::rowPointerBegin()
    {
        return _rowPtr.begin();
    }
    template <typename T>
    MatrixCsr<T>::IndexIterator MatrixCsr<T>::rowPointerEnd()
    {
        return _rowPtr.end();
    }
    template <typename T>
    MatrixCsr<T>::IndexIterator MatrixCsr<T>::colIndexBegin()
    {
        return _colIndex.begin();
    }
    template <typename T>
    MatrixCsr<T>::IndexIterator MatrixCsr<T>::colIndexEnd()
    {
        return _colIndex.end();
    }
    template <typename T>
    MatrixCsr<T>::ConstNonZeroIterator MatrixCsr<T>::nonZeroBegin() const
    {
        return _nonZeros.cbegin();
    }
    template <typename T>
    MatrixCsr<T>::ConstNonZeroIterator MatrixCsr<T>::nonZeroEnd() const
    {
        return _nonZeros.cend();
    }
    template <typename T>
    MatrixCsr<T>::ConstIndexIterator MatrixCsr<T>::rowPointerBegin() const
    {
        return _rowPtr.cbegin();
    }
    template <typename T>
    MatrixCsr<T>::ConstIndexIterator MatrixCsr<T>::rowPointerEnd() const
    {
        return _rowPtr.cend();
    }
    template <typename T>
    MatrixCsr<T>::ConstIndexIterator MatrixCsr<T>::colIndexBegin() const
    {
        return _colIndex.cbegin();
    }
    template <typename T>
    MatrixCsr<T>::ConstIndexIterator MatrixCsr<T>::colIndexEnd() const
    {
        return _colIndex.cend();
    }

    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::add(const T &s) const
    {
        MatrixCsr ret(*this);
        parallelFor(kZeroSize, ret._nonZeros.size(),
                    [&](std::size_t i)
                    { ret._nonZeros[i] += s; });
        return ret;
    }
    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::add(const MatrixCsr &m) const
    {
        return binaryOp(m, std::plus<T>()); // std::plus<T>() is a constructor.
    }
    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::sub(const T &s) const
    {
        MatrixCsr ret(*this);
        parallelFor(kZeroSize, ret._nonZeros.size(),
                    [&](std::size_t i)
                    { ret._nonZeros[i] -= s; });
        return ret;
    }
    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::sub(const MatrixCsr &m) const
    {
        return binaryOp(m, std::plus<T>());
    }
    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::mul(const T &s) const
    {
        MatrixCsr ret(*this);
        parallelFor(kZeroSize, ret._nonZeros.size(),
                    [&](std::size_t i)
                    { ret._nonZeros[i] *= s; });
        return ret;
    }
    template <typename T>
    template <typename VE>
    MatrixCsrVectorMul<T, VE> MatrixCsr<T>::mul(const VectorExpression<T, VE> &v) const
    {
        const VE &true_v = v();
        return MatrixCsrVectorMul<T, VE>(*this, true_v);
    }
    template <typename T>
    template <typename ME>
    MatrixCsrMatrixMul<T, ME> MatrixCsr<T>::mul(const MatrixExpression<T, ME> &m) const
    {
        const ME &true_m = m();
        return MatrixCsrMatrixMul<T, ME>(*this, m);
    }
    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::div(const T &s) const
    {
        MatrixCsr ret(*this);
        parallelFor(kZeroSize, ret._nonZeros.size(),
                    [&](std::size_t i)
                    { ret._nonZeros[i] /= s; });
        return ret;
    }
    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::rsub(const T &s) const
    {
        MatrixCsr ret(*this);
        parallelFor(kZeroSize, ret._nonZeros.size(),
                    [&](std::size_t i)
                    { ret._nonZeros[i] = s - ret._nonZeros[i]; });
        return ret;
    }
    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::rsub(const MatrixCsr &m) const
    {
        // return binaryOp(m, big::RMinus<T>());
        return m.sub(*this);
    }
    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::rdiv(const T &s) const
    {
        MatrixCsr ret(*this);
        parallelFor(kZeroSize, ret._nonZeros.size(),
                    [&](std::size_t i)
                    { ret._nonZeros[i] = s / ret._nonZeros[i]; });
        return ret;
    }

    template <typename T>
    T MatrixCsr<T>::operator()(std::size_t i, std::size_t j) const
    {
        std::size_t num = hasElement(i, j);
        if (num == kMaxSize)
        {
            return kZeroSize;
        }
        else
        {
            return _nonZeros[num];
        }
    }

    template <typename T>
    void MatrixCsr<T>::iadd(const T &s)
    {
        parallelFor(kZeroSize, this->_nonZeros.size(),
                    [&](std::size_t i)
                    { this->_nonZeros[i] += s; });
    }

    template <typename T>
    void MatrixCsr<T>::iadd(const MatrixCsr &m)
    {
        set(add(m));
    }

    template <typename T>
    void MatrixCsr<T>::isub(const T &s)
    {
        parallelFor(kZeroSize, this->_nonZeros.size(),
                    [&](std::size_t i)
                    { this->_nonZeros[i] -= s; });
    }

    template <typename T>
    void MatrixCsr<T>::isub(const MatrixCsr &m)
    {
        set(m.sub(*this));
    }

    template <typename T>
    void MatrixCsr<T>::imul(const T &s)
    {
        parallelFor(kZeroSize, this->_nonZeros.size(),
                    [&](std::size_t i)
                    { this->_nonZeros[i] *= s; });
    }
    template <typename T>
    template <typename ME>
    void MatrixCsr<T>::imul(const MatrixExpression<T, ME> &m)
    {
        set(mul(m)); // change to move
    }

    template <typename T>
    void MatrixCsr<T>::idiv(const T &s)
    {
        parallelFor(kZeroSize, this->_nonZeros.size(),
                    [&](std::size_t i)
                    { this->_nonZeros[i] /= s; });
    }

    template <typename T>
    T MatrixCsr<T>::sum() const
    {
        return parallelReduce(
            kZeroSize, this->_nonZeros.size(),
            T(0), [&](std::size_t begin, std::size_t end, T init)
            {
                T result = init;
                for(std::size_t i = begin; i< end; ++i)
                {
                    result += _nonZeros[i];
                }
                return result; },
            std::plus<T>());
    }

    template <typename T>
    T MatrixCsr<T>::avg() const
    {
        return sum() / numberNonZeros();
    }

    template <typename T>
    T MatrixCsr<T>::min() const
    {
        const T &(*_min)(const T &, const T &) = std::min<T>;
        return parallelReduce(
            kZeroSize, this->_nonZeros.size(),
            std::numeric_limits<T>::max(),
            [&](std::size_t begin, std::size_t end, T init)
            {
                T result = init;
                for(std::size_t i = begin; i< end; ++i)
                {
                    result = std::min(_nonZeros[i], result);
                }
                return result; },
            _min);
    }

    template <typename T>
    T MatrixCsr<T>::max() const
    {
        const T &(*_max)(const T &, const T &) = std::max<T>;
        return parallelReduce(
            kZeroSize, this->_nonZeros.size(),
            std::numeric_limits<T>::min(),
            [&](std::size_t begin, std::size_t end, T init)
            {
                T result = init;
                for(std::size_t i = begin; i< end; ++i)
                {
                    result = std::max(_nonZeros[i], result);
                }
                return result; },
            _max);
    }

    template <typename T>
    T MatrixCsr<T>::absmin() const
    {
        T(*_absmin)
        (T, T) = big::absmin<T>;
        return parallelReduce(
            kZeroSize, this->_nonZeros.size(),
            std::numeric_limits<T>::max(),
            [&](std::size_t begin, std::size_t end, T init)
            {
                T result = init;
                for(std::size_t i = begin; i< end; ++i)
                {
                    result = big::absmin(_nonZeros[i], result);
                }
                return result; },
            _absmin);
    }

    template <typename T>
    T MatrixCsr<T>::absmax() const
    {

        const T &(*_absmax)(const T &, const T &) = big::absmax<T>;
        return parallelReduce(
            kZeroSize, this->_nonZeros.size(),
            std::numeric_limits<T>::min(),
            [&](std::size_t begin, std::size_t end, T init)
            {
                T result = init;
                for(std::size_t i = begin; i< end; ++i)
                {
                    result = big::absmax(_nonZeros[i], result);
                }
                return result; },
            _absmax);
    }

    template <typename T>
    T MatrixCsr<T>::trace() const
    {
        assert(isSquare() && "CSRMatrix is not square.");
        return parallelReduce(
            kZeroSize, rows(),
            T(0), [&](std::size_t begin, std::size_t end, T init)
            {
                T result = init;
                for(std::size_t i = begin; i< end; ++i)
                {
                    result += (*this)(i, i);
                }
                return result; },
            std::plus<T>());
    }

    template <typename T>
    template <typename U>
    MatrixCsr<U> MatrixCsr<T>::castTo() const
    {
        MatrixCsr<U> ret;
        ret.reserve(rows(), cols(), numberNonZeros());

        auto nnz = ret.nonZeroBegin();
        auto coi = ret.colIndexBegin();
        auto rpt = ret.rowPointerBegin();

        parallelFor(kZeroSize, numberNonZeros(), [&](int i)
                    {
            nnz[i] = static_cast<U>(_nonZeros[i]);
            coi[i] = _colIndex[i]; });

        parallelFor(kZeroSize, rows() + 1, [&](int i)
                    { rpt[i] = _rowPtr[i]; });
        return ret;
    }

    template <typename T>
    template <typename E>
    MatrixCsr<T> &MatrixCsr<T>::operator=(const MatrixExpression<T, E> &other)
    {
        compress(other);
        return *this;
    }

    template <typename T>
    MatrixCsr<T> &MatrixCsr<T>::operator=(const MatrixCsr &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    MatrixCsr<T> &MatrixCsr<T>::operator=(MatrixCsr &&other)
    {
        _size = other._size;
        other._size = Size2();
        _nonZeros = std::move(other._nonZeros);
        _colIndex = std::move(other._colIndex);
        _rowPtr = std::move(other._rowPtr);
        return *this;
    }

    template <typename T>
    MatrixCsr<T> &MatrixCsr<T>::operator+=(T s)
    {
        iadd(s);
        return *this;
    }

    template <typename T>
    MatrixCsr<T> &MatrixCsr<T>::operator+=(const MatrixCsr &m)
    {
        iadd(m);
        return *this;
    }

    template <typename T>
    MatrixCsr<T> &MatrixCsr<T>::operator-=(T s)
    {
        isub(s);
        return *this;
    }

    template <typename T>
    MatrixCsr<T> &MatrixCsr<T>::operator-=(const MatrixCsr &m)
    {
        isub(m);
        return *this;
    }

    template <typename T>
    MatrixCsr<T> &MatrixCsr<T>::operator*=(T s)
    {
        imul(s);
        return *this;
    }

    template <typename T>
    template <typename ME>
    MatrixCsr<T> &MatrixCsr<T>::operator*=(const MatrixExpression<T, ME> &m)
    {
        imul(m);
        return *this;
    }

    template <typename T>
    MatrixCsr<T> &MatrixCsr<T>::operator/=(T s)
    {
        idiv(s);
        return *this;
    }

    template <typename T>
    bool MatrixCsr<T>::operator==(const MatrixCsr &m) const
    {
        return isEqual(m);
    }

    template <typename T>
    bool MatrixCsr<T>::operator!=(const MatrixCsr &other) const
    {
        return !isEqual(other);
    }

    template <typename T>
    MatrixCsr<T> MatrixCsr<T>::makeIdentity(std::size_t m)
    {
        MatrixCsr ret;
        ret._size = Size2(m, m);
        ret._nonZeros.resize(m, 1.0f);
        ret._colIndex.resize(m);
        ret._rowPtr.resize(m + 1);

        std::iota(ret.colIndexBegin(), ret.colIndexEnd(), kZeroSize);
        std::iota(ret.rowPointerBegin(), ret.rowPointerEnd(), kZeroSize);
        return ret;
    }
} // namespace big

#endif