#ifndef BIG_PARALLEL_INL_H_
#define BIG_PARALLEL_INL_H_
#include <thread>
#include <vector>
#include <future>
#include <cmath>
#include <iostream>
#include "constants.h"
#include <memory>

namespace big
{
    namespace internal
    {
        template <typename TASK_T>
        inline void schedule(TASK_T &&fcn)
        {
            std::thread thread(std::forward<TASK_T>(fcn)); // run
            thread.detach();                               // detach
        }

        template <typename TASK_T>
        using operator_return_t = typename std::invoke_result<TASK_T>::type;

        // lambda use *value* capturedvariables[=](){} will ++ ptr.use_count()
        // otherwise, [&](){} will get std::shared_ptr<package_t> &task and ptr.use_count() is unchanged.
        //
        template <typename TASK_T>
        inline auto async(TASK_T &&fcn) -> std::future<operator_return_t<TASK_T>>
        {
            using package_t = std::packaged_task<operator_return_t<TASK_T>()>;

            auto task = std::make_shared<package_t>(std::forward<TASK_T>(fcn));
            auto future = task->get_future();
            // std::thread thread([task = task](){(*task)();});
            // thread.detach();
            schedule([task = task]()
                     {
                         (*task)(); // run()
                     });
            return future;
        }

        /// @brief A function used to perform the "merge" operation in merge sort.
        /// @tparam RandomIterator
        /// @tparam RandomIterator2
        /// @tparam CompareFunction
        /// @param a
        /// @param size 
        /// @param temp
        /// @param compareFunction
        template <typename RandomIterator, typename RandomIterator2, typename CompareFunction>
        void merge(RandomIterator a, std::size_t size,
                   RandomIterator2 temp, CompareFunction compareFunction)
        {
            std::size_t i1 = 0;
            std::size_t i2 = 0 + size / 2;
            std::size_t tempi = 0;

            while (i1 < size / 2 && i2 < size)
            {
                if (compareFunction(a[i1], a[i2]))
                {
                    temp[tempi] = a[i1];
                    i1++;
                }
                else
                {
                    temp[tempi] = a[i2];
                    i2++;
                }
                tempi++;
            }
            while (i1 < size / 2)
            {
                temp[tempi] = a[i1];
                i1++;
                tempi++;
            }
            while (i2 < size)
            {
                temp[tempi] = a[i2];
                i2++;
                tempi++;
            }
            parallelFor(kZeroSize, size, [&](std::size_t i)
                        { a[i] = temp[i]; });
        }
        
        /// For smaller arrays it may be not be worth using multithreading.
        template <typename RandomIterator, typename RandomIterator2, typename CompareFunction>
        void parallelMergeSort(RandomIterator a, std::size_t size, RandomIterator2 temp,
                               unsigned int numThreads,
                               CompareFunction compareFunction)
        {
            if(size == 1)
            {
                return;
            }
            else if (numThreads == 1)
            {
                std::sort(a, a + size, compareFunction);
            }
            else if (numThreads > 1)
            {
                std::vector<std::future<void>> pool;
                pool.reserve(2);
                // use [=](){} to ensure no race.
                auto launchRange = [compareFunction = compareFunction](RandomIterator begin, std::size_t k2,
                                                                       RandomIterator2 temp,
                                                                       unsigned int numThreads)
                {
                    parallelMergeSort(begin, k2, temp, numThreads, compareFunction);
                };

                pool.emplace_back(internal::async([=]()
                                                  { launchRange(a, size / 2, temp, numThreads / 2); }));
                pool.emplace_back(internal::async([=]()
                                                  { launchRange(a + size / 2, size - size / 2, temp + size / 2, numThreads - numThreads / 2); }));
                for(auto &f : pool)
                {
                    if(f.valid())
                    {
                        f.wait();
                    }
                }
                merge(a, size, temp, compareFunction);
            }
        }

    }

    template <typename RandomIterator, typename T>
    void parallelFill(const RandomIterator &begin, const RandomIterator &end,
                      const T &value, ExecutionPolicy policy)
    {
        if (begin >= end)
        {
            return;
        }
        auto diff = end - begin;
        std::size_t size = static_cast<std::size_t>(diff);
        parallelFor(
            kZeroSize, size, [&](std::size_t k)
            { begin[k] = value; },
            policy);
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
        // don't need to use [=](){}
        auto launchRange = [&func](IndexType k1, IndexType k2)
        {
            for (IndexType k = k1; k < k2; ++k)
            {
                func(k);
            }
        };

        // Creat pool and launch jobs
        std::vector<std::thread> pool;
        pool.reserve(numThreads); // does not change the size of the vector.because the pool may be not full.

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
        // don't need to use [=](){}
        auto launchRange = [&](IndexType k1, IndexType k2, unsigned int tid)
        {
            results[tid] = func(k1, k2, identity);
            // std::cout << results[tid]<<" ";
        };

        std::vector<std::future<void>> pool;
        pool.reserve(numThreads);

        IndexType i1 = begin;
        IndexType i2 = begin + slice; // begin + slice <= end

        unsigned int tid = 0;
        // Use [=](){} to ensure no race in asynchronous program.
        for (; tid < numThreads - 1 && i1 < end; ++tid)
        {
            pool.emplace_back(internal::async([=]()
                                              { launchRange(i1, i2, tid); }));
            i1 = i2;
            i2 = std::min(end, i2 + slice);
        }
        if (i1 < end)
        {
            pool.emplace_back(internal::async([=]()
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


    template<typename RandomIterator, typename CompareFunction>
    void parallelSort(RandomIterator begin, RandomIterator end,
                      CompareFunction compareFunction,
                      ExecutionPolicy policy)
    {
        if(begin >= end)
        {
            return;
        }
        std::size_t size = static_cast<std::size_t>(end - begin);

        typedef typename std::iterator_traits<RandomIterator>::value_type value_type;

        std::vector<value_type> temp(size);

        unsigned int numThreadsHint = std::thread::hardware_concurrency();
        const unsigned int numThreads =
            (policy == ExecutionPolicy::kParallel)
                ? (numThreadsHint == 0u ? 8u : numThreadsHint)
                : 1;
        internal::parallelMergeSort(begin, size, temp.begin(),numThreads,compareFunction);
        
    }

    template<typename RandomIterator>
    void parallelSort(RandomIterator begin, RandomIterator end,
                      ExecutionPolicy policy)
    {
        parallelSort(begin, end,
                     std::less<typename std::iterator_traits<RandomIterator>::value_type>(),
                     policy);
    }
}

#endif