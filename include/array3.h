#ifndef INCLUDE_BIG_ARRAY3_H_
#define INCLUDE_BIG_ARRAY3_H_

#include <array.h>
#include <array_accessor3.h>
#include <size3.h>
#include <iostream>
#include <vector>
#include <point3.h>
namespace big
{
  //! datas were stored in an array i + width * j =(i, j)
  //! weight is the inner size
  //! height is the outer size
  template <typename T>
  class Array<T, 3> final
  {
  public:
    typedef std::vector<T> ContainterType; // 容器类型

    typedef typename ContainterType::iterator Iterator; // 迭代器

    typedef typename ContainterType::const_iterator ConstIterator; // 常量迭代器

    Array();

    explicit Array(const Size3 &size, const T &initial_val = T()); // forbid a = 1

    Array(const std::initializer_list<std::initializer_list<std::initializer_list<T>>> &lst);

    Array(std::size_t width, std::size_t height, std::size_t depth, const T &initial_val = T());

    Array(const Array &other);

    Array(Array &&other);

    Iterator begin();

    ConstIterator begin() const;

    Iterator end();

    ConstIterator end() const;

    ArrayAccessor<T, 3> accessor();

    ConstArrayAccessor<T, 3> constAccessor() const;

    void swap(Array &other);

    //! resize the array with \p size and fill the new element with \p initial_val.
    void resize(const Size3 &size, const T &initial_val = T());

    void resize(std::size_t width, std::size_t height, std::size_t depth, const T &initial_val = T());

    void set(const T &value);

    void set(const std::initializer_list<std::initializer_list<std::initializer_list<T>>> &lst);

    void set(const Array &other);

    T &at(std::size_t i);

    const T &at(std::size_t i) const;

    T &at(std::size_t i, std::size_t j, std::size_t k);

    const T &at(std::size_t i, std::size_t j, std::size_t k) const;

    T &at(Point3UI &pt);

    const T &at(Point3UI &pt) const;

    void clear();

    Size3 size() const;

    std::size_t width() const;

    std::size_t height() const;

    std::size_t depth() const;

    T *data();

    const T *const data() const;


    // void append(const T &newVal);

    // void append(const Array &other);

    T &operator[](std::size_t i);

    const T &operator[](std::size_t i) const;

    T &operator()(std::size_t i, std::size_t j, std::size_t k);

    const T &operator()(std::size_t i, std::size_t j, std::size_t k) const;

    T &operator()(const Point3UI &pt);

    const T &operator()(const Point3UI &pt) const;

    Array &operator=(const Array &other); // copy

    Array &operator=(Array &&other); // move

    Array &operator=(const T &value);

    Array &operator=(const std::initializer_list<std::initializer_list<std::initializer_list<T> > > &lst);

    template <typename Callback>
    void forEach(Callback func) const;

    template <typename Callback>
    void forEachIndex(Callback func) const;

    explicit operator ArrayAccessor<T, 3>();

    explicit operator ConstArrayAccessor<T, 3>();

  private:
    ContainterType _data;
    Size3 _size;
  };

  template <typename T>
  using Array3 = Array<T, 3>;

} // namespace big

#include "detail/array3-inl.h"
#endif