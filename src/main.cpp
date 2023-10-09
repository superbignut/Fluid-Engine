#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "matrix_csr.h"

int main(int argc, char **argv)
{
    big::Matrix<float, 10, 10> m;
    m.setDiagonal(1);
    float eps = 0.0f;
    big::MatrixCsr<float> aaa(m, eps);
    //aaa.addElement(0,1, 10);
    // std::vector<int> vec{1};
    // auto iter = std::lower_bound(vec.begin(), vec.end(), 1);
    // std::cout << iter - vec.begin();
    if (aaa.isSimilar(m))
        std::cout <<"aa";
    // aaa.show();
    return 0;
}
