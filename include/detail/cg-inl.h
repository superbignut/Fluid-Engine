#ifndef INCLUDE_BIG_CG_INL_H_
#define INCLUDE_BIG_CG_INL_H_

namespace big
{
    template <typename BlasType>
    void cg(
        const typename BlasType::MatrixType &A,
        const typename BlasType::VectorType &b,
        unsigned int maxNumberOfIterations,
        typename BlasType::ScalarType tolerance,
        typename BlasType::VectorType *x,
        typename BlasType::VectorType *r,
        typename BlasType::VectorType *p,
        typename BlasType::VectorType *q,
        typename BlasType::VectorType *s,
        unsigned int *lastNumberOfIterations,
        typename BlasType::ScalarType *lastResidualNorm)
    {
        // BlasType::set(0, r); // r = 0

        BlasType::residual(A, *x, b, r); // r = A * x - b

        *p = -*r;

        typename BlasType::ScalarType rr = BlasType::dot(*r, *r);

        unsigned int k = 0;

        while (rr > tolerance && k <= maxNumberOfIterations)
        {
            BlasType::mvm(A, *p, q); // q = A * p

            typename BlasType::ScalarType alpha = rr / BlasType::dot(*p, *q);

            BlasType::axpy(alpha, *p, *x, x); // x = x + alpha * p

            BlasType::axpy(alpha, *q, *r, r); // r = r + alpha * q   where q = A * p

            typename BlasType::ScalarType old_rr = rr;

            rr = BlasType::dot(*r, *r);

            typename BlasType::ScalarType beta = rr / old_rr; // beta = rr / rr

            BlasType::axpy(beta, *p, -*r, p); // p = beta * p - r

            ++k;

            std::cout << "rr is :" << rr << std::endl;
        }
        *lastNumberOfIterations = k;
        *lastResidualNorm = rr;
    }
}
#endif