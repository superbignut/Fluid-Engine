#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "vector.h"

#include "matrix_expression.h"


int main(int argc, char **argv)
{
    // const int &a = 10;
    big::Vector<float, 5> aaa;
    auto ans = aaa + 3.0f;
    aaa[0] = 10;
    std::cout<<ans[0];
    return 0;
}
