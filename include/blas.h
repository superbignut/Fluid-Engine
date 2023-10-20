#ifndef INCLUDE_BIG_BLAS_H_
#define INCLUDE_BIG_BLAS_H_

namespace big
{
    //! Basic Linear Algebra Subprograms

    template <typename S, typename V, typename M>
    struct Blas
    {
        typedef S ScalarType;
        typedef V VectorType;
        typedef M MatrixType;

        static void set(ScalarType s, VectorType *result);

        static void set(const VectorType &v, VectorType *result);

        static void set(ScalarType s, MatrixType *result);

        static void set(const MatrixType m, MatrixType *result);

        static ScalarType dot(const VectorType &a, const VectorType &b);

        //! ax+y
        static void axpy(
            ScalarType a,
            const VectorType &x,
            const VectorType &y,
            VectorType *result);
        //! m*v
        static void mvm(
            const MatrixType &m,
            const VectorType &v,
            VectorType *result);
        //! b-a*x
        static void residual(
            const MatrixType &a,
            const VectorType &x,
            const VectorType &b,
            VectorType *result);

        static ScalarType l2Norm(const VectorType &v);

        static ScalarType lInfNorm(const VectorType &v);
    };

}

#include "detail/blas-inl.h"
#endif