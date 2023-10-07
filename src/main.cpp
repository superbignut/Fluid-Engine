#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "matrix_csr.h"

int main(int argc, char **argv)
{
    std::vector<int> a = {1,2,3,4};

    std::vector<int>::iterator aaa = a.begin();

    std::cout<< *aaa << std::endl; 
    return 0;
}
