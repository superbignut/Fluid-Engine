#ifndef INCLUDE_BIG_VECTOR_INL_H_
#define INCLUDE_BIG_VECTOR_INL_H_
#include <stddef.h>

namespace big
{

    template <typename T, std::size_t N>
    Vector<T, N>::Vector()
    {
        // for (auto &elem : _elements)
        // {
        //     elem = static_cast<T>(0);
        // }
        _elements.fill(0);
    }

    template <typename T, std::size_t N>
    template <typename... Params>
    Vector<T, N>::Vector(Params... params)
    {
        static_assert(sizeof...(params) == N, "Invalid number of params.");
        setAt(0, params);
    }

    template <typename T, std::size_t N>
    template <typename U>
    Vector<T, N>::Vector(std::initializer_list<U> &lst)
    {
        set(lst);
    }

    template <typename T, std::size_t N>
    template <typename U>
    void Vector<T, N>::set(std::initializer_list<U> &lst)
    {
        static_assert(lst.size() == N, "lst's size is Invalid.");
        std::size_t i = 0;

        for (const auto &ele : lst)
        {
            _elements[i] = static_cast<T>(ele);
            ++i;
        }
    }

    template <typename T, std::size_t N>
    void Vector<T, N>::set(const T &s)
    {
        _elements.fill(s);
    }

    template <typename T, std::size_t N>
    template <typename... Params>
    void Vector<T, N>::setAt(std::size_t i, T v, Params... params)
    {
        _elements[i] = v;
        setAt(i + 1, params);
    }

    template <typename T, std::size_t N>
    void Vector<T, N>::setAt(std::size_t i, T v)
    {
        _elements[i] = v;
    }

} // namespace big

#endif