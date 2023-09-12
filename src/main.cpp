#include <array1.h>
#include <array_accessor.h>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

void fun(int a){
    std::cout<<a<<std::endl;
}

int main()
{
    big::Array1<int> aaa{1, 3, 4, 13};    

    big::ArrayAccessor1<int> acc(aaa.size(),aaa.data());

    acc.forEachIndex(fun);
    //acc.forEach([](int elem){std::cout<<elem<<std::endl;});
    
    return 0;
}