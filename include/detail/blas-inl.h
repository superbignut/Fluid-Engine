#ifndef INCLUDE_BIG_BLAS_INL_H_
#define INCLUDE_BIG_BLAS_INL_H_

namespace big
{

    template <typename ScalarType, typename VectorType, typename MatrixType>
    void Blas<ScalarType, VectorType, MatrixType>::set(
        ScalarType s, VectorType *result)
    {
        result->set(s);
    }

}

#endif