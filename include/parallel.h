#ifndef BIG_PARALLEL_H_
#define BIG_PARALLEL_H_
namespace big
{

    enum class ExecutionPolicy
    {
        kSerial,
        kParallel
    };

    /// @brief Fill the container [begin, end).
    /// @tparam RandomIterator 
    /// @tparam T 
    /// @param begin The begin iterator of a container, which is different from the param in parallelFor and parallelReduce.
    /// @param end The end iterator of a container, which is different from the param in parallelFor and parallelReduce.
    /// @param value 
    /// @param policy 
    template <typename RandomIterator, typename T>
    void parallelFill(const RandomIterator &begin, const RandomIterator &end,
                      const T &value,
                      ExecutionPolicy policy = ExecutionPolicy::kParallel);

    /// @brief Split the [begin, end) into pieces, and ex the function each part.
    /// @tparam IndexType 
    /// @tparam Function 
    /// @param begin 
    /// @param end 
    /// @param func 
    /// @param policy 
    template <typename IndexType, typename Function>
    void parallelFor(IndexType begin, IndexType end,
                     const Function &func,
                     ExecutionPolicy policy = ExecutionPolicy::kParallel);

    /// @brief Split the [begin, end) into pieces, ex the function and reduce the function's return. 
    /// @tparam IndexType 
    /// @tparam Value 
    /// @tparam Function 
    /// @tparam Reduce 
    /// @param beginIndex 
    /// @param endIndex 
    /// @param identity 
    /// @param func Must have a return to reduce.
    /// @param reduce Such as std::plus<T>().
    /// @param policy 
    /// @return 
    template <typename IndexType, typename Value, typename Function, typename Reduce>
    Value parallelReduce(IndexType beginIndex, IndexType endIndex,
                         const Value& identity, const Function& func,
                         const Reduce& reduce,
                         ExecutionPolicy policy = ExecutionPolicy::kParallel);

    /// @brief Sorts a containter in parallel with a custom compare function.
    /// @tparam RandomIterator 
    /// @tparam CompareFunction 
    /// @param begin 
    /// @param end 
    /// @param compare 
    /// @param policy 
    template<typename RandomIterator, typename CompareFunction>
    void parallelSort(RandomIterator begin, RandomIterator end,
                      CompareFunction compareFunction,
                      ExecutionPolicy policy = ExecutionPolicy::kParallel);

    /// @brief Sorts a containter in parallel with a default compare function. std::less<T>()
    /// @tparam RandomIterator 
    /// @param begin 
    /// @param end 
    /// @param policy 
    template<typename RandomIterator>
    void parallelSort(RandomIterator begin, RandomIterator end,
                      ExecutionPolicy policy = ExecutionPolicy::kParallel);
}

#include "detail/parallel-inl.h"
#endif