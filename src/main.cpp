#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "vector.h"
#include "matrix.h"


int main(int argc, char **argv)
{

    std::initializer_list<float> l1 = {3, 1, 0};
    std::initializer_list<float> l2 = {2, 1, 1};
    std::initializer_list<float> l3 = {1, 0, 0};
    std::initializer_list<std::initializer_list<float>> ll = {l1, l2, l3};

    big::Matrix<float, 3, 3> aaa(ll);
    big::Matrix<float, 3, 3> bbb(1,2,3,4,5,6,7,8,9);

    std::cout << (bbb != aaa);

    // aaa.invert();

    std::cout<<aaa.determinant();


    //std::cout << aaa(0, 0) <<"&"<< aaa(0, 1)<<"&" << aaa(1, 0)<<"&"<<aaa(1,1)<<std::endl;
    // aaa.show();
    return 0;
}
