#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "matrix_csr.h"

int main(int argc, char **argv)
{
    big::Matrix<float, 10, 10> m10;
    m10.setDiagonal(1.2);
    big::MatrixCsr<float> m(m10 + m10);
    //  big::MatrixCsr<float> m2(m);
    auto mm = m.add(1.0f);
    // if (m.hasElement(0, 0) != big::kMaxSize)
    //     std::cout << m.hasElement(0, 1) << "yes" << m.numberNonZeros();
    mm.show();
    m.show();
    // if(mm.size() == m.size())
    // {
    //     //auto ans = mm.add(m);
    // }
    return 0;
}
