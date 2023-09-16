#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array2.h>
#include <size2.h>
#include <point2.h>
#include <array_accessor2.h>


int main()
{
    big::Array<int ,2> arr(2,2,10);
    big::ArrayAccessor<int, 2> acc(2, 2, arr.data());

    big::ArrayAccessor<int, 2> abb(acc);
    std::cout<< "finish!";
    int a = 10;
    int *p = &a;
    int * q(p); 
    std::cout<<*q;
    return 0;
}