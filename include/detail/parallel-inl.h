#ifndef BIG_PARALLEL_INL_H_
#define BIG_PARALLEL_INL_H_
#include <thread>
#include <vector>
namespace big
{

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
            }
        };

        // Creat pool and launch jobs
        std::vector<std::thread> pool;
        pool.reserve(numThreads);

        IndexType i1 = begin;
        IndexType i2 = begin + slice; //begin + slice <= end
        
        for (unsigned int i = 0; i < numThreads - 1 && i1 < end; ++i) // last thread cover all data remain.
        {
            pool.emplace_back(launchRange, i1, i2);
            i1 = i2;
            i2 = std::min(end, i2 + slice); //Ensure i2 is always less_equal than end, also i1 for i1 = i2.
        }
        if(i1 < end)
        {
            pool.emplace_back(launchRange, i1, end);
        }
        
        for(std::thread &t : pool)
        {
            if(t.joinable())
            {
                t.join();// wait for finish.
            }
        }
        
    }
}

#endif