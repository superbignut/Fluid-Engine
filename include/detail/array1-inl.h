#ifndef INCLUDE_BIG_ARRAY1_INL_H_
#define INCLUDE_BIG_ARRAY1_INL_H_

// #include "array1.h" //为啥他不用加这个
#include <vector>
#include <utility>
#include <cassert>
namespace big
{

    template <typename T>
    Array<T, 1>::Array() : _data() {} /*Array()*/  //default construct 

    template <typename T>
    Array<T, 1>::Array(std::size_t size, const T &initial_val) /*Array()*/
    {
        resize(size, initial_val);
    }

    template <typename T>
    Array<T, 1>::Array(const std::initializer_list<T> &lst) /*Array()*/
    {
        set(lst);
    }

    template <typename T>
    Array<T, 1>::Array(const Array &other) /*Array(Array &)*/
    {
        set(other);
    }

    template <typename T>
    Array<T, 1>::Array(Array &&other) /*Array(Array &&)*/
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
    Array<T, 1> &Array<T, 1>::operator=(const Array<T, 1> &other)
    {
        _data = other._data;
        return *this;
    }

    template <typename T>
    Array<T, 1> &Array<T, 1>::operator=(const T &value)
    {
        set(value);
        return *this;
    }

    template <typename T>
    Array<T, 1> &Array<T, 1>::operator=(const std::initializer_list<T> &lst)
    {
        set(lst);
        return *this;
    }
    template <typename T>
    typename Array<T, 1>::Iterator Array<T, 1>::begin()
    {
        // std::cout << "begin used" << std::endl;
        return _data.begin();
    }

    template <typename T>
    typename Array<T, 1>::ConstIterator Array<T, 1>::begin() const
    {
        // std::cout << "cbegin used" << std::endl;
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
    ArrayAccessor<T, 1> Array<T, 1>::accessor()
    {
        return ArrayAccessor<T, 1>(size(), data());
    }

    template <typename T>
    ConstArrayAccessor<T, 1> Array<T, 1>::constAccessor() const
    {
        return ConstArrayAccessor<T, 1>(size(), data());
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
        assert(i < size()); // 这里为什么不用static_assert
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
    T *Array<T, 1>::data()
    {
        return _data.data();
    }

    template <typename T>
    const T *const Array<T, 1>::data() const
    {
        return _data.data();
    }

    template <typename T>
    void Array<T, 1>::swap(Array &other)
    {
        std::swap(other._data, _data);
    }

    template <typename T>
    void Array<T, 1>::append(const T &newVal)
    {
        _data.push_back(newVal);
    }

    template <typename T>
    void Array<T, 1>::append(const Array &other)
    {
        _data.insert(_data.begin(), other._data.begin(), other._data.end());
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

    template <typename T>
    template <typename Callback>
    void Array<T, 1>::forEach(Callback func) const
    {
        constAccessor().forEach(func);
    }

    template <typename T>
    template <typename Callback>
    void Array<T, 1>::forEachIndex(Callback func) const
    {
        constAccessor().forEachIndex(func);
    }

    template <typename T>
    Array<T, 1>::operator ArrayAccessor<T, 1>()
    {
        return accessor();
    }

    template <typename T>
    Array<T, 1>::operator ConstArrayAccessor<T, 1>()
    {
        return constAccessor();
    }

}
#endif