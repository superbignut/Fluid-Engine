#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "vector.h"
#include "vector_expression.h"
#include "matrix_expression.h"
#include "matrix.h"

int main(int argc, char **argv)
{
    std::initializer_list<float> l1 = {1, 2};
    std::initializer_list<float> l2 = {3, 4};
    std::initializer_list<std::initializer_list<float>> ll = {l1, l2};

    big::Matrix<float, 2, 2> aaa(ll);

    std::cout << aaa(0, 0) << aaa(0, 1) << aaa(1, 0) << aaa(1, 1);
    return 0;
}
