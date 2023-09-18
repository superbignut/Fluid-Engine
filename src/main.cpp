#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array3.h>
#include <gtest/gtest.h>

int main(int argc, char** argv)
{   


    std::initializer_list<int> lst = {1,2,3};

    for(auto & ele : lst)
    {
        std::cout<< ele <<std::endl;
    }
    //TEST();
    return 0;
}