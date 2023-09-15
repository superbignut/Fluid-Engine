#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array2.h>
#include <size2.h>


int main()
{
    big::Size2 sss(3,3);
    big::Size2 sss2(1,10);
    big::Array<int, 2> aaa;
    const big::Array<int, 2> bbb(sss,0);
    std::initializer_list<int> lll1={1,2,3,4,5};
    std::initializer_list<int> lll2={3,3,2,1,-1};
    std::initializer_list<int> lll3={3,2,2,0,1};

    std::initializer_list<std::initializer_list<int> > lst = {lll1,lll2,lll3};

    big::Array<int ,2> ccc(lst);

    big::Array2<int> ddd(std::move(ccc));
     
    return 0;
}