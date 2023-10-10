#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

#include "matrix_csr.h"

int main(int argc, char **argv)
{
    unsigned int numThreadsHint = std::thread::hardware_concurrency();
    std::cout << numThreadsHint<<std::endl;
    return 0;
}
