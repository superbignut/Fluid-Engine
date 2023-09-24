
#include <iostream>

template <typename T>
class A
{
public:
    void size() const
    {
        std::cout << "father\n";
        static_cast<const T &>(*this).size();   //这里不写引用会调用B的拷贝构造函数
        std::cout << static_cast<const T &>(*this).con << "\n"; //B的成员也都还在
    }
};
class B : public A<B>
{
public:
    void size() const
    {
        std::cout << "son\n";
    }
    int con = 10;
};
template <typename U>
void inter(const A<U> &other)
{
    other.size();
}
// int main(int argc, char **argv)
// {
//     B bbb;
//     inter(bbb);

//     return 0;
// }