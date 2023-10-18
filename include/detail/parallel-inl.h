#ifndef BIG_PARALLEL_INL_H_
#define BIG_PARALLEL_INL_H_
#include <thread>
#include <vector>
#include <future>
namespace big
{
    namespace internal
    {
        template <typename TASK_T>
        inline void schedule(TASK_T &&fcn)
        {
            std::thread thread(std::forward<TASK_T>(fcn)); // 执行线程
            thread.detach(); // 与主线程分离
        }

        template <typename TASK_T>
        using operator_return_t = typename std::invoke_result<TASK_T>::type; // 返回可调用对象的 返回值类型

        template <typename TASK_T>
        inline auto async(TASK_T &&fcn) -> std::future<operator_return_t<TASK_T>>
        {
            using package_t = std::packaged_task<operator_return_t<TASK_T>()>; // () means no params

            auto task = new package_t(std::forward<TASK_T>(fcn)); // 封装成一个可调用对象, 可以通过getfuture获得结果
            auto future = task->get_future();
            // add std::move(task)?
            schedule([task=task]() 
                     { //值传递 
                (*task)(); // 开始执行
                delete task; // 删除new的空间
                });
            return future;
        }

    }

    template <typename RandomIterator, typename T>
    void parallelFill(const RandomIterator &begin, const RandomIterator &end,
                      const T &value, ExecutionPolicy policy)
    {
    }

    template <typename IndexType, typename Function>
    void parallelFor(IndexType begin, IndexType end,
                     const Function &func,
                     ExecutionPolicy policy)
    {
        if (begin >= end)
        {
            return;
        }
        // Estimate number of threads in the pool.
        unsigned int numThreadsHint = std::thread::hardware_concurrency();
        const unsigned int numThreads =
            (policy == ExecutionPolicy::kParallel)
                ? (numThreadsHint == 0u ? 8u : numThreadsHint)
                : 1;
        IndexType n = end - begin;
        IndexType slice =
            (IndexType)std::round(n / static_cast<double>(numThreads));
        slice = std::max(slice, IndexType(1));

        auto launchRange = [&func](IndexType k1, IndexType k2)
        {
            for (IndexType k = k1; k < k2; ++k)
            {
                func(k);
                std::cout << k << " ";
            }
        };

        // Creat pool and launch jobs
        std::vector<std::thread> pool;
        pool.reserve(numThreads);

        IndexType i1 = begin;
        IndexType i2 = begin + slice; // begin + slice <= end

        for (unsigned int i = 0; i < numThreads - 1 && i1 < end; ++i) // last thread cover all data remain.
        {
            pool.emplace_back(launchRange, i1, i2);
            i1 = i2;
            i2 = std::min(end, i2 + slice); // Ensure i2 is always less_equal than end, also i1 for i1 = i2.
        }
        if (i1 < end)
        {
            pool.emplace_back(launchRange, i1, end);
        }

        for (std::thread &t : pool)
        {
            if (t.joinable())
            {
                t.join(); // wait for finish.
            }
        }
    }

    template <typename IndexType, typename Value, typename Function, typename Reduce>
    Value parallelReduce(IndexType begin, IndexType end,
                         const Value &identity, const Function &func,
                         const Reduce &reduce,
                         ExecutionPolicy policy)
    {
        if (begin >= end)
        {
            return identity;
        }
        unsigned int numThreadsHint = std::thread::hardware_concurrency();
        const unsigned int numThreads =
            (policy == ExecutionPolicy::kParallel)
                ? (numThreadsHint == 0u ? 8u : numThreadsHint)
                : 1;
        IndexType n = end - begin;
        IndexType slice =
            (IndexType)std::round(n / static_cast<double>(numThreads));
        slice = std::max(slice, IndexType(1));

        std::vector<Value> results(numThreads, identity);
        auto launchRange = [&func, &results, &identity](IndexType k1, IndexType k2, unsigned int tid)
        {
            results[tid] = func(k1, k2, identity);
            // std::cout << results[tid]<<" ";
        };

        std::vector<std::future<void>> pool;
        pool.reserve(numThreads);

        IndexType i1 = begin;
        IndexType i2 = begin + slice; // begin + slice <= end

        unsigned int tid = 0;
        for (; tid < numThreads - 1 && i1 < end; ++tid)
        {
            pool.emplace_back(internal::async([i1, i2, tid, &launchRange]()
                                              { launchRange(i1, i2, tid); }));
            i1 = i2;
            i2 = std::min(end, i2 + slice);
        }
        if (i1 < end)
        {
            pool.emplace_back(internal::async([i1, end, tid, &launchRange]()
                                              { launchRange(i1, end, tid); }));
        }
        for (auto &f : pool)
        {
            if (f.valid())
            {
                f.wait();
            }
        }
        Value finalResult = identity;
        for (const Value &val : results)
        {
            finalResult = reduce(val, finalResult);
        }
        return finalResult;
    }
}

#endif