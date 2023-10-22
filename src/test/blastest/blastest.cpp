#include <iostream>
#include "blas.h"
#include "matrix.h"
#include "vector.h"

int main()
{

    auto m = big::Matrix<double, 5, 5>::random();

    auto v = big::Vector<double, 5>::random();

    typedef big::Blas<double, big::Vector<double, 5>, big::Matrix<double, 5, 5>> BlasType;

    BlasType::set(2.5, &v);

    BlasType::set(1.1, &m);

    // BlasType::set(v, &v);

    m.show();

    BlasType::axpy(2.0, v, v, &v);

    v.show();

    auto ans = BlasType::dot(v, v);

    auto vps = v + 3.0;

    BlasType::mvm(m, v, &v);

    std::cout << "successfully compiles!!" << ans;
    return 0;
}