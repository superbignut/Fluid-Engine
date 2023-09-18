#ifndef INCLUDE_BIG_ARRAY_ACCESOR3_INL_H_
#define INCLUDE_BIG_ARRAY_ACCESOR3_INL_H_

#include <cstddef> //size_t
#include <cassert> //assert
#include <iostream>
namespace big
{
    // template <typename T>
    // ArrayAccessor<T, 3>::ArrayAccessor() : _size(0,0), _data(nullptr) {}

    template <typename T>
    ArrayAccessor<T, 3>::ArrayAccessor(Size3 size, T *const data) : _size(size), _data(data) // maybe more effective
    {
        // reset(size, data);
    }

    template <typename T>
    ArrayAccessor<T, 3>::ArrayAccessor(std::size_t width, std::size_t height, std::size_t depth, T *const data) : _size(width, height, depth), _data(data)
    {
        // reset(Size3(width, height), data);
    }

    template <typename T>
    ArrayAccessor<T, 3>::ArrayAccessor(const ArrayAccessor &other) : _size(other._size), _data(other._data)
    {
        // reset(other._size, other._data);
    }

    template <typename T>
    void ArrayAccessor<T, 3>::reset(Size3 size, T *const data)
    {
        _size = size;
        _data = data;
    }

    template <typename T>
    void ArrayAccessor<T, 3>::reset(std::size_t width, std::size_t height, std::size_t depth, T *const data)
    {
        _size = Size3(width, height, depth);
        _data = data;
    }
    template <typename T>
    Size3 ArrayAccessor<T, 3>::size() const
    {
        return _size;
    }

    template <typename T>
    void ArrayAccessor<T, 3>::set(const ArrayAccessor &other)
    {
        reset(other._size, other._data);
    }

    template <typename T>
    T &ArrayAccessor<T, 3>::at(std::size_t i)
    {

        return _data[i];
    }

    template <typename T>
    const T &ArrayAccessor<T, 3>::at(std::size_t i) const
    {
        return _data[i];
    }

    template <typename T>
    T &ArrayAccessor<T, 3>::at(std::size_t i, std::size_t j, std::size_t k)
    {
        // return _data[i + j * _size.x + _size.x * _size.y * k];
        return _data[i + _size.x * (j + _size.y * k)]; // equals to the last line
    }

    template <typename T>
    const T &ArrayAccessor<T, 3>::at(std::size_t i, std::size_t j, std::size_t k) const
    {

        return _data[i + _size.x * (j + _size.y * k)];
    }

    template <typename T>
    T &ArrayAccessor<T, 3>::at(const Point3UI &pt)
    {
        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }

    template <typename T>
    const T &ArrayAccessor<T, 3>::at(const Point3UI &pt) const
    {
        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }

    template <typename T>
    T *ArrayAccessor<T, 3>::begin()
    {
        return _data;
    }

    template <typename T>
    T *ArrayAccessor<T, 3>::end()
    {
        return _data + _size.x * _size.y * _size.z;
    }

    template <typename T>
    const T *ArrayAccessor<T, 3>::begin() const
    {
        return _data;
    }

    template <typename T>
    const T *ArrayAccessor<T, 3>::end() const
    {
        return _data + _size.x * _size.y * _size.z;
    }

    template <typename T>
    T ArrayAccessor<T, 3>::width() const
    {
        return _size.x;
    }

    template <typename T>
    T ArrayAccessor<T, 3>::height() const
    {
        return _size.y;
    }

    template <typename T>
    T ArrayAccessor<T, 3>::depth() const
    {
        return _size.z;
    }

    template <typename T>
    T *const ArrayAccessor<T, 3>::data() const
    {
        return _data;
    }

    template <typename T>
    void ArrayAccessor<T, 3>::swap(ArrayAccessor &other)
    {
        std::swap(other._data, _data);
        std::swap(other._size, _size);
    }

    template <typename T>
    template <typename Callback>
    void ArrayAccessor<T, 3>::forEach(Callback func) const
    {
        for (std::size_t k = 0; k < depth(); ++k)
        {
            for (std::size_t j = 0; j < height(); ++j)
            {
                for (std::size_t i = 0; i < width(); ++i)
                {
                    func(at(i, j));
                }
            }
        }
    }

    template <typename T>
    template <typename Callback>
    void ArrayAccessor<T, 3>::forEachIndex(Callback func) const
    {
        for (std::size_t k = 0; k < depth(); ++k)
        {
            for (std::size_t j = 0; j < height(); ++j)
            {
                for (std::size_t i = 0; i < width(); ++i)
                {
                    func(i, j, k);
                }
            }
        }
    }

    template <typename T>
    std::size_t ArrayAccessor<T, 3>::index(std::size_t i, std::size_t j, std::size_t k) const
    {
        return i + _size.x * (j + _size.y * k);
    }

    template <typename T>
    std::size_t ArrayAccessor<T, 3>::index(const Point3UI &pt) const
    {
        return pt.x + _size.x * (pt.y + _size.y * pt.z);
    }

    template <typename T>
    T &ArrayAccessor<T, 3>::operator[](std::size_t i)
    {
        return _data[i];
    }

    template <typename T>
    const T &ArrayAccessor<T, 3>::operator[](std::size_t i) const
    {
        return _data[i];
    }

    template <typename T>
    T &ArrayAccessor<T, 3>::operator()(std::size_t i, std::size_t j)
    {
        return _data[i + j * _size.x];
    }

    template <typename T>
    const T &ArrayAccessor<T, 3>::operator()(std::size_t i, std::size_t j, std::size_t k) const
    {
        return _data[i + _size.x * (j + _size.y * k)];
    }

    template <typename T>
    T &ArrayAccessor<T, 3>::operator()(const Point3UI &pt)
    {
        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }

    template <typename T>
    const T &ArrayAccessor<T, 3>::operator()(const Point3UI &pt) const
    {
        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }
    template <typename T>
    ArrayAccessor<T, 3> &ArrayAccessor<T, 3>::operator=(const ArrayAccessor &other)
    {
        set(other);
        return *this;
    }

    template <typename T>
    ArrayAccessor<T, 3>::operator ConstArrayAccessor<T, 3>() const
    {
        return ConstArrayAccessor<T, 3>(*this);
    }

    template <typename T>
    ConstArrayAccessor<T, 3>::ConstArrayAccessor() : _size(0, 0, 0), _data(nullptr) {}

    template <typename T>
    ConstArrayAccessor<T, 3>::ConstArrayAccessor(const Size3 &size, const T *const data) : _size(size), _data(data)
    {
        // _size = size;
        // _data = data;
    }

    template <typename T>
    ConstArrayAccessor<T, 3>::ConstArrayAccessor(const ArrayAccessor<T, 3> &other) : _size(other._size), _data(other._data)
    {
        // _size = other._size;
        // _data = other._data;
    }

    template <typename T>
    ConstArrayAccessor<T, 3>::ConstArrayAccessor(const ConstArrayAccessor &other) : _size(other._size), _data(other._data)
    {
        // _size = other._size;
        // _data = other._data;
    }

    template <typename T>
    const T &ConstArrayAccessor<T, 3>::at(std::size_t i) const
    {
        return _data[i];
    }

    template <typename T>
    const T &ConstArrayAccessor<T, 3>::at(std::size_t i, std::size_t j, std::size_t k) const
    {
        return _data[i + _size.x * (j + _size.y * k)];
    }

    template <typename T>
    const T &ConstArrayAccessor<T, 3>::at(const Point3UI &pt) const
    {
        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }

    template <typename T>
    const T *ConstArrayAccessor<T, 3>::begin() const
    {
        return _data;
    }

    template <typename T>
    const T *ConstArrayAccessor<T, 3>::end() const
    {
        return _data + _size.x * _size.y;
    }

    template <typename T>
    Size3 ConstArrayAccessor<T, 3>::size() const
    {
        return _size;
    }

    template <typename T>
    std::size_t ConstArrayAccessor<T, 3>::width() const
    {
        return _size.x;
    }
    template <typename T>
    std::size_t ConstArrayAccessor<T, 3>::height() const
    {
        return _size.y;
    }
    template <typename T>
    std::size_t ConstArrayAccessor<T, 3>::depth() const
    {
        return _size.z;
    }

    template <typename T>
    const T *const ConstArrayAccessor<T, 3>::data() const
    {
        return _data;
    }

    template <typename T>
    template <typename Callback>
    void ConstArrayAccessor<T, 3>::forEach(Callback func) const
    {
        for (std::size_t k = 0; k < depth(); ++k)
        {
            for (std::size_t j = 0; j < height(); ++j)
            {
                for (std::size_t i = 0; i < width(); ++i)
                {
                    func(at(i, j, k));
                }
            }
        }
    }

    template <typename T>
    template <typename Callback>
    void ConstArrayAccessor<T, 3>::forEachIndex(Callback func) const
    {
        for (std::size_t k = 0; k < depth(); ++k)
        {
            for (std::size_t j = 0; j < height(); ++j)
            {
                for (std::size_t i = 0; i < width(); ++i)
                {
                    func(i, j, k);
                }
            }
        }
    }

    template <typename T>
    std::size_t ConstArrayAccessor<T, 3>::index(std::size_t i, std::size_t j, std::size_t k) const
    {
        return i + _size.x * (j + _size.y * k);
    }

    template <typename T>
    std::size_t ConstArrayAccessor<T, 3>::index(const Point3UI &pt) const
    {
        return pt.x + _size.x * (pt.y + _size.y * pt.z);
    }

    template <typename T>
    const T &ConstArrayAccessor<T, 3>::operator[](std::size_t i) const
    {
        return _data[i];
    }
    template <typename T>
    const T &ConstArrayAccessor<T, 3>::operator()(std::size_t i, std::size_t j, std::size_t k) const
    {
        return _data[i + _size.x * (j + _size.y * k)];
    }
    template <typename T>
    const T &ConstArrayAccessor<T, 3>::operator()(const Point3UI &pt) const
    {
        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }

} // namespace big

#endif