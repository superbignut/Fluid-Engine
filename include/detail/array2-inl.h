#ifndef INCLUDE_BIG_ARRAY2_INL_H_
#define INCLUDE_BIG_ARRAY2_INL_H_
#include <vector>
#include <utility>
#include <cassert>
namespace big
{

    template <typename T>
    Array<T, 2>::Array() : _data(), _size() {} /*Array()*/ // default construct

    template <typename T>
    Array<T, 2>::Array(const Size2& size, const T &initial_val) /*Array()*/
    {
        resize(size, initial_val);//这时_size.x 和 _size.y的值汉没有呢 resize里面咋用的？？？
    }

    template <typename T>
    Array<T, 2>::Array(const std::initializer_list<std::initializer_list<T>> &lst) /*Array()*/
    {
        set(lst);
    }

    template <typename T>
    void Array<T, 2>::set(const std::initializer_list<std::initializer_list<T> > &lst)
    {
        std::size_t height = lst.size(); // outer size // can equals 0.

        std::size_t weight = (height != 0) ? lst->begin()->size() : 0;

        resize(Size2(weight, height), T());

        auto rowIter = lst.begin();
        for (std::size_t j = 0; j < height; ++j)
        {
            auto colIter = rowIter->begin();
            for (std::size_t i = 0; i < weight; ++i)
            {
                (*this)(i, j) = *colIter;
                ++colIter;
            }
            ++rowIter;
        }
        // std::size_t height = size;
    }

    //! change size with smallest change
    template <typename T>
    void Array<T, 2>::resize(const Size2 &size, const T &initial_val)
    {
        Array grid;
        grid._data.resize(size.x * size.y, initial_val);
        grid._size = size;
        std::size_t iMin = std::min(size.x, _size.x);
        std::size_t jMin = std::min(size.y, _size.y);

        for (std::size_t j = 0; j < jMin; ++j)
        {
            for (std::size_t i = 0; i < iMin; ++i)
            {
                grid(i, j) = at(i, j);
            }
        }
        swap(grid);
    }

    template <typename T>
    void Array<T, 2>::swap(Array &other)
    {
        std::swap(other._data, _data);
        std::swap(other._size, _size);
    }
    // template <typename T>
    // Array<T, 2>::Array(const Array &other) /*Array(Array &)*/
    // {
    //     set(other);
    // }

    // template <typename T>
    // Array<T, 2>::Array(Array &&other) /*Array(Array &&)*/
    // {
    //     (*this) = std::move(other); // call move assign func
    // }

    // template <typename T>
    // Array<T, 2> &Array<T, 2>::operator=(Array &&other) // move assign
    // {
    //     _data = std::move(other._data);
    //     return *this;
    // }

    // template <typename T>
    // Array<T, 2> &Array<T, 2>::operator=(const Array<T, 2> &other)
    // {
    //     _data = other._data;
    //     return *this;
    // }

    // template <typename T>
    // Array<T, 2> &Array<T, 2>::operator=(const T &value)
    // {
    //     set(value);
    //     return *this;
    // }

    // template <typename T>
    // Array<T, 2> &Array<T, 2>::operator=(const std::initializer_list<T> &lst)
    // {
    //     set(lst);
    //     return *this;
    // }
    // template <typename T>
    // typename Array<T, 2>::Iterator Array<T, 2>::begin()
    // {
    //     // std::cout << "begin used" << std::endl;
    //     return _data.begin();
    // }

    // template <typename T>
    // typename Array<T, 2>::ConstIterator Array<T, 2>::begin() const
    // {
    //     // std::cout << "cbegin used" << std::endl;
    //     return _data.cbegin();
    // }

    // template <typename T>
    // typename Array<T, 2>::Iterator Array<T, 2>::end()
    // {
    //     return _data.end();
    // }

    // template <typename T>
    // typename Array<T, 2>::ConstIterator Array<T, 2>::end() const
    // {
    //     return _data.cend();
    // }

    // template <typename T>
    // ArrayAccessor<T, 1> Array<T, 2>::accessor()
    // {
    //     return ArrayAccessor<T, 1>(size(), data());
    // }

    // template <typename T>
    // ConstArrayAccessor<T, 1> Array<T, 2>::constAccessor() const
    // {
    //     return ConstArrayAccessor<T, 1>(size(), data());
    // }

    // template <typename T>
    // std::size_t Array<T, 2>::size() const
    // {
    //     return _data.size();
    // }

    template <typename T>
    void Array<T, 2>::resize(std::size_t weight, std::size_t height, const T &initial_val)
    {
        resize(Size2(weight, height), initial_val);
    }

    template <typename T>
    T &Array<T, 2>::at(std::size_t i, std::size_t j)
    {

        return _data[i + j * _size.x];
    }

    template <typename T>
    const T &Array<T, 2>::at(std::size_t i, std::size_t j) const
    {
        return _data[i + j * _size.x];
    }
    // template <typename T>
    // void Array<T, 2>::clear()
    // {
    //     _data.clear();
    // }

    // template <typename T>
    // T *Array<T, 2>::data()
    // {
    //     return _data.data();
    // }

    // template <typename T>
    // const T *const Array<T, 2>::data() const
    // {
    //     return _data.data();
    // }

    // template <typename T>
    // void Array<T, 2>::swap(Array &other)
    // {
    //     std::swap(other._data, _data);
    // }

    // template <typename T>
    // void Array<T, 2>::append(const T &newVal)
    // {
    //     _data.push_back(newVal);
    // }

    // template <typename T>
    // void Array<T, 2>::append(const Array &other)
    // {
    //     _data.insert(_data.begin(), other._data.begin(), other._data.end());
    // }

    // template <typename T>
    // void Array<T, 2>::set(const T &value)
    // {
    //     for (auto &v : _data)
    //     {
    //         v = value;
    //     }
    // }

    // template <typename T>
    // void Array<T, 2>::set(const Array &other)
    // {
    //     //_data = other._data;
    //     _data.resize(other.size());
    //     std::copy(other.begin(), other.end(), _data.begin());
    // }

    // template <typename T>
    // T &Array<T, 2>::operator[](std::size_t i)
    // {
    //     return _data[i];
    // }

    // template <typename T>
    // const T &Array<T, 2>::operator[](std::size_t i) const
    // {
    //     return _data[i];
    // }

    template <typename T>
    T &Array<T, 2>::operator()(std::size_t i, std::size_t j)
    {
        return _data[i + _size.x * j];
    }

    template <typename T>
    const T &Array<T, 2>::operator()(std::size_t i, std::size_t j) const
    {
        return _data[i + _size.x * j];
    }
    // template <typename T>
    // template <typename Callback>
    // void Array<T, 2>::forEach(Callback func) const
    // {
    //     constAccessor().forEach(func);
    // }

    // template <typename T>
    // template <typename Callback>
    // void Array<T, 2>::forEachIndex(Callback func) const
    // {
    //     constAccessor().forEachIndex(func);
    // }

    // template <typename T>
    // Array<T, 2>::operator ArrayAccessor<T, 1>()
    // {
    //     return accessor();
    // }

    // template <typename T>
    // Array<T, 2>::operator ConstArrayAccessor<T, 1>()
    // {
    //     return constAccessor();
    // }

}
#endif