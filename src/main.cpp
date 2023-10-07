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
    aaa.show();
    return 0;
}
