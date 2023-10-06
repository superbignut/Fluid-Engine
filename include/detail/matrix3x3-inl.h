#ifndef INCLUDE_BIG_MATRIX3X3_INL_H_
#define INCLUDE_BIG_MATRIX3X3_INL_H_

#include <cstring>
namespace big
{

    template <typename T>
    Matrix<T, 3, 3>::Matrix()
    {
        _elements.fill(0);
    }
    template <typename T>
    Matrix<T, 3, 3>::Matrix(T s)
    {
        set(s);
    }
    template <typename T>
    Matrix<T, 3, 3>::Matrix(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)
    {
        set(m00, m01, m02, m10, m11, m12, m20, m21, m22);
    }

    template <typename T>
    Matrix<T, 3, 3>::Matrix(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        set(lst);
    }
    template <typename T>
    Matrix<T, 3, 3>::Matrix(const Matrix &m)
    {
        set(m);
    }

    template <typename T>
    Matrix<T, 3, 3>::Matrix(const T *arr)
    {
        set(arr);
    }
    template <typename T>
    void Matrix<T, 3, 3>::set(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)
    {
        _elements[0] = m00;
        _elements[1] = m01;
        _elements[2] = m02;

        _elements[3] = m10;
        _elements[4] = m11;
        _elements[5] = m12;

        _elements[6] = m20;
        _elements[7] = m21;
        _elements[8] = m22;
    }

    template <typename T>
    void Matrix<T, 3, 3>::set(const T *arr)
    {
        memcpy(_elements.data(), arr, sizeof(T) * 9);
    }

    template <typename T>
    void Matrix<T, 3, 3>::set(const Matrix &m)
    {
        memcpy(_elements.data(), m._elements.data(), sizeof(T) * 9);
    }

    template <typename T>
    void Matrix<T, 3, 3>::set(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        std::size_t rows = lst.size();
        std::size_t cols = (rows != 0) ? lst.begin()->size() : 0;
        assert(rows == 3 && cols == 3 && "initializer_list has anMatrix<T, 3, 3>:: invalid size.");

        auto rowIter = lst.begin();
        for (std::size_t i = 0; i < rows; ++i)
        {
            auto colIter = rowIter->begin();
            assert(rowIter->size() == cols && "Error column sizeMatrix<T, 3, 3>:: inMatrix<T, 3, 3>:: iniitalizer_list."); // because eachMatrix<T, 3, 3>:: innerMatrix<T, 3, 3>:: initialize_list can have diff size.

            for (std::size_t j = 0; j < cols; ++j)
            {
                (*this)(i, j) = *colIter;
                ++colIter;
            }
            ++rowIter;
        }
    }

    template <typename T>
    void Matrix<T, 3, 3>::set(T s)
    {
        _elements.fill(s);
    }
    template <typename T>
    void Matrix<T, 3, 3>::setRow(std::size_t i, const Vector<T, 3> &row)
    {
        _elements[3 * i] = row.x;
        _elements[3 * i + 1] = row.y;
        _elements[3 * i + 2] = row.z;
    }
    template <typename T>
    void Matrix<T, 3, 3>::setCol(std::size_t i, const Vector<T, 3> &col)
    {
        _elements[i] = col.x;
        _elements[i + 3] = col.y;
        _elements[i + 6] = col.z;
    }
    template <typename T>
    bool Matrix<T, 3, 3>::isSimilar(const Matrix &other, double tol) const
    {
        for (std::size_t i = 0; i < 3; ++i)
        {
            for (std::size_t j = 0; j < 3; ++j)
            {
                if (std::fabs((*this)(i, j) - other(i, j)) > tol)
                    return false;
            }
        }
        return true;
    }

    template <typename T>
    constexpr bool Matrix<T, 3, 3>::isSquare() const
    {
        return true;
    }

    template <typename T>
    constexpr std::size_t Matrix<T, 3, 3>::rows() const
    {
        return 3;
    }
    template <typename T>
    constexpr std::size_t Matrix<T, 3, 3>::cols() const
    {
        return 3;
    }

    template <typename T>
    T *Matrix<T, 3, 3>::data()
    {
        return _elements.data();
    }
    template <typename T>
    const T *const Matrix<T, 3, 3>::data() const
    {
        return _elements.data();
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::add(T val) const
    {
        return Matrix(_elements[0] + val, _elements[1] + val, _elements[2] + val,
                      _elements[3] + val, _elements[4] + val, _elements[5] + val,
                      _elements[6] + val, _elements[7] + val, _elements[8] + val);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::add(const Matrix &other) const
    {
        return Matrix(_elements[0] + other._elements[0], _elements[1] + other._elements[1], _elements[2] + other._elements[2],
                      _elements[3] + other._elements[3], _elements[4] + other._elements[4], _elements[5] + other._elements[5],
                      _elements[6] + other._elements[6], _elements[7] + other._elements[7], _elements[8] + other._elements[8]);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::sub(T val) const
    {
        return Matrix(_elements[0] - val, _elements[1] - val, _elements[2] - val,
                      _elements[3] - val, _elements[4] - val, _elements[5] - val,
                      _elements[6] - val, _elements[7] - val, _elements[8] - val);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::sub(const Matrix &other) const
    {
        return Matrix(_elements[0] - other._elements[0], _elements[1] - other._elements[1], _elements[2] - other._elements[2],
                      _elements[3] - other._elements[3], _elements[4] - other._elements[4], _elements[5] - other._elements[5],
                      _elements[6] - other._elements[6], _elements[7] - other._elements[7], _elements[8] - other._elements[8]);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::mul(T val) const
    {
        return Matrix(_elements[0] * val, _elements[1] * val, _elements[2] * val,
                      _elements[3] * val, _elements[4] * val, _elements[5] * val,
                      _elements[6] * val, _elements[7] * val, _elements[8] * val);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::mul(const Matrix &other) const
    {
        return Matrix(_elements[0] * other._elements[0] + _elements[1] * other._elements[3] + _elements[2] * other._elements[6],
                      _elements[0] * other._elements[1] + _elements[1] * other._elements[4] + _elements[2] * other._elements[7],
                      _elements[0] * other._elements[2] + _elements[1] * other._elements[5] + _elements[2] * other._elements[8],

                      _elements[3] * other._elements[0] + _elements[4] * other._elements[3] + _elements[5] * other._elements[6],
                      _elements[3] * other._elements[1] + _elements[4] * other._elements[4] + _elements[5] * other._elements[7],
                      _elements[3] * other._elements[2] + _elements[4] * other._elements[5] + _elements[5] * other._elements[8],

                      _elements[6] * other._elements[0] + _elements[7] * other._elements[3] + _elements[8] * other._elements[6],
                      _elements[6] * other._elements[1] + _elements[7] * other._elements[4] + _elements[8] * other._elements[7],
                      _elements[6] * other._elements[2] + _elements[7] * other._elements[5] + _elements[8] * other._elements[8]);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::div(T val) const
    {
        return Matrix(_elements[0] / val, _elements[1] / val, _elements[2] / val,
                      _elements[3] / val, _elements[4] / val, _elements[5] / val,
                      _elements[6] / val, _elements[7] / val, _elements[8] / val);
    }

    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::rsub(T val) const
    {
        return Matrix(val - _elements[0], val - _elements[1], val - _elements[2],
                      val - _elements[3], val - _elements[4], val - _elements[5],
                      val - _elements[6], val - _elements[7], val - _elements[8]);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::rsub(const Matrix &other) const
    {
        return Matrix(other._elements[0] - _elements[0], other._elements[1] - _elements[1], other._elements[2] - _elements[2],
                      other._elements[3] - _elements[3], other._elements[4] - _elements[4], other._elements[5] - _elements[5],
                      other._elements[6] - _elements[6], other._elements[7] - _elements[7], other._elements[8] - _elements[8]);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::rmul(const Matrix &other) const
    {
        return other.mul(*this);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::rdiv(T val) const
    {
        return Matrix(val / _elements[0], val / _elements[1], val / _elements[2],
                      val / _elements[3], val / _elements[4], val / _elements[5],
                      val / _elements[6], val / _elements[7], val / _elements[8]);
    }
    template <typename T>
    void Matrix<T, 3, 3>::iadd(T val)
    {
        set(add(val));
    }
    template <typename T>
    void Matrix<T, 3, 3>::iadd(const Matrix &other)
    {
        set(add(other));
    }
    template <typename T>
    void Matrix<T, 3, 3>::isub(T val)
    {
        set(sub(val));
    }
    template <typename T>
    void Matrix<T, 3, 3>::isub(const Matrix &other)
    {
        set(sub(other));
    }
    template <typename T>
    void Matrix<T, 3, 3>::imul(T val)
    {
        set(mul(val));
    }
    template <typename T>
    void Matrix<T, 3, 3>::imul(const Matrix &other)
    {
        set(mul(other));
    }
    template <typename T>
    void Matrix<T, 3, 3>::idiv(T val)
    {
        set(div(val));
    }
    template <typename T>
    void Matrix<T, 3, 3>::transpose()
    {
        std::swap(_elements[1], _elements[3]);
        std::swap(_elements[2], _elements[6]);
        std::swap(_elements[5], _elements[7]);
    }
    template <typename T>
    void Matrix<T, 3, 3>::invert()
    {
        Matrix m;
        T d = determinant();
        assert((d != 0) && "matrix's determinant is zero.");
        m._elements[0] = _elements[4] * _elements[8] - _elements[5] * _elements[7];
        m._elements[1] = _elements[2] * _elements[7] - _elements[1] * _elements[8];
        m._elements[2] = _elements[1] * _elements[5] - _elements[2] * _elements[4];

        m._elements[3] = _elements[5] * _elements[6] - _elements[3] * _elements[8];
        m._elements[4] = _elements[0] * _elements[8] - _elements[2] * _elements[6];
        m._elements[5] = _elements[2] * _elements[3] - _elements[0] * _elements[5];

        m._elements[6] = _elements[3] * _elements[7] - _elements[4] * _elements[6];
        m._elements[7] = _elements[1] * _elements[6] - _elements[0] * _elements[7];
        m._elements[8] = _elements[0] * _elements[4] - _elements[1] * _elements[3];
        m.idiv(d);
        set(m);
    }

    template <typename T>
    T Matrix<T, 3, 3>::sum() const
    {
        return (_elements[0] + _elements[1] + _elements[2] +
                _elements[3] + _elements[4] + _elements[5] +
                _elements[6] + _elements[7] + _elements[8]);
    }

    template <typename T>
    T Matrix<T, 3, 3>::avg() const
    {
        return sum() / 9;
    }

    template <typename T>
    T Matrix<T, 3, 3>::min() const
    {
        return big::minn(data(), 9);
    }

    template <typename T>
    T Matrix<T, 3, 3>::max() const
    {
        return big::maxn(data(), 9);
    }

    template <typename T>
    T Matrix<T, 3, 3>::absmin() const
    {
        return big::absminn(data(), 9);
    }

    template <typename T>
    T Matrix<T, 3, 3>::absmax() const
    {
        return big::absmaxn(data(), 9);
    }

    template <typename T>
    T Matrix<T, 3, 3>::trace() const
    {
        return _elements[0] + _elements[4] + _elements[8];
    }

    template <typename T>
    T Matrix<T, 3, 3>::determinant() const
    {
        return _elements[0] * _elements[4] * _elements[8] +
               _elements[2] * _elements[3] * _elements[7] +
               _elements[1] * _elements[5] * _elements[6] -
               _elements[2] * _elements[4] * _elements[6] -
               _elements[1] * _elements[3] * _elements[8] -
               _elements[0] * _elements[5] * _elements[7];
    }
    template <typename T>
    void Matrix<T, 3, 3>::show() const
    {
        printf("%f %f %f %f %f %f %f %f %f\n", _elements[0], _elements[1], _elements[2],
               _elements[3], _elements[4], _elements[5],
               _elements[6], _elements[7], _elements[8]);
    }

    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::diagonal() const
    {
        return (Matrix(_elements[0], 0, 0,
                       0, _elements[4], 0,
                       0, 0, _elements[8]));
    }

    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::offDiagonal() const
    {
        return (Matrix(0, _elements[1], _elements[2],
                       _elements[3], 0, _elements[4],
                       _elements[6], _elements[7], 0));
    }

    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::strictLowerTri() const
    {
        return (Matrix(0, 0, 0,
                       _elements[3], 0, 0,
                       _elements[6], _elements[7], 0));
    }

    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::stricitUpperTri() const
    {
        return (Matrix(0, _elements[1], _elements[2],
                       0, 0, _elements[4],
                       0, 0, 0));
    }

    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::lowerTri() const
    {
        return (Matrix(_elements[0], 0, 0,
                       _elements[3], _elements[4], 0,
                       _elements[6], _elements[7], _elements[8]));
    }

    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::upperTri() const
    {
        return (Matrix(_elements[0], _elements[1], _elements[2],
                       0, _elements[4], _elements[5],
                       0, 0, _elements[8]));
    }

    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::transposed() const
    {
        return (Matrix(_elements[0], _elements[3], _elements[6],
                       _elements[1], _elements[4], _elements[7] _elements[2], _elements[5], _elements[8]));
    }

    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::inverse() const
    {
        Matrix m(*this);
        m.invert();
        return m;
    }

    template <typename T>
    T Matrix<T, 3, 3>::frobeniusNorm() const
    {
        return std::sqrt(_elements[0] * _elements[0] + _elements[1] * _elements[1] + _elements[2] * _elements[2] +
                         _elements[3] * _elements[3] + _elements[4] * _elements[4] + _elements[5] * _elements[5] +
                         _elements[6] * _elements[6] + _elements[7] * _elements[7] + _elements[8] * _elements[8]);
    }
    template <typename T>
    template <typename U>
    Matrix<U, 3, 3> Matrix<T, 3, 3>::castTo() const
    {
        return Matrix<U, 3, 3>(
            static_cast<U>(_elements[0]), static_cast<U>(_elements[1]), static_cast<U>(_elements[2]),
            static_cast<U>(_elements[3]), static_cast<U>(_elements[4]), static_cast<U>(_elements[5]),
            static_cast<U>(_elements[6]), static_cast<U>(_elements[7]), static_cast<U>(_elements[8]));
    }

    template <typename T>
    Matrix<T, 3, 3> &Matrix<T, 3, 3>::operator=(const Matrix &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    Matrix<T, 3, 3> &Matrix<T, 3, 3>::operator+=(T &s)
    {
        iadd(s);
        return *this;
    }

    template <typename T>
    Matrix<T, 3, 3> &Matrix<T, 3, 3>::operator+=(const Matrix &m)
    {
        iadd(m);
        return *this;
    }

    template <typename T>
    Matrix<T, 3, 3> &Matrix<T, 3, 3>::operator-=(T &s)
    {
        isub(s);
        return *this;
    }

    template <typename T>
    Matrix<T, 3, 3> &Matrix<T, 3, 3>::operator-=(const Matrix &m)
    {
        isub(m);
        return *this;
    }

    template <typename T>
    Matrix<T, 3, 3> &Matrix<T, 3, 3>::operator*=(T &s)
    {
        imul(s);
        return *this;
    }

    template <typename T>
    Matrix<T, 3, 3> &Matrix<T, 3, 3>::operator*=(const Matrix &m)
    {
        iadd(m);
        return *this;
    }

    template <typename T>
    Matrix<T, 3, 3> &Matrix<T, 3, 3>::operator/=(T &s)
    {
        idiv(s);
        return *this;
    }
    template <typename T>
    bool Matrix<T, 3, 3>::operator==(const Matrix &other) const
    {
        return (_elements[0] == other._elements[0] && _elements[1] == other._elements[1] && _elements[2] == other._elements[2] &&
                _elements[3] == other._elements[3] && _elements[4] == other._elements[4] && _elements[5] == other._elements[5] &&
                _elements[6] == other._elements[6] && _elements[7] == other._elements[7] && _elements[8] == other._elements[8]);
    }
    template <typename T>
    bool Matrix<T, 3, 3>::operator!=(const Matrix &other) const
    {
        return (_elements[0] != other._elements[0] || _elements[1] != other._elements[1] || _elements[2] != other._elements[2] ||
                _elements[3] != other._elements[3] || _elements[4] != other._elements[4] || _elements[5] != other._elements[5] ||
                _elements[6] != other._elements[6] || _elements[7] != other._elements[7] || _elements[8] != other._elements[8]);
    }

    template <typename T>
    T &Matrix<T, 3, 3>::operator()(std::size_t i, std::size_t j)
    {
        return _elements[i * 3 + j];
    }
    template <typename T>
    const T &Matrix<T, 3, 3>::operator()(std::size_t i, std::size_t j) const
    {
        return _elements[i * 3 + j];
    }
    template <typename T>
    T &Matrix<T, 3, 3>::operator[](std::size_t i)
    {
        return _elements[i];
    }
    template <typename T>
    const T &Matrix<T, 3, 3>::operator[](std::size_t i) const
    {
        return _elements[i];
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::makeZero()
    {
        return Matrix(0, 0, 0,
                      0, 0, 0,
                      0, 0, 0);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::makeIdentity()
    {
        return Matrix(1, 0, 0,
                      0, 1, 0,
                      0, 0, 1);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::makeScaleMatrix(T sx, T sy, T sz)
    {
        return Matrix(sx, 0, 0,
                      0, sy, 0,
                      0, 0, sz);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::makeScaleMatrix(const Vector<T, 3> &s)
    {
        return Matrix(s.x, 0, 0,
                      0, s.y, 0,
                      0, 0, s.z);
    }
    template <typename T>
    Matrix<T, 3, 3> Matrix<T, 3, 3>::makeRotationMatrix(const Vector<T, 3> &axis, T rad)
    {
        // https://zh.wikipedia.org/zh-sg/%E6%97%8B%E8%BD%AC%E7%9F%A9%E9%98%B5
        axis.normalize();
        T cos = std::cos(rad);
        T rad = std::sin(rad);
        T x = axis.x;
        T y = axis.y;
        T z = axis.z;
        return Matrix(cos + (1 - cos) * x * x, (1 - cos) * x * y - sin * z, (1 - cos) * x * z + sin * y,
                      (1 - cos) * y * x + sin * z, cos + (1 - cos) * y * y, (1 - cos) * y * z - sin * x,
                      (1 - cos) * z * x + sin * y, (1 - cos) * z * y - sin * x, cos + (1 - cos) * z * z);
    }

    template <typename T>
    Matrix<T, 3, 3> operator+(const Matrix<T, 3, 3> &a, const Matrix<T, 3, 3> &b)
    {
        return a.add(b);
    }

    template <typename T>
    Matrix<T, 3, 3> operator+(const Matrix<T, 3, 3> &a, T b)
    {

        return a.add(b);
    }

    template <typename T>
    Matrix<T, 3, 3> operator+(T a, const Matrix<T, 3, 3> &b)
    {
        return b.add(a);
    }

    template <typename T>
    Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3> &a, const Matrix<T, 3, 3> &b)
    {
        return a.sub(b);
    }

    template <typename T>
    Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3> &a, T b)
    {
        return a.sub(b);
    }

    template <typename T>
    Matrix<T, 3, 3> operator-(T a, const Matrix<T, 3, 3> &b)
    {
        return b.rsub(a);
    }

    template <typename T>
    Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3> &a)
    {
        return a.mul(-1);
    }

    template <typename T>
    Matrix<T, 3, 3> operator*(const Matrix<T, 3, 3> &a, const Matrix<T, 3, 3> &b)
    {
        return a.mul(b);
    }

    template <typename T>
    Matrix<T, 3, 3> operator*(const Matrix<T, 3, 3> &a, T b)
    {
        return a.mul(b);
    }

    template <typename T>
    Matrix<T, 3, 3> operator*(T a, const Matrix<T, 3, 3> &b)
    {
        return b.mul(a);
    }

    template <typename T>
    Matrix<T, 3, 3> operator*(const Matrix<T, 3, 3> &a, const Vector<T, 2> &b)
    {
        return a.mul(b);
    }

    template <typename T>
    Matrix<T, 3, 3> operator/(const Matrix<T, 3, 3> &a, T b)
    {
        return a.div(b);
    }

    template <typename T>
    Matrix<T, 3, 3> operator/(T a, const Matrix<T, 3, 3> &b)
    {
        return b.rdiv(a);
    }

}
#endif