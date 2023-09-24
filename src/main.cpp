#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array3.h>
#include <vector_expression.h>
#include "vector.h"




int main(int argc, char **argv)
{

    big::Vector<float, 4> aaa(1.1, 2.1, 3.1, 4.1);

    big::Vector<float, 4> bbb(1, 2, 3, 4);

    float tmp=10;
    auto ddd = aaa + bbb;
    // // aaa.set(bbb);
    big::ScalarType<int> aa; 
    // auto ccc = aaa.castTo<int>();

    std::cout << ddd[0] << " " << ddd[3] << std::endl;

    return 0;
}
