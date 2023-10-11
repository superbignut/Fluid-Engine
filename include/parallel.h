#ifndef BIG_PARALLEL_H_
#define BIG_PARALLEL_H_
namespace big
{

    enum class ExecutionPolicy
    {
        kSerial,
        kParallel
    };

    template <typename RandomIterator, typename T>
    void parallelFill(const RandomIterator &begin, const RandomIterator &end,
                      const T &value,
                      ExecutionPolicy policy = ExecutionPolicy::kParallel);

    //! parallel func in [begin, end) if policy == kParallel
    template <typename IndexType, typename Function>
    void parallelFor(IndexType begin, IndexType end,
                     const Function &func,
                     ExecutionPolicy policy = ExecutionPolicy::kParallel);

}

#include "detail/parallel-inl.h"
#endif