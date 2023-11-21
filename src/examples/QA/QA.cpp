// #include <iostream>

// class A;

// A* aa;
// class A
// {

// public:
//     int temp = 1;

//     template <typename Call>
//     void func(Call call) const
//     {
//         call();
//     }

//     void fun2()const{
//         aa->temp=3;
//     }
//     void aaaa() {
//         aa=this;
//     }
//     // void set()
//     // {
//     //     func([this]()
//     //          { this->temp = 2; });
//     // }
//     // 通过使用 lambda表达式和全局变量将this指针存其来，
//     // 那么再使用另一个const就可以修改这个外面存好的this指针了。
//     void set2()
//     {
//         class B
//         {
//         public:
//             B(A *_this) {__this = _this; }
//             void operator()()
//             {
//                 __this->temp = 2;
//             }
//             A *__this;
//         };
//         B b(this);
//         func(b);
//     }
// };

// int main(int argc, char **argv)
// {
//     A abc;
//     // abc.set2();
//     abc.aaaa();
//     abc.fun2();
//     std::cout << abc.temp << std::endl;
//     return 0;
// }