#include <iostream>
#include "blas.h"
#include "matrix.h"
#include "vector.h"




int main(){

    auto m = big::Matrix<float, 5, 5>::random();
    
    auto v = big::Vector<float, 5>::random();

    m.show();

    v.show();

    std::cout <<"successfully compiles!!";
    return 0;
}