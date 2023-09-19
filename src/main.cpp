#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array3.h>
#include <gtest/gtest.h>
#include <vector_expression.h>

// template<typename T>
// class A{
//     const T& operator()(){return static_cast<const T&>(*this);}
// };

// class B : public A<B> {
//     public:
//         B(const int &a, const int &b){}
//     void func(){std::cout<<"hhh"<<std::endl;}
// };
// template<typename T>
// B operator+(const A<T>& a, const A<T> &b)
// {
//     return B()
// }

int a[] = {1, 2, 3, 4, 5, 6};

int *begin = std::begin(a);
int *end = std::end(a);

bool func(int a, int b){return a < b;}

int main(int argc, char **argv)
{

    int *iter = std::max_element(begin, end, func);
    std::cout<<*iter<<std::endl;
    big::Array3<int> arr(3, 3, 3, 10);
    big::Array3<int> add(3, 3, 3, 9);

    int scal = 5;

    // TEST();
    return 0;
}