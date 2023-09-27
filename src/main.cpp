#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array3.h>
#include <vector_expression.h>
#include "vector2.h"



int main(int argc, char **argv)
{

    big::Vector<float, 2> aaa(1.0, 1.0);
    big::Vector<float, 2> normal(0,1);
    auto refl = aaa.reflect(normal);


    std::cout << refl.at(0)<<refl.at(1)<<std::endl;
    return 0;
}
