#ifndef INCLUDE_BIG_ARRAY1_ACCESOR_INL_H_
#define INCLUDE_BIG_ARRAY1_ACCESOR_INL_H_
#include <cstddef> //size_t
#include <cassert> //assert
#include<iostream>
namespace big
{
    template <typename T>
    ArrayAccessor<T, 1>::ArrayAccessor() : _data(nullptr), _size(0) {}

    template <typename T>
    ArrayAccessor<T, 1>::ArrayAccessor(std::size_t size, T *const data)
    {
        reset(size, data);
    }

    template <typename T>
    ArrayAccessor<T, 1>::ArrayAccessor(const ArrayAccessor &other)
    {
        reset(other._size, other._data);
    }

    template <typename T>
    void ArrayAccessor<T, 1>::reset(std::size_t size, T *const data)
    {
        _size = size;
        _data = data;
    }
    template <typename T>
    std::size_t ArrayAccessor<T, 1>::size() const
    {
        return _size;
    }

    template <typename T>
    void ArrayAccessor<T, 1>::set(const ArrayAccessor &other)
    {
        reset(other._size, other._data);
    }

    template <typename T>
    T &ArrayAccessor<T, 1>::at(std::size_t i)
    {
        std::cout<<"normal at"<<std::endl;
        assert(i < _size);
        return _data[i];
    }

    template <typename T>
    const T &ArrayAccessor<T, 1>::at(std::size_t i) const
    {
        std::cout<<"const at"<<std::endl;
        assert(i < _size);
        return _data[i];
    }

    template <typename T>
    T *ArrayAccessor<T, 1>::begin()
    {
        return _data;
    }

    template <typename T>
    T *ArrayAccessor<T, 1>::end()
    {
        return _data + _size;
    }

    template <typename T>
    const T *ArrayAccessor<T, 1>::begin() const
    {
        return _data;
    }

    template <typename T>
    const T *ArrayAccessor<T, 1>::end() const
    {
        return _data + _size;
    }

    template <typename T>
    T *const ArrayAccessor<T, 1>::data() const
    {
        return _data;
    }

    template <typename T>
    void ArrayAccessor<T, 1>::swap(ArrayAccessor &other)
    {
        std::swap(other._data, _data);
        std::swap(other._size, _size);
    }

    template <typename T>
    template <typename Callback>
    void ArrayAccessor<T, 1>::forEach(Callback func) const
    {
        for (std::size_t i = 0; i < size(); ++i)
        {
            func(at(i));
        }
    }

    template <typename T>
    template <typename Callback>
    void ArrayAccessor<T, 1>::forEachIndex(Callback func) const
    {
        for (std::size_t i = 0; i < size(); ++i)
        {
            func(i);
        }
    }


} // namespace big

#endif