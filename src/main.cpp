#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array2.h>
#include <size2.h>
#include <point2.h>

void func(int a){
    std::cout << a << std::endl;
}

int main()
{   
    big::Array<int, 2> aaa(3, 2, 1);
    std::cout<< aaa(2, 3) << aaa.accessor().at(2,3)<<std::endl;
    aaa.forEach(func);
    
    return 0;
}