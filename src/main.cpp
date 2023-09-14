#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array2.h>
#include <size2.h>


int main()
{
    big::Size2 sss(3,3);
    big::Array<int, 2> aaa;
    big::Array<int, 2> bbb(sss,0);
    std::initializer_list<int> lll1={1,2,3,4,5};
    std::initializer_list<int> lll2={3,2,1,0,-1};

    std::initializer_list<std::initializer_list<int> > lst;
    // std::cout << *(lll.begin()->end())<<std::endl;
    return 0;
}