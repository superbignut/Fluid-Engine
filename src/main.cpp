#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "matrix2x2.h"

int main(int argc, char **argv)
{
    int max[10] = {10,2,3,4};
    big::Matrix<float, 2, 2> aaa(1,2,3,4);
    float a = 1.0f;
    aaa += a;
    auto bbb = aaa + a;
    bbb.show();
    auto ccc = bbb.inverse();
    ccc.show();
    std::cout << *max;
    return 0;
}
