#ifndef INCLUDE_BIG_ARRAY1_INL_H_
#define INCLUDE_BIG_ARRAY1_INL_H_

// #include "array1.h" //为啥他不用加这个
#include <vector>
#include <utility>
#include <cassert>
namespace big
{

    template <typename T>
    Array<T, 1>::Array() {}

    template <typename T>
    Array<T, 1>::Array(std::size_t size, const T &initial_val)
    {
        resize(size, initial_val);
    }

    template <typename T>
    Array<T, 1>::Array(const std::initializer_list<T> &lst)
    {
        set(lst);
    }

    template <typename T>
    Array<T, 1>::Array(const Array &other)
    {
        set(other);
    }



    template <typename T>
    Array<T, 1>::Array(Array &&other) // move construct
    {
        (*this) = std::move(other); // call move assign func
    }

    template <typename T>
    Array<T, 1> &Array<T, 1>::operator=(Array &&other) // move assign
    {
        _data = std::move(other._data);
        return *this;
    }

    template <typename T>
    typename Array<T, 1>::Iterator Array<T, 1>::begin()
    {
        return _data.begin();
    }

    template <typename T>
    typename Array<T, 1>::ConstIterator Array<T, 1>::begin() const
    {
        return _data.cbegin();
    }

    template <typename T>
    typename Array<T, 1>::Iterator Array<T, 1>::end()
    {
        return _data.end();
    }

    template <typename T>
    typename Array<T, 1>::ConstIterator Array<T, 1>::end() const
    {
        return _data.cend();
    }

    template <typename T>
    std::size_t Array<T, 1>::size() const
    {
        return _data.size();
    }

    template <typename T>
    void Array<T, 1>::resize(std::size_t size, const T &initial_val)
    {
        _data.resize(size, initial_val);
    }

    template <typename T>
    T &Array<T, 1>::at(std::size_t i)
    {
        assert(i < size()); //这里为什么不用static_assert
        return _data[i];
    }

    template <typename T>
    const T &Array<T, 1>::at(std::size_t i) const
    {
        assert(i < size());
        return _data[i];
    }
    template <typename T>
    void Array<T, 1>::clear()
    {
        _data.clear();
    }

    template <typename T>
    void Array<T, 1>::set(const std::initializer_list<T> &lst)
    {
        std::size_t size = lst.size();
        resize(size);
        auto Iter = lst.begin();
        for (std::size_t i = 0; i < size; ++i)
        {
            (*this)[i] = *Iter;
            ++Iter;
        }
    }

    template <typename T>
    void Array<T, 1>::set(const T &value)
    {
        for (auto &v : _data)
        {
            v = value;
        }
    }

    template <typename T>
    void Array<T, 1>::set(const Array &other)
    {
        //_data = other._data;
        _data.resize(other.size());
        std::copy(other.begin(), other.end(), _data.begin());
    }

    template <typename T>
    T &Array<T, 1>::operator[](std::size_t i)
    {
        return _data[i];
    }

    template <typename T>
    const T &Array<T, 1>::operator[](std::size_t i) const
    {
        return _data[i];
    }
}
#endif