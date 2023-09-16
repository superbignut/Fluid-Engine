#ifndef INCLUDE_BIG_ARRAY_ACCESOR2_INL_H_
#define INCLUDE_BIG_ARRAY_ACCESOR2_INL_H_

#include <cstddef> //size_t
#include <cassert> //assert
#include <iostream>
namespace big
{
    // template <typename T>
    // ArrayAccessor<T, 2>::ArrayAccessor() : _size(0,0), _data(nullptr) {}

    template <typename T>
    ArrayAccessor<T, 2>::ArrayAccessor(Size2 size, T *const data) : _size(size), _data(data) // maybe more effective
    {
        // reset(size, data);
    }

    template <typename T>
    ArrayAccessor<T, 2>::ArrayAccessor(std::size_t width, std::size_t height, T *const data) : _size(width, height), _data(data)
    {
        // reset(Size2(width, height), data);
    }

    template <typename T>
    ArrayAccessor<T, 2>::ArrayAccessor(const ArrayAccessor &other) : _size(other._size), _data(other._data)
    {
        // reset(other._size, other._data);
    }

    template <typename T>
    void ArrayAccessor<T, 2>::reset(Size2 size, T *const data)
    {
        _size = size;
        _data = data;
    }

    template <typename T>
    void ArrayAccessor<T, 2>::reset(std::size_t width, std::size_t height, T *const data)
    {
        _size = Size2(width, height);
        _data = data;
    }
    template <typename T>
    Size2 ArrayAccessor<T, 2>::size() const
    {
        return _size;
    }

    template <typename T>
    void ArrayAccessor<T, 2>::set(const ArrayAccessor &other)
    {
        reset(other._size, other._data);
    }

    template <typename T>
    T &ArrayAccessor<T, 2>::at(std::size_t i)
    {

        return _data[i];
    }

    template <typename T>
    const T &ArrayAccessor<T, 2>::at(std::size_t i) const
    {
        return _data[i];
    }

    template <typename T>
    T &ArrayAccessor<T, 2>::at(std::size_t i, std::size_t j)
    {
        return _data[i + j * _size.x];
    }

    template <typename T>
    const T &ArrayAccessor<T, 2>::at(std::size_t i, std::size_t j) const
    {

        return _data[i + j * _size.x];
    }

    template <typename T>
    T &ArrayAccessor<T, 2>::at(const Point2UI &pt)
    {
        return _data[pt.x + pt.y * _size.x];
    }

    template <typename T>
    const T &ArrayAccessor<T, 2>::at(const Point2UI &pt) const
    {
        return _data[pt.x + pt.y * _size.x];
    }

    template <typename T>
    T *ArrayAccessor<T, 2>::begin()
    {
        return _data;
    }

    template <typename T>
    T *ArrayAccessor<T, 2>::end()
    {
        return _data + _size.x * _size.y;
    }

    template <typename T>
    const T *ArrayAccessor<T, 2>::begin() const
    {
        return _data;
    }

    template <typename T>
    const T *ArrayAccessor<T, 2>::end() const
    {
        return _data + _size.x * _size.y;
    }

    template <typename T>
    T ArrayAccessor<T, 2>::width() const
    {
        return _size.x;
    }

    template <typename T>
    T ArrayAccessor<T, 2>::height() const
    {
        return _size.y;
    }
    template <typename T>
    T *const ArrayAccessor<T, 2>::data() const
    {
        return _data;
    }

    template <typename T>
    void ArrayAccessor<T, 2>::swap(ArrayAccessor &other)
    {
        std::swap(other._data, _data);
        std::swap(other._size, _size);
    }

    template <typename T>
    template <typename Callback>
    void ArrayAccessor<T, 2>::forEach(Callback func) const
    {

        for (std::size_t j = 0; j < height(); ++j)
        {
            for (std::size_t i = 0; i < width(); ++i)
            {
                func(at(i, j));
            }
        }
    }

    template <typename T>
    template <typename Callback>
    void ArrayAccessor<T, 2>::forEachIndex(Callback func) const
    {
        for (std::size_t j = 0; j < height(); ++j)
        {
            for (std::size_t i = 0; i < width(); ++i)
            {
                func(i, j);
            }
        }
    }

    template <typename T>
    std::size_t ArrayAccessor<T, 2>::index(std::size_t i, std::size_t j) const
    {
        return i + j * _size.x;
    }

    template <typename T>
    std::size_t ArrayAccessor<T, 2>::index(const Point2UI &pt) const
    {
        return pt.x + pt.y * _size.x;
    }

    template <typename T>
    T &ArrayAccessor<T, 2>::operator[](std::size_t i)
    {
        return _data[i];
    }

    template <typename T>
    const T &ArrayAccessor<T, 2>::operator[](std::size_t i) const
    {
        return _data[i];
    }

    template <typename T>
    T &ArrayAccessor<T, 2>::operator()(std::size_t i, std::size_t j)
    {
        return _data[i + j * _size.x];
    }

    template <typename T>
    const T &ArrayAccessor<T, 2>::operator()(std::size_t i, std::size_t j) const
    {
        return _data[i + j * _size.x];
    }    

    template <typename T>
    T &ArrayAccessor<T, 2>::operator()(const Point2UI &pt)
    {
        return _data[pt.x + pt.y * _size.x];
    }

    template <typename T>
    const T &ArrayAccessor<T, 2>::operator()(const Point2UI &pt) const
    {
        return _data[pt.x + pt.y * _size.x];
    } 
    template <typename T>
    ArrayAccessor<T, 2> &ArrayAccessor<T, 2>::operator=(const ArrayAccessor &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    ArrayAccessor<T, 2>::operator ConstArrayAccessor<T, 2>() const
    {
        return ConstArrayAccessor<T, 2>(*this);
    }

    template <typename T>
    ConstArrayAccessor<T, 2>::ConstArrayAccessor() : _size(0,0), _data(nullptr) {}

    template <typename T>
    ConstArrayAccessor<T, 2>::ConstArrayAccessor(const Size2 &size, const T *const data) : _size(size),_data(data)
    {
        // _size = size;
        // _data = data;
    }

    template <typename T>
    ConstArrayAccessor<T, 2>::ConstArrayAccessor(const ArrayAccessor<T, 2> &other) : _size(other._size), _data(other._data)
    {
        // _size = other._size;
        // _data = other._data;
    }

    template <typename T>
    ConstArrayAccessor<T, 2>::ConstArrayAccessor(const ConstArrayAccessor &other) : _size(other._size), _data(other._data)
    {
        // _size = other._size;
        // _data = other._data;
    }

    template <typename T>
    const T &ConstArrayAccessor<T, 2>::at(std::size_t i) const
    {
        return _data[i];
    }

    template <typename T>
    const T &ConstArrayAccessor<T, 2>::at(std::size_t i, std::size_t j) const
    {
        return _data[i + _size.x * j];
    }

    template <typename T>
    const T &ConstArrayAccessor<T, 2>::at(const Point2UI &pt) const
    {
        return _data[pt.x + _size.x * pt.y];
    }

    template <typename T>
    const T *ConstArrayAccessor<T, 2>::begin() const
    {
        return _data;
    }

    template <typename T>
    const T *ConstArrayAccessor<T, 2>::end() const
    {
        return _data + _size.x * _size.y;
    }

    template <typename T>
    Size2 ConstArrayAccessor<T, 2>::size() const
    {
        return _size;
    }

    template <typename T>
    std::size_t ConstArrayAccessor<T, 2>::width() const
    {
        return _size.x;
    }
    template <typename T>
    std::size_t ConstArrayAccessor<T, 2>::height() const
    {
        return _size.y;
    }

    template <typename T>
    const T *const ConstArrayAccessor<T, 2>::data() const
    {
        return _data;
    }

    template <typename T>
    template <typename Callback>
    void ConstArrayAccessor<T, 2>::forEach(Callback func) const
    {
        for (std::size_t j = 0; j < height(); ++j)
        {
            for (std::size_t i = 0; i < width(); ++i)
            {
                func(at(i, j));
            }
        }
    }

    template <typename T>
    template <typename Callback>
    void ConstArrayAccessor<T, 2>::forEachIndex(Callback func) const
    {
        for (std::size_t j = 0; j < height(); ++j)
        {
            for (std::size_t i = 0; i < width(); ++i)
            {
                func(i, j);
            }
        }
    }

    template <typename T>
    std::size_t ConstArrayAccessor<T, 2>::index(std::size_t i, std::size_t j) const
    {
        return i + j * _size.x;
    }

    template <typename T>
    std::size_t ConstArrayAccessor<T, 2>::index(const Point2UI &pt) const
    {
        return pt.x + pt.y * _size.x;
    }

    template <typename T>
    const T &ConstArrayAccessor<T, 2>::operator[](std::size_t i) const
    {
        return _data[i];
    }
    template <typename T>
    const T &ConstArrayAccessor<T, 2>::operator()(std::size_t i, std::size_t j) const
    {
        return _data[i + _size.x * j];
    }
    template <typename T>
    const T &ConstArrayAccessor<T, 2>::operator()(const Point2UI &pt) const
    {
        return _data[pt.x + _size.x * pt.y];
    }


} // namespace big

#endif