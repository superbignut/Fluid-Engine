#ifndef INCLUDE_BIG_MATRIX4X4_INL_H_
#define INCLUDE_BIG_MATRIX4X4_INL_H_

#include <cstring>
namespace big
{

    template <typename T>
    Matrix<T, 4, 4>::Matrix()
    {
        _elements.fill(0);
    }
    template <typename T>
    Matrix<T, 4, 4>::Matrix(T s)
    {
        set(s);
    }
    template <typename T>
    Matrix<T, 4, 4>::Matrix(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)
    {
        set(m00, m01, m02, m10, m11, m12, m20, m21, m22);
    }
    template <typename T>
    Matrix<T, 4, 4>::Matrix(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33)
    {
        set(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
    }
    template <typename T>
    void Matrix<T, 4, 4>::set(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33)
    {
        _elements[0] = m00;
        _elements[1] = m01;
        _elements[2] = m02;
        _elements[3] = m03;

        _elements[4] = m10;
        _elements[5] = m11;
        _elements[6] = m12;
        _elements[7] = m13;

        _elements[8] = m20;
        _elements[9] = m21;
        _elements[10] = m22;
        _elements[11] = m23;

        _elements[12] = m30;
        _elements[13] = m31;
        _elements[14] = m32;
        _elements[15] = m33;
    }

    template <typename T>
    Matrix<T, 4, 4>::Matrix(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        set(lst);
    }
    template <typename T>
    Matrix<T, 4, 4>::Matrix(const Matrix &m)
    {
        set(m);
    }

    template <typename T>
    Matrix<T, 4, 4>::Matrix(const T *arr)
    {
        set(arr);
    }

    template <typename T>
    Matrix<T, 4, 4>::Matrix(const Matrix3x3<T> &m33)
    {
        set(m33);
    }

    template <typename T>
    void Matrix<T, 4, 4>::set(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)
    {
        _elements[0] = m00;
        _elements[1] = m01;
        _elements[2] = m02;
        _elements[3] = 0;

        _elements[4] = m10;
        _elements[5] = m11;
        _elements[6] = m12;
        _elements[7] = 0;

        _elements[8] = m20;
        _elements[9] = m21;
        _elements[10] = m22;
        _elements[11] = 0;

        _elements[12] = 0;
        _elements[13] = 0;
        _elements[14] = 0;
        _elements[15] = 1;
    }

    template <typename T>
    void Matrix<T, 4, 4>::set(const Matrix3x3<T> &m33)
    {
        set(m33[0], m33[1], m33[2],
            m33[3], m33[4], m33[5],
            m33[6], m33[7], m33[8]);
    }

    template <typename T>
    void Matrix<T, 4, 4>::set(const T *arr)
    {
        memcpy(_elements.data(), arr, sizeof(T) * 16);
    }

    template <typename T>
    void Matrix<T, 4, 4>::set(const Matrix &m)
    {
        memcpy(_elements.data(), m._elements.data(), sizeof(T) * 16);
    }

    template <typename T>
    void Matrix<T, 4, 4>::set(const std::initializer_list<std::initializer_list<T>> &lst)
    {
        std::size_t rows = lst.size();
        std::size_t cols = (rows != 0) ? lst.begin()->size() : 0;
        assert(rows == 4 && cols == 4 && "initializer_list has anMatrix<T, 4, 4>:: invalid size.");

        auto rowIter = lst.begin();
        for (std::size_t i = 0; i < rows; ++i)
        {
            auto colIter = rowIter->begin();
            assert(rowIter->size() == cols && "Error column sizeMatrix<T, 4, 4>:: inMatrix<T, 4, 4>:: iniitalizer_list."); // because eachMatrix<T, 4, 4>:: innerMatrix<T, 4, 4>:: initialize_list can have diff size.

            for (std::size_t j = 0; j < cols; ++j)
            {
                (*this)(i, j) = *colIter;
                ++colIter;
            }
            ++rowIter;
        }
    }

    template <typename T>
    void Matrix<T, 4, 4>::set(T s)
    {
        _elements.fill(s);
    }
    template <typename T>
    void Matrix<T, 4, 4>::setDiagnoal(T s)
    {
        _elements[0] = s;
        _elements[5] = s;
        _elements[10] = s;
        _elements[15] = s;
    }
    template <typename T>
    void Matrix<T, 4, 4>::setOffDiagnoal(T s)
    {
        _elements[1] = _elements[2] = _elements[3] = s;
        _elements[4] = _elements[6] = _elements[7] = s;
        _elements[8] = _elements[9] = _elements[11] = s;
        _elements[12] = _elements[13] = _elements[14] = s;
    }
    template <typename T>
    void Matrix<T, 4, 4>::setRow(std::size_t i, const Vector<T, 4> &row)
    {
        _elements[4 * i] = row.x;
        _elements[4 * i + 1] = row.y;
        _elements[4 * i + 2] = row.z;
        _elements[4 * i + 3] = row.w;
    }
    template <typename T>
    void Matrix<T, 4, 4>::setCol(std::size_t i, const Vector<T, 4> &col)
    {
        _elements[i] = col.x;
        _elements[i + 4] = col.y;
        _elements[i + 8] = col.z;
        _elements[i + 12] = col.w;
    }
    template <typename T>
    bool Matrix<T, 4, 4>::isSimilar(const Matrix &other, double tol) const
    {
        for (std::size_t i = 0; i < 4; ++i)
        {
            for (std::size_t j = 0; j < 4; ++j)
            {
                if (std::fabs((*this)(i, j) - other(i, j)) > tol)
                    return false;
            }
        }
        return true;
    }

    template <typename T>
    constexpr bool Matrix<T, 4, 4>::isSquare() const
    {
        return true;
    }

    template <typename T>
    constexpr std::size_t Matrix<T, 4, 4>::rows() const
    {
        return 4;
    }
    template <typename T>
    constexpr std::size_t Matrix<T, 4, 4>::cols() const
    {
        return 4;
    }

    template <typename T>
    T *Matrix<T, 4, 4>::data()
    {
        return _elements.data();
    }
    template <typename T>
    const T *const Matrix<T, 4, 4>::data() const
    {
        return _elements.data();
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::add(T val) const
    {
        return Matrix(_elements[0] + val,
                      _elements[1] + val,
                      _elements[2] + val,
                      _elements[3] + val,
                      _elements[4] + val,
                      _elements[5] + val,
                      _elements[6] + val,
                      _elements[7] + val,
                      _elements[8] + val,
                      _elements[9] + val,
                      _elements[10] + val,
                      _elements[11] + val,
                      _elements[12] + val,
                      _elements[13] + val,
                      _elements[14] + val,
                      _elements[15] + val);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::add(const Matrix &other) const
    {
        return Matrix(_elements[0] + other._elements[0],
                      _elements[1] + other._elements[1],
                      _elements[2] + other._elements[2],
                      _elements[3] + other._elements[3],
                      _elements[4] + other._elements[4],
                      _elements[5] + other._elements[5],
                      _elements[6] + other._elements[6],
                      _elements[7] + other._elements[7],
                      _elements[8] + other._elements[8],
                      _elements[9] + other._elements[9],
                      _elements[10] + other._elements[10],
                      _elements[11] + other._elements[11],
                      _elements[12] + other._elements[12],
                      _elements[13] + other._elements[13],
                      _elements[14] + other._elements[14],
                      _elements[15] + other._elements[15]);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::sub(T val) const
    {
        return Matrix(_elements[0] - val,
                      _elements[1] - val,
                      _elements[2] - val,
                      _elements[3] - val,
                      _elements[4] - val,
                      _elements[5] - val,
                      _elements[6] - val,
                      _elements[7] - val,
                      _elements[8] - val,
                      _elements[9] - val,
                      _elements[10] - val,
                      _elements[11] - val,
                      _elements[12] - val,
                      _elements[13] - val,
                      _elements[14] - val,
                      _elements[15] - val);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::sub(const Matrix &other) const
    {
        return Matrix(_elements[0] - other._elements[0],
                      _elements[1] - other._elements[1],
                      _elements[2] - other._elements[2],
                      _elements[3] - other._elements[3],
                      _elements[4] - other._elements[4],
                      _elements[5] - other._elements[5],
                      _elements[6] - other._elements[6],
                      _elements[7] - other._elements[7],
                      _elements[8] - other._elements[8],
                      _elements[9] - other._elements[9],
                      _elements[10] - other._elements[10],
                      _elements[11] - other._elements[11],
                      _elements[12] - other._elements[12],
                      _elements[13] - other._elements[13],
                      _elements[14] - other._elements[14],
                      _elements[15] - other._elements[15]);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::mul(T val) const
    {
        return Matrix(_elements[0] * val,
                      _elements[1] * val,
                      _elements[2] * val,
                      _elements[3] * val,
                      _elements[4] * val,
                      _elements[5] * val,
                      _elements[6] * val,
                      _elements[7] * val,
                      _elements[8] * val,
                      _elements[9] * val,
                      _elements[10] * val,
                      _elements[11] * val,
                      _elements[12] * val,
                      _elements[13] * val,
                      _elements[14] * val,
                      _elements[15] * val);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::mul(const Matrix &other) const
    {
        return Matrix(_elements[0] * other._elements[0] + _elements[1] * other._elements[4] + _elements[2] * other._elements[8] + _elements[3] * other._elements[12],
                      _elements[0] * other._elements[1] + _elements[1] * other._elements[5] + _elements[2] * other._elements[9] + _elements[3] * other._elements[13],
                      _elements[0] * other._elements[2] + _elements[1] * other._elements[6] + _elements[2] * other._elements[10] + _elements[3] * other._elements[14],
                      _elements[0] * other._elements[3] + _elements[1] * other._elements[7] + _elements[2] * other._elements[11] + _elements[3] * other._elements[15],

                      _elements[4] * other._elements[0] + _elements[5] * other._elements[4] + _elements[6] * other._elements[8] + _elements[7] * other._elements[12],
                      _elements[4] * other._elements[1] + _elements[5] * other._elements[5] + _elements[6] * other._elements[9] + _elements[7] * other._elements[13],
                      _elements[4] * other._elements[2] + _elements[5] * other._elements[6] + _elements[6] * other._elements[10] + _elements[7] * other._elements[14],
                      _elements[4] * other._elements[3] + _elements[5] * other._elements[7] + _elements[6] * other._elements[11] + _elements[7] * other._elements[15],

                      _elements[8] * other._elements[0] + _elements[9] * other._elements[4] + _elements[10] * other._elements[8] + _elements[11] * other._elements[12],
                      _elements[8] * other._elements[1] + _elements[9] * other._elements[5] + _elements[10] * other._elements[9] + _elements[11] * other._elements[13],
                      _elements[8] * other._elements[2] + _elements[9] * other._elements[6] + _elements[10] * other._elements[10] + _elements[11] * other._elements[14],
                      _elements[8] * other._elements[3] + _elements[9] * other._elements[7] + _elements[10] * other._elements[11] + _elements[11] * other._elements[15],

                      _elements[12] * other._elements[0] + _elements[13] * other._elements[4] + _elements[14] * other._elements[8] + _elements[15] * other._elements[12],
                      _elements[12] * other._elements[1] + _elements[13] * other._elements[5] + _elements[14] * other._elements[9] + _elements[15] * other._elements[13],
                      _elements[12] * other._elements[2] + _elements[13] * other._elements[6] + _elements[14] * other._elements[10] + _elements[15] * other._elements[14],
                      _elements[12] * other._elements[3] + _elements[13] * other._elements[7] + _elements[14] * other._elements[11] + _elements[15] * other._elements[15]);
    }

    template <typename T>
    Vector<T, 4> Matrix<T, 4, 4>::mul(const Vector<T, 4> &v) const
    {
        return Vector<T, 4>(
            _elements[0] * v.x + _elements[1] * v.y + _elements[2] * v.z + _elements[3] * v.w,
            _elements[4] * v.x + _elements[5] * v.y + _elements[6] * v.z + _elements[7] * v.w,
            _elements[8] * v.x + _elements[9] * v.y + _elements[10] * v.z + _elements[11] * v.w,
            _elements[12] * v.x + _elements[13] * v.y + _elements[14] * v.z + _elements[15] * v.w);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::div(T val) const
    {
        return Matrix(_elements[0] / val,
                      _elements[1] / val,
                      _elements[2] / val,
                      _elements[3] / val,
                      _elements[4] / val,
                      _elements[5] / val,
                      _elements[6] / val,
                      _elements[7] / val,
                      _elements[8] / val,
                      _elements[9] / val,
                      _elements[10] / val,
                      _elements[11] / val,
                      _elements[12] / val,
                      _elements[13] / val,
                      _elements[14] / val,
                      _elements[15] / val);
    }

    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::rsub(T val) const
    {
        return Matrix(val - _elements[0],
                      val - _elements[1],
                      val - _elements[2],
                      val - _elements[3],
                      val - _elements[4],
                      val - _elements[5],
                      val - _elements[6],
                      val - _elements[7],
                      val - _elements[8],
                      val - _elements[9],
                      val - _elements[10],
                      val - _elements[11],
                      val - _elements[12],
                      val - _elements[13],
                      val - _elements[14],
                      val - _elements[15]);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::rsub(const Matrix &other) const
    {
        return Matrix(other._elements[0] - _elements[0],
                      other._elements[1] - _elements[1],
                      other._elements[2] - _elements[2],
                      other._elements[3] - _elements[3],
                      other._elements[4] - _elements[4],
                      other._elements[5] - _elements[5],
                      other._elements[6] - _elements[6],
                      other._elements[7] - _elements[7],
                      other._elements[8] - _elements[8],
                      other._elements[9] - _elements[9],
                      other._elements[10] - _elements[10],
                      other._elements[11] - _elements[11],
                      other._elements[12] - _elements[12],
                      other._elements[13] - _elements[13],
                      other._elements[14] - _elements[14],
                      other._elements[15] - _elements[15]);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::rmul(const Matrix &other) const
    {
        return other.mul(*this);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::rdiv(T val) const
    {
        return Matrix(val / _elements[0],
                      val / _elements[1],
                      val / _elements[2],
                      val / _elements[3],
                      val / _elements[4],
                      val / _elements[5],
                      val / _elements[6],
                      val / _elements[7],
                      val / _elements[8],
                      val / _elements[9],
                      val / _elements[10],
                      val / _elements[11],
                      val / _elements[12],
                      val / _elements[13],
                      val / _elements[14],
                      val / _elements[15]);
    }
    template <typename T>
    void Matrix<T, 4, 4>::iadd(T val)
    {
        set(add(val));
    }
    template <typename T>
    void Matrix<T, 4, 4>::iadd(const Matrix &other)
    {
        set(add(other));
    }
    template <typename T>
    void Matrix<T, 4, 4>::isub(T val)
    {
        set(sub(val));
    }
    template <typename T>
    void Matrix<T, 4, 4>::isub(const Matrix &other)
    {
        set(sub(other));
    }
    template <typename T>
    void Matrix<T, 4, 4>::imul(T val)
    {
        set(mul(val));
    }
    template <typename T>
    void Matrix<T, 4, 4>::imul(const Matrix &other)
    {
        set(mul(other));
    }
    template <typename T>
    void imul(const Matrix3x3<T> &other)
    {
        assert(false && " Can it be used?");
    }

    template <typename T>
    void Matrix<T, 4, 4>::idiv(T val)
    {
        set(div(val));
    }
    template <typename T>
    void Matrix<T, 4, 4>::transpose()
    {
        std::swap(_elements[1], _elements[4]);
        std::swap(_elements[2], _elements[8]);
        std::swap(_elements[9], _elements[6]);
        std::swap(_elements[3], _elements[12]);
        std::swap(_elements[7], _elements[13]);
        std::swap(_elements[11], _elements[14]);
    }
    template <typename T>
    void Matrix<T, 4, 4>::invert()
    {
        Matrix m;
        T d = determinant();
        assert((d != 0) && "matrix's determinant is zero.");
        m._elements[0] = _elements[5] * _elements[10] * _elements[15] + _elements[9] * _elements[14] * _elements[7] + _elements[13] * _elements[6] * _elements[11] - _elements[7] * _elements[10] * _elements[13] - _elements[6] * _elements[9] * _elements[15] - _elements[5] * _elements[11] * _elements[14];
        m._elements[1] = _elements[4] * _elements[10] * _elements[15] + _elements[8] * _elements[14] * _elements[7] + _elements[12] * _elements[6] * _elements[11] - _elements[7] * _elements[10] * _elements[12] - _elements[6] * _elements[8] * _elements[15] - _elements[4] * _elements[11] * _elements[14];
        m._elements[1] = -m._elements[1];

        m._elements[2] = _elements[4] * _elements[9] * _elements[15] + _elements[8] * _elements[13] * _elements[7] + _elements[12] * _elements[5] * _elements[11] - _elements[7] * _elements[9] * _elements[12] - _elements[5] * _elements[8] * _elements[15] - _elements[4] * _elements[11] * _elements[13];
        m._elements[3] = _elements[4] * _elements[9] * _elements[14] + _elements[8] * _elements[13] * _elements[6] + _elements[12] * _elements[5] * _elements[10] - _elements[6] * _elements[9] * _elements[12] - _elements[5] * _elements[8] * _elements[14] - _elements[4] * _elements[10] * _elements[13];
        m._elements[3] = -m._elements[3];

        m._elements[4] = _elements[1] * _elements[10] * _elements[15] + _elements[9] * _elements[14] * _elements[3] + _elements[13] * _elements[2] * _elements[11] - _elements[3] * _elements[10] * _elements[13] - _elements[2] * _elements[9] * _elements[15] - _elements[1] * _elements[11] * _elements[14];
        m._elements[4] = -m._elements[4];

        m._elements[5] = _elements[0] * _elements[10] * _elements[15] + _elements[8] * _elements[14] * _elements[3] + _elements[12] * _elements[2] * _elements[11] - _elements[3] * _elements[10] * _elements[12] - _elements[2] * _elements[8] * _elements[15] - _elements[0] * _elements[11] * _elements[14];
        m._elements[6] = _elements[0] * _elements[9] * _elements[15] + _elements[8] * _elements[13] * _elements[3] + _elements[12] * _elements[1] * _elements[11] - _elements[3] * _elements[9] * _elements[12] - _elements[1] * _elements[8] * _elements[15] - _elements[0] * _elements[11] * _elements[13];
        m._elements[6] = -m._elements[6];

        m._elements[7] = _elements[0] * _elements[9] * _elements[14] + _elements[8] * _elements[13] * _elements[2] + _elements[12] * _elements[1] * _elements[10] - _elements[2] * _elements[9] * _elements[12] - _elements[1] * _elements[8] * _elements[14] - _elements[0] * _elements[10] * _elements[13];
        m._elements[8] = _elements[1] * _elements[6] * _elements[15] + _elements[5] * _elements[14] * _elements[3] + _elements[13] * _elements[2] * _elements[7] - _elements[3] * _elements[6] * _elements[13] - _elements[2] * _elements[5] * _elements[15] - _elements[1] * _elements[7] * _elements[14];
        m._elements[9] = _elements[0] * _elements[6] * _elements[15] + _elements[4] * _elements[14] * _elements[3] + _elements[12] * _elements[2] * _elements[7] - _elements[3] * _elements[6] * _elements[12] - _elements[2] * _elements[4] * _elements[15] - _elements[0] * _elements[7] * _elements[14];
        m._elements[9] = -m._elements[9];

        m._elements[10] = _elements[0] * _elements[5] * _elements[15] + _elements[4] * _elements[13] * _elements[3] + _elements[12] * _elements[1] * _elements[7] - _elements[3] * _elements[5] * _elements[12] - _elements[1] * _elements[4] * _elements[15] - _elements[0] * _elements[7] * _elements[13];
        m._elements[11] = _elements[0] * _elements[5] * _elements[14] + _elements[4] * _elements[13] * _elements[2] + _elements[12] * _elements[1] * _elements[6] - _elements[2] * _elements[5] * _elements[12] - _elements[1] * _elements[4] * _elements[14] - _elements[0] * _elements[6] * _elements[13];
        m._elements[11] = -m._elements[11];

        m._elements[12] = _elements[1] * _elements[6] * _elements[11] + _elements[5] * _elements[10] * _elements[3] + _elements[9] * _elements[2] * _elements[7] - _elements[3] * _elements[6] * _elements[9] - _elements[2] * _elements[5] * _elements[11] - _elements[1] * _elements[7] * _elements[10];
        m._elements[12] = -m._elements[12];

        m._elements[13] = _elements[0] * _elements[6] * _elements[11] + _elements[4] * _elements[10] * _elements[3] + _elements[8] * _elements[2] * _elements[7] - _elements[3] * _elements[6] * _elements[8] - _elements[2] * _elements[4] * _elements[11] - _elements[0] * _elements[7] * _elements[10];
        m._elements[14] = _elements[0] * _elements[5] * _elements[11] + _elements[4] * _elements[9] * _elements[3] + _elements[8] * _elements[1] * _elements[7] - _elements[3] * _elements[5] * _elements[8] - _elements[1] * _elements[4] * _elements[11] - _elements[0] * _elements[7] * _elements[9];
        m._elements[14] = -m._elements[14];

        m._elements[15] = _elements[0] * _elements[5] * _elements[10] + _elements[4] * _elements[9] * _elements[2] + _elements[8] * _elements[1] * _elements[6] - _elements[2] * _elements[5] * _elements[8] - _elements[1] * _elements[4] * _elements[10] - _elements[0] * _elements[6] * _elements[9];

        m.idiv(d);

        m.transpose();

        set(m);
    }

    template <typename T>
    T Matrix<T, 4, 4>::sum() const
    {
        return (_elements[0] + _elements[1] + _elements[2] +
                _elements[3] + _elements[4] + _elements[5] +
                _elements[6] + _elements[7] + _elements[8]);
    }

    template <typename T>
    T Matrix<T, 4, 4>::avg() const
    {
        return sum() / 9;
    }

    template <typename T>
    T Matrix<T, 4, 4>::min() const
    {
        return big::minn(data(), 9);
    }

    template <typename T>
    T Matrix<T, 4, 4>::max() const
    {
        return big::maxn(data(), 9);
    }

    template <typename T>
    T Matrix<T, 4, 4>::absmin() const
    {
        return big::absminn(data(), 9);
    }

    template <typename T>
    T Matrix<T, 4, 4>::absmax() const
    {
        return big::absmaxn(data(), 9);
    }

    template <typename T>
    T Matrix<T, 4, 4>::trace() const
    {
        return _elements[0] + _elements[4] + _elements[8];
    }

    template <typename T>
    T Matrix<T, 4, 4>::determinant() const
    {

        T A00 = _elements[5] * _elements[10] * _elements[15] + _elements[9] * _elements[14] * _elements[7] + _elements[13] * _elements[6] * _elements[11] - _elements[7] * _elements[10] * _elements[13] - _elements[6] * _elements[9] * _elements[15] - _elements[5] * _elements[11] * _elements[14];
        T A01 = _elements[4] * _elements[10] * _elements[15] + _elements[8] * _elements[14] * _elements[7] + _elements[12] * _elements[6] * _elements[11] - _elements[7] * _elements[10] * _elements[12] - _elements[6] * _elements[8] * _elements[15] - _elements[4] * _elements[11] * _elements[14];

        T A02 = _elements[4] * _elements[9] * _elements[15] + _elements[8] * _elements[13] * _elements[7] + _elements[12] * _elements[5] * _elements[11] - _elements[7] * _elements[9] * _elements[12] - _elements[5] * _elements[8] * _elements[15] - _elements[4] * _elements[11] * _elements[13];
        T A03 = _elements[4] * _elements[9] * _elements[14] + _elements[8] * _elements[13] * _elements[6] + _elements[12] * _elements[5] * _elements[10] - _elements[6] * _elements[9] * _elements[12] - _elements[5] * _elements[8] * _elements[14] - _elements[4] * _elements[10] * _elements[13];

        return _elements[0] * A00 - _elements[1] * A01 + _elements[2] * A02 - _elements[3] * A03;
    }
    template <typename T>
    void Matrix<T, 4, 4>::show() const
    {
        std::cout << "Matrix:" << std::endl;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                std::cout << (*this)(i, j);
                if (j < 3)
                    std::cout << " ";
                else
                    std::cout << std::endl;
            }
        }
        // std::cout << "det is :" << determinant() << std::endl;
    }

    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::diagonal() const
    {
        return (Matrix(_elements[0], 0, 0,
                       0, _elements[4], 0,
                       0, 0, _elements[8]));
    }

    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::offDiagonal() const
    {
        return (Matrix(0, _elements[1], _elements[2],
                       _elements[3], 0, _elements[4],
                       _elements[6], _elements[7], 0));
    }

    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::strictLowerTri() const
    {
        return (Matrix(0, 0, 0,
                       _elements[3], 0, 0,
                       _elements[6], _elements[7], 0));
    }

    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::stricitUpperTri() const
    {
        return (Matrix(0, _elements[1], _elements[2],
                       0, 0, _elements[4],
                       0, 0, 0));
    }

    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::lowerTri() const
    {
        return (Matrix(_elements[0], 0, 0,
                       _elements[3], _elements[4], 0,
                       _elements[6], _elements[7], _elements[8]));
    }

    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::upperTri() const
    {
        return (Matrix(_elements[0], _elements[1], _elements[2],
                       0, _elements[4], _elements[5],
                       0, 0, _elements[8]));
    }

    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::transposed() const
    {
        return (Matrix(_elements[0], _elements[3], _elements[6],
                       _elements[1], _elements[4], _elements[7], _elements[2], _elements[5], _elements[8]));
    }

    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::inverse() const
    {
        Matrix m(*this);
        m.invert();
        return m;
    }

    template <typename T>
    T Matrix<T, 4, 4>::frobeniusNorm() const
    {
        return std::sqrt(_elements[0] * _elements[0] + _elements[1] * _elements[1] + _elements[2] * _elements[2] +
                         _elements[3] * _elements[3] + _elements[4] * _elements[4] + _elements[5] * _elements[5] +
                         _elements[6] * _elements[6] + _elements[7] * _elements[7] + _elements[8] * _elements[8]);
    }
    template <typename T>
    template <typename U>
    Matrix<U, 4, 4> Matrix<T, 4, 4>::castTo() const
    {
        return Matrix<U, 4, 4>(
            static_cast<U>(_elements[0]), static_cast<U>(_elements[1]), static_cast<U>(_elements[2]),
            static_cast<U>(_elements[3]), static_cast<U>(_elements[4]), static_cast<U>(_elements[5]),
            static_cast<U>(_elements[6]), static_cast<U>(_elements[7]), static_cast<U>(_elements[8]));
    }

    template <typename T>
    Matrix<T, 4, 4> &Matrix<T, 4, 4>::operator=(const Matrix &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    Matrix<T, 4, 4> &Matrix<T, 4, 4>::operator+=(T &s)
    {
        iadd(s);
        return *this;
    }

    template <typename T>
    Matrix<T, 4, 4> &Matrix<T, 4, 4>::operator+=(const Matrix &m)
    {
        iadd(m);
        return *this;
    }

    template <typename T>
    Matrix<T, 4, 4> &Matrix<T, 4, 4>::operator-=(T &s)
    {
        isub(s);
        return *this;
    }

    template <typename T>
    Matrix<T, 4, 4> &Matrix<T, 4, 4>::operator-=(const Matrix &m)
    {
        isub(m);
        return *this;
    }

    template <typename T>
    Matrix<T, 4, 4> &Matrix<T, 4, 4>::operator*=(T &s)
    {
        imul(s);
        return *this;
    }

    template <typename T>
    Matrix<T, 4, 4> &Matrix<T, 4, 4>::operator*=(const Matrix &m)
    {
        iadd(m);
        return *this;
    }

    template <typename T>
    Matrix<T, 4, 4> &Matrix<T, 4, 4>::operator/=(T &s)
    {
        idiv(s);
        return *this;
    }
    template <typename T>
    bool Matrix<T, 4, 4>::operator==(const Matrix &other) const
    {
        return (_elements[0] == other._elements[0] && _elements[1] == other._elements[1] && _elements[2] == other._elements[2] &&
                _elements[3] == other._elements[3] && _elements[4] == other._elements[4] && _elements[5] == other._elements[5] &&
                _elements[6] == other._elements[6] && _elements[7] == other._elements[7] && _elements[8] == other._elements[8]);
    }
    template <typename T>
    bool Matrix<T, 4, 4>::operator!=(const Matrix &other) const
    {
        return (_elements[0] != other._elements[0] || _elements[1] != other._elements[1] || _elements[2] != other._elements[2] ||
                _elements[3] != other._elements[3] || _elements[4] != other._elements[4] || _elements[5] != other._elements[5] ||
                _elements[6] != other._elements[6] || _elements[7] != other._elements[7] || _elements[8] != other._elements[8]);
    }

    template <typename T>
    T &Matrix<T, 4, 4>::operator()(std::size_t i, std::size_t j)
    {
        return _elements[i * 4 + j];
    }
    template <typename T>
    const T &Matrix<T, 4, 4>::operator()(std::size_t i, std::size_t j) const
    {
        return _elements[i * 4 + j];
    }
    template <typename T>
    T &Matrix<T, 4, 4>::operator[](std::size_t i)
    {
        return _elements[i];
    }
    template <typename T>
    const T &Matrix<T, 4, 4>::operator[](std::size_t i) const
    {
        return _elements[i];
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::makeZero()
    {
        return Matrix(0, 0, 0,
                      0, 0, 0,
                      0, 0, 0);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::makeIdentity()
    {
        return Matrix(1, 0, 0,
                      0, 1, 0,
                      0, 0, 1);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::makeScaleMatrix(T sx, T sy, T sz)
    {
        return Matrix(sx, 0, 0,
                      0, sy, 0,
                      0, 0, sz);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::makeScaleMatrix(const Vector<T, 3> &s)
    {
        return Matrix(s.x, 0, 0,
                      0, s.y, 0,
                      0, 0, s.z);
    }
    template <typename T>
    Matrix<T, 4, 4> Matrix<T, 4, 4>::makeRotationMatrix(const Vector<T, 3> &axis, T rad)
    {
        // https://zh.wikipedia.org/zh-sg/%E6%97%8B%E8%BD%AC%E7%9F%A9%E9%98%B5
        axis.normalize();
        T cos = std::cos(rad);
        T sin = std::sin(rad);
        T x = axis.x;
        T y = axis.y;
        T z = axis.z;
        return Matrix(cos + (1 - cos) * x * x, (1 - cos) * x * y - sin * z, (1 - cos) * x * z + sin * y,
                      (1 - cos) * y * x + sin * z, cos + (1 - cos) * y * y, (1 - cos) * y * z - sin * x,
                      (1 - cos) * z * x + sin * y, (1 - cos) * z * y - sin * x, cos + (1 - cos) * z * z);
    }

    template <typename T>
    Matrix<T, 4, 4> operator+(const Matrix<T, 4, 4> &a, const Matrix<T, 4, 4> &b)
    {
        return a.add(b);
    }

    template <typename T>
    Matrix<T, 4, 4> operator+(const Matrix<T, 4, 4> &a, T b)
    {

        return a.add(b);
    }

    template <typename T>
    Matrix<T, 4, 4> operator+(T a, const Matrix<T, 4, 4> &b)
    {
        return b.add(a);
    }

    template <typename T>
    Matrix<T, 4, 4> operator-(const Matrix<T, 4, 4> &a, const Matrix<T, 4, 4> &b)
    {
        return a.sub(b);
    }

    template <typename T>
    Matrix<T, 4, 4> operator-(const Matrix<T, 4, 4> &a, T b)
    {
        return a.sub(b);
    }

    template <typename T>
    Matrix<T, 4, 4> operator-(T a, const Matrix<T, 4, 4> &b)
    {
        return b.rsub(a);
    }

    template <typename T>
    Matrix<T, 4, 4> operator-(const Matrix<T, 4, 4> &a)
    {
        return a.mul(-1);
    }

    template <typename T>
    Matrix<T, 4, 4> operator*(const Matrix<T, 4, 4> &a, const Matrix<T, 4, 4> &b)
    {
        return a.mul(b);
    }

    template <typename T>
    Matrix<T, 4, 4> operator*(const Matrix<T, 4, 4> &a, T b)
    {
        return a.mul(b);
    }

    template <typename T>
    Matrix<T, 4, 4> operator*(T a, const Matrix<T, 4, 4> &b)
    {
        return b.mul(a);
    }

    template <typename T>
    Matrix<T, 4, 4> operator*(const Matrix<T, 4, 4> &a, const Vector<T, 2> &b)
    {
        return a.mul(b);
    }

    template <typename T>
    Matrix<T, 4, 4> operator/(const Matrix<T, 4, 4> &a, T b)
    {
        return a.div(b);
    }

    template <typename T>
    Matrix<T, 4, 4> operator/(T a, const Matrix<T, 4, 4> &b)
    {
        return b.rdiv(a);
    }

}
#endif