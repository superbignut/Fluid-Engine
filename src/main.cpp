#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array3.h>
#include <gtest/gtest.h>

template <typename T>
class A
{
public:
    void interface()
    {
        static_cast<T *>(this)->implementation();
    }
};

class B : public A<B>
{
public:
    void implementation()
    {
        std::cout << "!!!" << std::endl;
    }
};

int main(int argc, char **argv)
{
    B bbb;
    bbb.interface();

    // TEST();
    return 0;
}