template <typename _compare>
    struct _Iter_comp_iter
    {
        _compare _m_comp;

        _Iter_comp_iter(_compare __comp) : _m_comp(std::move(__comp)) {}

        template <typename _iter1, typename _iter2>
        bool operator()(_iter1 __it1, _iter2 __it2)
        {
            return bool(_m_comp(*__it1, *__it2));
        }
    };

    template <typename _Compare>
    _Iter_comp_iter<_Compare> _iter_comp_iter(_Compare __comp)
    {
        return _Iter_comp_iter<_Compare>(std::move(__comp)); // 为啥要move一下呢？？
    }

    template <typename _iter, typename _comp>
    _iter _max_element(_iter __first, _iter __end, _comp __comp)
    {
        if (__first == __end)
            return __first;
        _iter __result = __first;
        while (++__first != __end)
            if (__comp(__result, __first))
                __result = __first;
        return __result;
    }

    template <typename _Iter, typename _Comp>
    _Iter max_element(_Iter __first, _Iter __end, _Comp __comp)
    {
        return __max_element(__first, __end, _iter_comp_iter(__comp));
    }