#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "matrix_csr.h"

int main(int argc, char **argv)
{
    big::Matrix<float, 4, 4> m10(
        {{1, 0, 0, 0},
         {0, 3, 0, 0},
         {0, 0, 1, 0},
         {0, 0, 2, 1}});
    // m10.setDiagonal(1.2);

    big::MatrixCsr<float> m(m10);
    std::cout << m.size().x << m.size().y << std::endl;
    big::MatrixCsr<float> mm(
        {{0, 1, 0, 6},
         {0, 0, 10, 0},
         {8, 0, 9, 0},
         {0, 1, 1, 0}});

    std::cout << mm.size().x << mm.size().y << std::endl;

    auto ans = m.add(mm);
    std::cout << ans.size().x << ans.size().y << std::endl;
    ans.setElement(3, 9, 1.0f);
    ans.show();
    return 0;
}
