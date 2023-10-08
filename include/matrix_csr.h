#ifndef INCLUDE_BIG_MATRIXCSR_H_
#define INCLUDE_BIG_MATRIXCSR_H_
#include "matrix.h"
#include "size2.h"
// #include <tuple>
namespace big
{
    // declare MatrixCsr
    template <typename T>
    class MatrixCsr;
    //
    // M * v return type
    template <typename T, typename VE>
    class MatrixCsrVectorMul : public VectorExpression<T, MatrixCsrVectorMul<T, VE>>
    {
    public:
        MatrixCsrVectorMul(const MatrixCsr<T> &m, const VE &v);
        // why has this copy constructor?
        MatrixCsrVectorMul(const MatrixCsrVectorMul &other);

        std::size_t size() const;

        T operator[](std::size_t i) const;

    private:
        const MatrixCsr<T> &_m; // const ensure it can't be changed and & avoid copy. so as its name, class itself is  just an expression.
        const VE &_v;
        // const VE& _v2;
    };
    //
    // M * M return type
    template <typename T, typename ME>
    class MatrixCsrMatrixMul : public MatrixExpression<T, MatrixCsrMatrixMul<T, ME>>
    {
    public:
        MatrixCsrMatrixMul(const MatrixCsr<T> &m1, const ME &m2);

        Size2 size() const;

        std::size_t rows() const;

        std::size_t cols() const;

        T operator()(std::size_t i, std::size_t j) const;

    private:
        const MatrixCsr<T> &_m1; // const ensure it can't be changed and & avoid copy. so as its name, class itself is  just an expression.
        const ME &_m2;
        // define three var below for the easyness to use
        const T *const _nnz;
        const std::size_t *const _rp;
        const std::size_t *const _ci;
        // const VE& _v2;
    };
    // defination MatrixCsr
    template <typename T>
    class MatrixCsr final : public MatrixExpression<T, MatrixCsr<T>>
    {
    public:
        static_assert(std::is_floating_point<T>::value, "Matrix only can be instantiated with float point types.");

        struct Element
        {
            std::size_t i;
            std::size_t j;
            T value;

            Element();

            Element(std::size_t i, std::size_t j, const T &value);
        };

        typedef std::vector<T> NonZeroContainterType;
        typedef typename NonZeroContainterType::iterator NonZeroIterator;
        typedef typename NonZeroContainterType::const_iterator ConstNonZeroIterator;

        typedef std::vector<std::size_t> IndexContainterType;
        typedef typename IndexContainterType::iterator IndexIterator;
        typedef typename IndexContainterType::const_iterator ConstIndexIterator;

        //! \brief init with all zero.
        MatrixCsr();

        //! \brief init with lst whose value is greater than epslion.
        MatrixCsr(const std::initializer_list<std::initializer_list<T>> &lst, T epslion = std::numeric_limits<T>::epsilon());

        //! init with normal matrix.
        template <typename E>
        MatrixCsr(const MatrixExpression<T, E> &other, T epslion = std::numeric_limits<T>::epsilon());

        //! \brief init with other whose value is greater than epslion.
        MatrixCsr(const MatrixCsr &other, T epslion = std::numeric_limits<T>::epsilon());

        //! \brief init with other by std::move().
        MatrixCsr(const MatrixCsr &&other); // without const

        //! \brief clear all data and row_ptr.push_back(0).
        void clear();

        //! \brief  Set all nonzero value to s.
        void set(T s);

        //! \brief  Copy all data from other.
        void set(const MatrixCsr &other);

        //! \brief reshape the data with new size, destory the original data.
        void reserve(std::size_t rows, std::size_t cols, std::size_t numNonZeros);

        //! lst -> csr
        void compress(const std::initializer_list<std::initializer_list<T>> &lst, T epslion = std::numeric_limits<T>::epsilon());

        //! matrixExpression -> csr
        template <typename E>
        void compress(const MatrixExpression<T, E> &other, T epslion = std::numeric_limits<T>::epsilon());

        //! show data in csr
        void show(std::size_t i = 0, std::size_t j =0) const;

        //! add a new element, but you must ensure original (i,j) is zero or not exits.(allows bigger)
        void addElement(std::size_t i, std::size_t j, T value);

        //! add a new element, but you must ensure original (i,j) is zero or not exits.(allows bigger)
        void addElement(const Element &element);

        //! add a new row, allows cols bigger.
        void addRow(const NonZeroContainterType &nonZeros, const IndexContainterType &columnIndex);
        
        //! judge if hasElement and add/change it.
        void setElement(std::size_t i, std::size_t j, T value);

        //! judge if hasElement and add/change it.
        void setElement(const Element &element);

        bool isEqual(const MatrixCsr &other) const;

        bool isSimilar(const MatrixCsr &other, double tol = std::numeric_limits<double>::epsilon()) const;

        constexpr bool isSquare() const;

        constexpr std::size_t rows() const;

        constexpr std::size_t cols() const;

        Size2 size() const;

        std::size_t numberNonZeros() const;

        T &nonZero(std::size_t i);

        const T &nonZero(std::size_t i) const;

        const std::size_t &rowPointer(std::size_t i) const;

        const std::size_t &colIndex(std::size_t i) const;

        T *nonZeroData();

        const T *const nonZeroData() const;

        const std::size_t *const rowPointerData() const;

        const std::size_t *const colIndexData() const;

        NonZeroIterator nonZeroBegin();

        NonZeroIterator nonZeroEnd();

        IndexIterator rowPointerBegin();

        IndexIterator rowPointerEnd();

        IndexIterator colIndexBegin();

        IndexIterator colIndexEnd();

        ConstNonZeroIterator nonZeroBegin() const;

        ConstNonZeroIterator nonZeroEnd() const;

        ConstIndexIterator rowPointerBegin() const;

        ConstIndexIterator rowPointerEnd() const;

        ConstIndexIterator colIndexBegin() const;

        ConstIndexIterator colIndexEnd() const;

        MatrixCsr add(const T &s) const;

        MatrixCsr add(const MatrixCsr &m) const;

        MatrixCsr sub(const T &s) const;

        MatrixCsr sub(const MatrixCsr &m) const;

        MatrixCsr mul(const T &s) const;

        template <typename VE>
        MatrixCsrVectorMul<T, VE> mul(const VectorExpression<T, VE> &v) const;

        template <typename ME>
        MatrixCsrMatrixMul<T, ME> mul(const MatrixExpression<T, ME> &m) const;

        MatrixCsr div(const T &s) const;

        MatrixCsr rsub(const T &s) const;

        MatrixCsr rsub(const MatrixCsr &m) const;

        MatrixCsr rdiv(const T &s) const;

        void iadd(const T &s);

        void iadd(const MatrixCsr &m);

        void isub(const T &s);

        void isub(const MatrixCsr &m);

        void imul(const T &s);

        template <typename ME>
        void imul(const MatrixExpression<T, ME> &m);

        void idiv(const T &s);

        T sum() const;

        T avg() const;

        T min() const;

        T max() const;

        T absmin() const;

        T absmax() const;

        T trace() const;

        template <typename U>
        MatrixCsr<U> castTo() const;

        template <typename E>
        MatrixCsr &operator=(const MatrixExpression<T, E> &other);

        //! \brief I think the function below is same as above.
        MatrixCsr &operator=(const MatrixCsr &other);

        MatrixCsr &operator=(const MatrixCsr &&other);

        MatrixCsr &operator+=(T s);

        MatrixCsr &operator+=(const MatrixCsr &m);

        MatrixCsr &operator-=(T s);

        MatrixCsr &operator-=(const MatrixCsr &m);

        MatrixCsr &operator*=(T s);

        template <typename ME>
        MatrixCsr &operator*=(const MatrixExpression<T, ME> &m);

        MatrixCsr &operator/=(T s);

        T operator()(std::size_t i, std::size_t j) const;

        bool operator==(const MatrixCsr &m) const;

        bool operator!=(const MatrixCsr &other) const;

        static MatrixCsr<T> makeIdentity();

    private:
        big::Size2 _size;
        NonZeroContainterType _nonZeros;
        IndexContainterType _colIndex;
        IndexContainterType _rowPtr;

        std::size_t hasElement(std::size_t i, std::size_t j) const;

        template <typename Op>
        MatrixCsr binaryOp(const MatrixCsr &m, Op op) const;
    };

    typedef MatrixCsr<float> MatrixCsrF;

    typedef MatrixCsr<double> MatrixCsrD;
}
#include "detail/matrix_csr-inl.h"
#endif