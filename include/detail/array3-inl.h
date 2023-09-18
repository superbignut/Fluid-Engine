#ifndef INCLUDE_BIG_ARRAY3_INL_H_
#define INCLUDE_BIG_ARRAY3_INL_H_
#include <vector>
#include <utility>
#include <cassert>
namespace big
{

    template <typename T>
    Array<T, 3>::Array() : _data(), _size() {} /*Array()*/ // default construct

    template <typename T>
    Array<T, 3>::Array(const Size3 &size, const T &initial_val) /*Array()*/
    {
        resize(size, initial_val); // 这时_size.x 和 _size.y的值汉没有呢 resize里面咋用的？？？
    }

    template <typename T>
    Array<T, 3>::Array(const std::initializer_list<std::initializer_list<std::initializer_list<T>>> &lst) /*Array()*/
    {
        set(lst);
    }

    template <typename T>
    Array<T, 3>::Array(std::size_t width, std::size_t height, std::size_t depth, const T &initial_val)
    {
        resize(Size3(width, height, depth), initial_val);
    }

    template <typename T>
    void Array<T, 3>::set(const std::initializer_list<std::initializer_list<std::initializer_list<T>>> &lst)
    {
        std::size_t depth = lst.size(); // outer size

        std::size_t height = (depth != 0) ? lst.begin()->size() : 0; // can equals 0.

        std::size_t width = (height != 0) ? lst.begin()->begin()->size() : 0;

        resize(Size3(width, height, depth), T());

        auto depIter = lst.begin();
        for (std::size_t k = 0; k < depth; ++k)
        {
            auto rowIter = depIter->begin();
            assert(height == depIter->size() && "Error height size in iniitalizer_list."); // because each inner initialize_list can have diff size.
            for (std::size_t j = 0; j < height; ++j)
            {
                auto colIter = rowIter->begin();
                assert(width == rowIter->size() && "Error width size in iniitalizer_list."); // because each inner initialize_list can have diff size.
                for (std::size_t i = 0; i < width; ++i)
                {
                    (*this)(i, j, k) = *colIter;
                    ++colIter;
                }
                ++rowIter;
            }
            ++depIter;
        }
        // std::size_t height = size;
    }

    template <typename T>
    void Array<T, 3>::resize(const Size3 &size, const T &initial_val)
    {
        Array grid;
        grid._data.resize(size.x * size.y * size.z, initial_val);
        grid._size = size;
        std::size_t iMin = std::min(size.x, _size.x);
        std::size_t jMin = std::min(size.y, _size.y);
        std::size_t kMin = std::min(size.z, _size.z);
        for (std::size_t k = 0; k < kMin; ++k)
        {
            for (std::size_t j = 0; j < jMin; ++j)
            {
                for (std::size_t i = 0; i < iMin; ++i)
                {
                    grid(i, j, k) = at(i, j, k);
                }
            }
        }

        swap(grid);
    }

    template <typename T>
    void Array<T, 3>::swap(Array &other)
    {
        std::swap(other._data, _data);
        std::swap(other._size, _size);
    }

    template <typename T>
    Array<T, 3>::Array(const Array &other)
    {
        set(other);
    }

    template <typename T>
    void Array<T, 3>::set(const Array &other)
    {
        _data.resize(other._data.size());
        // resize(other.size());
        std::copy(other.begin(), other.end(), _data.begin());
        _size = other._size; // Size3's copy assign function
    }

    template <typename T>
    Array<T, 3>::Array(Array &&other) /*Array(Array &&)*/
    {
        (*this) = std::move(other); // call move assign func
    }

    template <typename T>
    Array<T, 3> &Array<T, 3>::operator=(Array &&other) // move assign
    {
        _data = std::move(other._data);
        _size = other._size;
        return *this;
    }

    template <typename T>
    Array<T, 3> &Array<T, 3>::operator=(const Array<T, 3> &other) // copy assign
    {
        set(other);
        return *this;
    }

    template <typename T>
    Array<T, 3> &Array<T, 3>::operator=(const T &value)
    {
        set(value);
        return *this;
    }

    template <typename T>
    Array<T, 3> &Array<T, 3>::operator=(const std::initializer_list<std::initializer_list<std::initializer_list<T>>> &lst)
    {
        set(lst);
        return *this;
    }

    template <typename T>
    typename Array<T, 3>::Iterator Array<T, 3>::begin()
    {
        // std::cout << "begin used" << std::endl;
        return _data.begin();
    }

    template <typename T>
    typename Array<T, 3>::ConstIterator Array<T, 3>::begin() const
    {
        // std::cout << "cbegin used" << std::endl;
        return _data.cbegin();
    }

    template <typename T>
    typename Array<T, 3>::Iterator Array<T, 3>::end()
    {
        return _data.end();
    }

    template <typename T>
    typename Array<T, 3>::ConstIterator Array<T, 3>::end() const
    {
        return _data.cend();
    }

    template <typename T>
    ArrayAccessor<T, 3> Array<T, 3>::accessor()
    {
        return ArrayAccessor<T, 3>(size(), data());
    }

    template <typename T>
    ConstArrayAccessor<T, 3> Array<T, 3>::constAccessor() const
    {
        return ConstArrayAccessor<T, 3>(size(), data());
    }

    template <typename T>
    void Array<T, 3>::resize(std::size_t width, std::size_t height, std::size_t depth, const T &initial_val)
    {
        resize(Size3(width, height, depth), initial_val);
    }

    template <typename T>
    T &Array<T, 3>::at(std::size_t i)
    {
        return _data[i];
    }

    template <typename T>
    const T &Array<T, 3>::at(std::size_t i) const
    {
        return _data[i];
    }

    template <typename T>
    T &Array<T, 3>::at(std::size_t i, std::size_t j, std::size_t k)
    {
        assert(i <= _size.x && j <= _size.y && k <= _size.z);
        return _data[i + _size.x * (j + _size.y * k)];
    }

    template <typename T>
    const T &Array<T, 3>::at(std::size_t i, std::size_t j, std::size_t k) const
    {
        assert(i <= _size.x && j <= _size.y && k <= _size.z);
        return _data[i + _size.x * (j + _size.y * k)];
    }

    template <typename T>
    T &Array<T, 3>::at(Point3UI &pt)
    {

        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }

    template <typename T>
    const T &Array<T, 3>::at(Point3UI &pt) const
    {
        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }

    template <typename T>
    void Array<T, 3>::clear()
    {
        _data.clear();
        _size.setZero();
    }

    template <typename T>
    Size3 Array<T, 3>::size() const
    {
        return _size;
    }

    template <typename T>
    std::size_t Array<T, 3>::width() const
    {
        return _size.x;
    }
    template <typename T>
    std::size_t Array<T, 3>::height() const
    {
        return _size.y;
    }
    template <typename T>
    std::size_t Array<T, 3>::depth() const
    {
        return _size.z;
    }
    template <typename T>
    T *Array<T, 3>::data()
    {
        return _data.data();
    }

    template <typename T>
    const T *const Array<T, 3>::data() const
    {
        return _data.data();
    }

    // template <typename T>
    // void Array<T, 3>::append(const T &newVal)
    // {
    //     _data.push_back(newVal);
    // }

    // template <typename T>
    // void Array<T, 3>::append(const Array &other)
    // {
    //     _data.insert(_data.begin(), other._data.begin(), other._data.end());
    // }

    template <typename T>
    void Array<T, 3>::set(const T &value)
    {
        for (auto &v : _data)
        {
            v = value;
        }
    }

    template <typename T>
    T &Array<T, 3>::operator[](std::size_t i)
    {
        return _data[i];
    }

    template <typename T>
    const T &Array<T, 3>::operator[](std::size_t i) const
    {
        return _data[i];
    }

    template <typename T>
    T &Array<T, 3>::operator()(std::size_t i, std::size_t j, std::size_t k)
    {
        assert(i <= _size.x && j <= _size.y && k <= _size.z);
        return _data[i + _size.x * (j + _size.y * k)];
    }

    template <typename T>
    const T &Array<T, 3>::operator()(std::size_t i, std::size_t j, std::size_t k) const
    {
        assert(i <= _size.x && j <= _size.y && k <= _size.z);
        return _data[i + _size.x * (j + _size.y * k)];
    }

    template <typename T>
    T &Array<T, 3>::operator()(const Point3UI &pt)
    {
        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }

    template <typename T>
    const T &Array<T, 3>::operator()(const Point3UI &pt) const
    {
        return _data[pt.x + _size.x * (pt.y + _size.y * pt.z)];
    }

    template <typename T>
    template <typename Callback>
    void Array<T, 3>::forEach(Callback func) const
    {
        constAccessor().forEach(func);
    }

    template <typename T>
    template <typename Callback>
    void Array<T, 3>::forEachIndex(Callback func) const
    {
        constAccessor().forEachIndex(func);
    }

    template <typename T>
    Array<T, 3>::operator ArrayAccessor<T, 3>()
    {
        return accessor();
    }

    template <typename T>
    Array<T, 3>::operator ConstArrayAccessor<T, 3>()
    {
        return constAccessor();
    }

}
#endif