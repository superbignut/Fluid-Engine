#ifndef INCLUDE_BIG_POINT_INL_H_
#define INCLUDE_BIG_POINT_INL_H_
#include <cassert>
namespace big
{

    template <typename T, std::size_t N>
    Point<T, N>::Point()
    {
        for (auto &elem : _elements)
        {
            elem = static_cast<T>(0);
        }
    }

    template <typename T, std::size_t N>
    template <typename... Params>
    Point<T, N>::Point(Params... params)
    {
        // printf("this\n");
        static_assert(sizeof...(params) == N, "invalide number of paramters.");
        setAt(0, params...);
    }

    template <typename T, std::size_t N>
    template <typename U>
    Point<T, N>::Point(const std::initializer_list<U> &lst)
    {
        assert(lst.size() == N);
        std::size_t i = 0;
        for (const auto &elem : lst)
        {
            _elements[i] = static_cast<T>(elem);
        }
    }

    template <typename T, std::size_t N>
    Point<T, N>::Point(const Point &other) : _elements(other._elements)
    {
    }

    template <typename T, std::size_t N>
    template <typename U>
    void Point<T, N>::set(const std::initializer_list<U> &lst)
    {
        assert(lst.size() == N);
        std::size_t i = 0;
        for (const auto &elem : lst)
        {
            _elements[i] = static_cast<T>(elem);
        }
    }

    template <typename T, std::size_t N>
    void Point<T, N>::set(const Point &other)
    {
        _elements = other._elements;
    }

    template <typename T, std::size_t N>
    template <typename U>
    Point<T, N> &Point<T, N>::operator=(const std::initializer_list<U> &lst)
    {
        assert(lst.size() == N);
        std::size_t i = 0;
        for (const auto &elem : lst)
        {
            _elements[i] = static_cast<T>(elem);
        }
        return *this;
    }

    template <typename T, std::size_t N>
    Point<T, N> &Point<T, N>::operator=(const Point &other)
    {
        _elements = other._elements;
        return *this;
    }

    template <typename T, std::size_t N>
    T &Point<T, N>::operator[](std::size_t i)
    {
        return _elements[i];
    }

    template <typename T, std::size_t N>
    const T &Point<T, N>::operator[](std::size_t i) const
    {
        return _elements[i];
    }

    template <typename T, std::size_t N>
    template <typename... Params>
    void Point<T, N>::setAt(std::size_t i, T v, Params... params)
    {
        _elements[i] = v;
        setAt(i + 1, params...);
    }

    template <typename T, std::size_t N>
    void Point<T, N>::setAt(std::size_t i, T v)
    {
        _elements[i] = v;
    }
}

#endif