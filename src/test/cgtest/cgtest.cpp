#include <iostream>
#include "blas.h"
#include "matrix.h"
#include "vector.h"
#include "cg.h"
int main()
{

    auto A = big::Matrix<double, 10, 10>::random();

    auto x = big::Vector<double, 10>::random();

    auto b = big::Vector<double, 10>::random();

    auto r = big::Vector<double, 10>::random();

    auto d = big::Vector<double, 10>::random();

    auto q = big::Vector<double, 10>::random();

    auto s = big::Vector<double, 10>::random();


    unsigned int lastNum = 0;

    double lastReisudalNum = 0.0;


    if (A.determinant() != 0)
    {
        std::cout << "Matrix's rank is full: " << std::endl;

        big::Vector<double, 10> xx = A.inverse() * b;

        std::cout << "A^-1 * b is :" << std::endl;
        
        xx.show();
    }


    typedef big::Blas<double, big::Vector<double, 10>, big::Matrix<double, 10, 10>> BlasType;

    big::cg<BlasType>(A, b, 100, 0.001, &x, &r, &d, &q, &s, &lastNum, &lastReisudalNum);



    std::cout <<  "iter k is : " << lastNum << std::endl;

    std::cout <<  "lastReisudalNum is : " << lastReisudalNum << std::endl;

    x.show();
    r.show();
    return 0;
}