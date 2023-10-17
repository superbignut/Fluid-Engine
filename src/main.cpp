#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <type_traits>
#include "matrix_csr.h"

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

        auto task = new package_t(std::forward<TASK_T>(fcn)); // 封装成一个可调用对象, 可以通过getfuture获得结果
        auto future = task->get_future();

        schedule([=]() { // 值传递
            (*task)();   // 开始执行
            delete task; // 删除new的空间
        });
        return future;
    };
}
int main(int argc, char **argv)
{
    std::vector<std::future<void>> pool;
    for (int i = 0; i < 10; ++i)
    {
        pool.emplace_back(small::async([=]()
                                      { std::cout << i << " "; }));
    }
    for (auto &f : pool)
    {
        if (f.valid())
        {
            f.wait();
        }
    }

    // std::packaged_task<int(int, int)> task([](int a, int b)
    //                                        { return a + b; });
    // std::future<int> result = task.get_future();

    //     task(10, 10);

    // std::cout << result.get() << std::endl;
    // big::Matrix<float, 4, 4> m10(
    //     {{1, 0, 0, 0},
    //      {0, 3, 0, 0},
    //      {0, 0, 1, 0},
    //      {0, 0, 2, 1}});
    // // m10.setDiagonal(1.2);

    // big::MatrixCsr<float> m(m10);
    // std::cout << m.size().x << m.size().y << std::endl;
    // big::MatrixCsr<float> mm(
    //     {{0, 1, 0, 6},
    //      {0, 0, 10, 0},
    //      {8, 0, 9, 0},
    //      {0, 1, 1, 0}});

    // std::cout << mm.size().x << mm.size().y << std::endl;

    // auto ans = m.rsub(mm);
    // std::cout << ans.size().x << ans.size().y << std::endl;
    // ans.setElement(3, 9, 1.0f);
    // ans.show();
    return 0;
}
