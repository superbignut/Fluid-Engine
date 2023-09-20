#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <array3.h>
#include <gtest/gtest.h>
#include <vector_expression.h>

int a[] = {1, 2, 3, 4, 5, 6, 7};
int *begin = std::begin(a);
int *end = std::end(a);

bool func(int &a, int &b)
{
    return a < b;
}

namespace big
{
    template <typename _Compare>
    struct _Iter_comp_iter
    {
        _Compare _M_comp;

        _Iter_comp_iter(_Compare __comp) : _M_comp(std::move(__comp)) {}

        template <typename _Iter1, typename _Iter2>
        bool operator()(_Iter1 __it1, _Iter2 __it2)
        {
            return bool(_M_comp(*__it1, *__it2));
        }
    };


    template <typename _Compare>
    _Iter_comp_iter<_Compare> _iter_comp_iter(_Compare __comp)
    {
        return _Iter_comp_iter<_Compare>(std::move(__comp));//为啥要move一下呢？？
    }


    template <typename _Iter, typename _Comp>
    _Iter __max_element(_Iter __first, _Iter __end, _Comp __comp)
    {
        if(__first == __end) return __first;
        _Iter __result = __first;
        while(++__first != __end)
            if (__comp(__result, __first))
                __result = __first;
        return __result;
    }

    template <typename _Iter, typename _Comp>
    _Iter max_element(_Iter __first, _Iter __end, _Comp __comp)
    {
        return __max_element(__first, __end, _iter_comp_iter(__comp));
    }
}

int main(int argc, char **argv)
{
    int * a = big::max_element(begin, end, func);
    std::cout << *a << std::endl;
    // big::Vector<int, 4> aaa(1,2,3,4);
    return 0;
}