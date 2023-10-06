#ifndef INCLUDE_BIG_MATRIX2X2_INL_H_
#define INCLUDE_BIG_MATRIX2X2_INL_H_

#include <cstring>
namespace big
{

    template <typename T>
    Matrix<T, 2, 2>::Matrix()
    {
        _elements.fill(0);
    }
    template <typename T>
    Matrix<T, 2, 2>::Matrix(T s)
    {
        set(s);
    }
    template <typename T>
    Matrix<T, 2, 2>::Matrix(T m00, T m01, T m10, T m11)
    {
        set(m00, m01, m10, m11);
    }

    template <typename T>
    Matrix<T, 2, 2>::Matrix(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        set(lst);
    }
    template <typename T>
    Matrix<T, 2, 2>::Matrix(const Matrix &m)
    {
        set(m);
    }

    template <typename T>
    Matrix<T, 2, 2>::Matrix(const T *arr)
    {
        set(arr);
    }
    template <typename T>
    void Matrix<T, 2, 2>::set(T m00, T m01, T m10, T m11)
    {
        _elements[0] = m00;
        _elements[1] = m01;
        _elements[2] = m10;
        _elements[3] = m11;
    }

    template <typename T>
    void Matrix<T, 2, 2>::set(const T *arr)
    {
        memcpy(_elements.data(), arr, sizeof(T) * 4);
    }

    template <typename T>
    void Matrix<T, 2, 2>::set(const Matrix &m)
    {
        memcpy(_elements.data(), m._elements.data(), sizeof(T) * 4);
    }

    template <typename T>
    void Matrix<T, 2, 2>::set(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        std::size_t rows = lst.size();
        std::size_t cols = (rows != 0) ? lst.begin()->size() : 0;
        assert(rows == 2 && cols == 2 && "initializer_list has anMatrix<T, 2, 2>:: invalid size.");

        auto rowIter = lst.begin();
        for (std::size_t i = 0; i < rows; ++i)
        {
            auto colIter = rowIter->begin();
            assert(rowIter->size() == cols && "Error column sizeMatrix<T, 2, 2>:: inMatrix<T, 2, 2>:: iniitalizer_list."); // because eachMatrix<T, 2, 2>:: innerMatrix<T, 2, 2>:: initialize_list can have diff size.

            for (std::size_t j = 0; j < cols; ++j)
            {
                (*this)(i, j) = *colIter;
                ++colIter;
            }
            ++rowIter;
        }
    }

    template <typename T>
    void Matrix<T, 2, 2>::set(T s)
    {
        _elements.fill(s);
    }
    template <typename T>
    void Matrix<T, 2, 2>::setRow(std::size_t i, const Vector<T, 2> &row)
    {
        _elements[2 * i] = row.x;
        _elements[2 * i + 1] = row.y;
    }
    template <typename T>
    void Matrix<T, 2, 2>::setCol(std::size_t i, const Vector<T, 2> &col)
    {
        _elements[i] = col.x;
        _elements[i + 2] = col.y;
    }
    template <typename T>
    bool Matrix<T, 2, 2>::isSimilar(const Matrix &other, double tol) const
    {
        for (std::size_t i = 0; i < 2; ++i)
        {
            for (std::size_t j = 0; j < 2; ++j)
            {
                if (std::fabs((*this)(i, j) - other(i, j)) > tol)
                    return false;
            }
        }
        return true;
    }

    template <typename T>
    constexpr bool Matrix<T, 2, 2>::isSquare() const
    {
        return true;
    }

    template <typename T>
    constexpr std::size_t Matrix<T, 2, 2>::rows() const
    {
        return 2;
    }
    template <typename T>
    constexpr std::size_t Matrix<T, 2, 2>::cols() const
    {
        return 2;
    }

    template <typename T>
    T *Matrix<T, 2, 2>::data()
    {
        return _elements.data();
    }
    template <typename T>
    const T *const Matrix<T, 2, 2>::data() const
    {
        return _elements.data();
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::add(T val) const
    {
        return Matrix(_elements[0] + val, _elements[1] + val,
                      _elements[2] + val, _elements[3] + val);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::add(const Matrix &other) const
    {
        return Matrix(_elements[0] + other._elements[0], _elements[1] + other._elements[1],
                      _elements[2] + other._elements[2], _elements[3] + other._elements[3]);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::sub(T val) const
    {
        return Matrix(_elements[0] - val, _elements[1] - val,
                      _elements[2] - val, _elements[3] - val);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::sub(const Matrix &other) const
    {
        return Matrix(_elements[0] - other._elements[0], _elements[1] - other._elements[1],
                      _elements[2] - other._elements[2], _elements[3] - other._elements[3]);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::mul(T val) const
    {
        return Matrix(_elements[0] * val, _elements[1] * val,
                      _elements[2] * val, _elements[3] * val);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::mul(const Matrix &other) const
    {
        return Matrix(_elements[0] * other._elements[0] + _elements[1] * other._elements[2],
                      _elements[0] * other._elements[1] + _elements[1] * other._elements[3],
                      _elements[2] * other._elements[0] + _elements[3] * other._elements[2],
                      _elements[2] * other._elements[1] + _elements[3] * other._elements[3]);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::div(T val) const
    {
        return Matrix(_elements[0] / val, _elements[1] / val,
                      _elements[2] / val, _elements[3] / val);
    }

    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::rsub(T val) const
    {
        return Matrix(val - _elements[0], val - _elements[1],
                      val - _elements[2], val - _elements[3]);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::rsub(const Matrix &other) const
    {
        return Matrix(other._elements[0] - _elements[0], other._elements[1] - _elements[1],
                      other._elements[2] - _elements[2], other._elements[3] - _elements[3]);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::rmul(const Matrix &other) const
    {
        return Matrix(other._elements[0] * _elements[0] + other._elements[1] * _elements[2],
                      other._elements[0] * _elements[1] + other._elements[1] * _elements[3],
                      other._elements[2] * _elements[0] + other._elements[3] * _elements[2],
                      other._elements[2] * _elements[1] + other._elements[3] * _elements[3]);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::rdiv(T val) const
    {
        return Matrix(val / _elements[0], val / _elements[1],
                      val / _elements[2], val / _elements[3]);
    }
    template <typename T>
    void Matrix<T, 2, 2>::iadd(T val)
    {
        set(add(val));
    }
    template <typename T>
    void Matrix<T, 2, 2>::iadd(const Matrix &other)
    {
        set(add(other));
    }
    template <typename T>
    void Matrix<T, 2, 2>::isub(T val)
    {
        set(sub(val));
    }
    template <typename T>
    void Matrix<T, 2, 2>::isub(const Matrix &other)
    {
        set(sub(other));
    }
    template <typename T>
    void Matrix<T, 2, 2>::imul(T val)
    {
        set(mul(val));
    }
    template <typename T>
    void Matrix<T, 2, 2>::imul(const Matrix &other)
    {
        set(mul(other));
    }
    template <typename T>
    void Matrix<T, 2, 2>::idiv(T val)
    {
        set(div(val));
    }
    template <typename T>
    void Matrix<T, 2, 2>::transpose()
    {
        set(Matrix(_elements[0], _elements[2], _elements[1], _elements[3]));
    }
    template <typename T>
    void Matrix<T, 2, 2>::invert()
    {
        Matrix m;
        T d = determinant();
        assert((d != 0) && "matrix's determinant is zero.");
        m._elements[0] = _elements[3];
        m._elements[1] = -_elements[2];
        m._elements[2] = -_elements[1];
        m._elements[3] = _elements[0];
        m.idiv(d);
        set(m);
    }

    template <typename T>
    T Matrix<T, 2, 2>::sum() const
    {
        return (_elements[0] + _elements[1] + _elements[2] + _elements[3]);
    }

    template <typename T>
    T Matrix<T, 2, 2>::avg() const
    {
        return sum() / 4;
    }

    template <typename T>
    T Matrix<T, 2, 2>::min() const
    {
        return std::min(
            std::min(_elements[0], _elements[1]),
            std::min(_elements[2], _elements[3]));
    }

    template <typename T>
    T Matrix<T, 2, 2>::max() const
    {
        return std::max(
            std::max(_elements[0], _elements[1]),
            std::max(_elements[2], _elements[3]));
    }

    template <typename T>
    T Matrix<T, 2, 2>::absmin() const
    {
        return big::absmin(
            big::absmin(_elements[0], _elements[1]),
            big::absmin(_elements[2], _elements[3]));
    }

    template <typename T>
    T Matrix<T, 2, 2>::absmax() const
    {
        return big::absmax(
            big::absmax(_elements[0], _elements[1]),
            big::absmax(_elements[2], _elements[3]));
    }

    template <typename T>
    T Matrix<T, 2, 2>::trace() const
    {
        return _elements[0] + _elements[3];
    }

    template <typename T>
    T Matrix<T, 2, 2>::determinant() const
    {
        return _elements[0] * _elements[3] - _elements[1] * _elements[2];
    }
    template <typename T>
    void Matrix<T, 2, 2>::show() const
    {
        printf("%f %f %f %f\n", _elements[0], _elements[1], _elements[2], _elements[3]);
    }

    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::diagonal() const
    {
        return (Matrix(_elements[0], 0, 0, _elements[3]));
    }

    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::offDiagonal() const
    {
        return (Matrix(0, _elements[1], _elements[2], 0));
    }

    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::strictLowerTri() const
    {
        return (Matrix(0, 0, _elements[2], 0));
    }

    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::stricitUpperTri() const
    {
        return (Matrix(0, _elements[1], 0, 0));
    }

    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::lowerTri() const
    {
        return (Matrix(_elements[0], 0, _elements[2], _elements[3]));
    }

    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::upperTri() const
    {
        return (Matrix(_elements[0], _elements[1], 0, _elements[3]));
    }

    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::transposed() const
    {
        return (Matrix(_elements[0], _elements[2], _elements[1], _elements[3]));
    }

    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::inverse() const
    {
        Matrix m(*this);
        T d = determinant();
        assert((d != 0) && "matrix's determinant is zero.");
        m._elements[0] = _elements[3];
        m._elements[1] = -_elements[1];
        m._elements[2] = -_elements[2];
        m._elements[3] = _elements[0];
        m.idiv(d);
        return m;
    }

    template <typename T>
    T Matrix<T, 2, 2>::frobeniusNorm() const
    {
        return std::sqrt(_elements[0] * _elements[0] + _elements[1] * _elements[1] + _elements[2] * _elements[2] + _elements[3] * _elements[3]);
    }
    template <typename T>
    template <typename U>
    Matrix<U, 2, 2> Matrix<T, 2, 2>::castTo() const
    {
        return Matrix<U, 2, 2>(
            static_cast<U>(_elements[0]), static_cast<U>(_elements[1]),
            static_cast<U>(_elements[2]), static_cast<U>(_elements[3]));
    }

    template <typename T>
    Matrix<T, 2, 2> &Matrix<T, 2, 2>::operator=(const Matrix &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    Matrix<T, 2, 2> &Matrix<T, 2, 2>::operator+=(T &s)
    {

        iadd(s);
        return *this;
    }

    template <typename T>
    Matrix<T, 2, 2> &Matrix<T, 2, 2>::operator+=(const Matrix &m)
    {
        iadd(m);
        return *this;
    }

    template <typename T>
    Matrix<T, 2, 2> &Matrix<T, 2, 2>::operator-=(T &s)
    {
        isub(s);
        return *this;
    }

    template <typename T>
    Matrix<T, 2, 2> &Matrix<T, 2, 2>::operator-=(const Matrix &m)
    {
        isub(m);
        return *this;
    }

    template <typename T>
    Matrix<T, 2, 2> &Matrix<T, 2, 2>::operator*=(T &s)
    {
        imul(s);
        return *this;
    }

    template <typename T>
    Matrix<T, 2, 2> &Matrix<T, 2, 2>::operator*=(const Matrix &m)
    {
        iadd(m);
        return *this;
    }

    template <typename T>
    Matrix<T, 2, 2> &Matrix<T, 2, 2>::operator/=(T &s)
    {
        idiv(s);
        return *this;
    }
    template <typename T>
    bool Matrix<T, 2, 2>::operator==(const Matrix &other) const
    {
        return (_elements[0] == other._elements[0] && _elements[1] == other._elements[1] &&
                _elements[2] == other._elements[2] && _elements[3] == other._elements[3]);
    }
    template <typename T>
    bool Matrix<T, 2, 2>::operator!=(const Matrix &other) const
    {
        return (_elements[0] != other._elements[0] || _elements[1] != other._elements[1] ||
                _elements[2] != other._elements[2] || _elements[3] != other._elements[3]);
    }

    template <typename T>
    T &Matrix<T, 2, 2>::operator()(std::size_t i, std::size_t j)
    {
        return _elements[i * 2 + j];
    }
    template <typename T>
    const T &Matrix<T, 2, 2>::operator()(std::size_t i, std::size_t j) const
    {
        return _elements[i * 2 + j];
    }
    template <typename T>
    T &Matrix<T, 2, 2>::operator[](std::size_t i)
    {
        return _elements[i];
    }
    template <typename T>
    const T &Matrix<T, 2, 2>::operator[](std::size_t i) const
    {
        return _elements[i];
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::makeZero()
    {
        return Matrix(0, 0, 0, 0);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::makeIdentity()
    {
        return Matrix(1, 0, 0, 1);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::makeScaleMatrix(T sx, T sy)
    {
        return Matrix(sx, 0, 0, sy);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::makeScaleMatrix(const Vector<T, 2> &s)
    {
        return Matrix(s.x, 0, 0, s.y);
    }
    template <typename T>
    Matrix<T, 2, 2> Matrix<T, 2, 2>::makeRotationMatrix(T rad)
    {
        return Matrix(std::cos(rad), -std::sin(rad), std::sin(rad), std::cos(rad));
    }

    template <typename T>
    Matrix<T, 2, 2> operator+(const Matrix<T, 2, 2> &a, const Matrix<T, 2, 2> &b)
    {
        return a.add(b);
    }

    template <typename T>
    Matrix<T, 2, 2> operator+(const Matrix<T, 2, 2> &a, T b)
    {

        return a.add(b);
    }

    template <typename T>
    Matrix<T, 2, 2> operator+(T a, const Matrix<T, 2, 2> &b)
    {
        return b.add(a);
    }

    template <typename T>
    Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2> &a, const Matrix<T, 2, 2> &b)
    {
        return a.sub(b);
    }

    template <typename T>
    Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2> &a, T b)
    {
        return a.sub(b);
    }

    template <typename T>
    Matrix<T, 2, 2> operator-(T a, const Matrix<T, 2, 2> &b)
    {
        return b.rsub(a);
    }

    template <typename T>
    Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2> &a)
    {
        return a.mul(-1);
    }

    template <typename T>
    Matrix<T, 2, 2> operator*(const Matrix<T, 2, 2> &a, const Matrix<T, 2, 2> &b)
    {
        return a.mul(b);
    }

    template <typename T>
    Matrix<T, 2, 2> operator*(const Matrix<T, 2, 2> &a, T b)
    {
        return a.mul(b);
    }

    template <typename T>
    Matrix<T, 2, 2> operator*(T a, const Matrix<T, 2, 2> &b)
    {
        return b.mul(a);
    }

    template <typename T>
    Matrix<T, 2, 2> operator*(const Matrix<T, 2, 2> &a, const Vector<T, 2> &b)
    {
        return a.mul(b);
    }

    template <typename T>
    Matrix<T, 2, 2> operator/(const Matrix<T, 2, 2> &a, T b)
    {
        return a.div(b);
    }

    template <typename T>
    Matrix<T, 2, 2> operator/(T a, const Matrix<T, 2, 2> &b)
    {
        return b.rdiv(a);
    }

}
#endif