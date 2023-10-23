#ifndef INCLUDE_BIG_CG_H_
#define INCLUDE_BIG_CG_H_
#include "blas.h"

namespace big{


template <typename BlasType>
struct NullCgPreconditioner final{

    void build(const typename BlasType::MatrixType& other){}

    void solve(
        const typename BlasType::VectorType& b,
        typename BlasType::VectorType* x){
            BlasType::set(b, x); // x = b
        }
};


//! r = b - A * x
//! q = A * p
//! 
template <typename BlasType>
void cg(
    const typename BlasType::MatrixType & A,
    const typename BlasType::VectorType & b,
    unsigned int maxNumberOfIterations,
    typename BlasType::ScalarType tolerance,
    typename BlasType::VectorType* x,
    typename BlasType::VectorType* r,
    typename BlasType::VectorType* p,
    typename BlasType::VectorType* q,
    typename BlasType::VectorType* s,
    unsigned int * lastNumberOfIterations,
    typename BlasType::ScalarType* lastResidualNorm);

template <typename BlasType, typename PrecondType>
void pcg(
    const typename BlasType::MatrixType & A,
    const typename BlasType::VectorType & b,
    unsigned int maxNumberOfIterations,
    double tolerance,
    PrecondType* M,
    typename BlasType::VectorType* x,
    typename BlasType::VectorType* r,
    typename BlasType::VectorType* d,
    typename BlasType::VectorType* q,
    typename BlasType::VectorType* s,
    unsigned int * lastNumberOfIterations,
    double* lastResidualNorm);

}




#include "detail/cg-inl.h"
#endif