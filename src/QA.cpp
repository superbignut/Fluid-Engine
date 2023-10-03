// class A
// {

// public:
//     int temp = 1;

//     template <typename Call>
//     void func(Call call) const
//     {
//         call();
//     }

//     void set()
//     {
//         func([this](){ this->temp = 2; });
//     }


// };

// int main(int argc, char **argv)
// {
//     A abc;
//     abc.set();

//     return 0;

// }