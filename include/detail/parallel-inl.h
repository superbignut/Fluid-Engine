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
        if (begin > end)
        {
            return;
        }
        // Estimate number of threads in the pool.
        unsigned int numThreadsHint = std::thread::hardware_concurrency();
        const unsigned int numThreads =
            (policy == ExecutionPolicy::kParallel)
                ? (numThreadsHint == 0u ? 8u : numThreadsHint)
                : 1;
        IndexType n = end - begin + 1;
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
    }
}

#endif