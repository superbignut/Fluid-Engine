#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <type_traits>
#include <future>
#include <memory>
//! small::async has the basical function as std::async
namespace small
{

    template <typename TASK_T>
    inline void schedule(TASK_T &&fcn)
    {
        std::thread thread(std::forward<TASK_T>(fcn)); // 执行线程
        thread.detach();                               // 与主线程分离
    }

    template <typename TASK_T>
    using operator_return_t = typename std::invoke_result<TASK_T>::type; // 返回可调用对象的 返回值类型

    template <typename TASK_T>
    inline auto async(TASK_T &&fcn) -> std::future<operator_return_t<TASK_T>>
    {
        using package_t = std::packaged_task<operator_return_t<TASK_T>()>; // () means no params

        auto task = std::make_shared<package_t>(std::forward<TASK_T>(fcn)); // 封装成一个可调用对象, 可以通过getfuture获得结果
        
        auto future = task->get_future();

        schedule([task = task]() { // 值传递
            (*task)();             // 开始执行
            // delete task;           // 删除new的空间
        });
        return future;
    };
}

// double MyFunction(int a, char b)
// {
//     std::cout<< 100 <<std::endl;
// }

// double MyFunction2(int a, char b)
// {
//     std::cout<< 200 <<std::endl;
// }

int main(int argc, char **argv)
{
    std::vector<std::future<void>> pool;
    for (int i = 0; i < 10; ++i)
    {
        pool.emplace_back(small::async([i = i]()
                                       { std::cout << i << " "; }));
        // without push_back :
        // auto fu = std::async([i=i, &logger](){std::cout << std::to_string(i);});
        // when temp loop finish, fu is going to destrut, but, if this async opetion does not finsh, program will block.
        // to prevent this, u need to store the std::async's return, which is a std::future object into a container.
    }
    for (auto &f : pool)
    {
        if (f.valid())
        {
            f.wait();
        }
    }
}