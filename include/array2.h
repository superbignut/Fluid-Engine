#ifndef INCLUDE_BIG_ARRAY2_H_
#define INCLUDE_BIG_ARRAY2_H_

#include <array.h>
#include <array_accessor2.h>
#include <size2.h>
#include <iostream>
#include <vector>
namespace big
{
  //! datas were stored in an array i + width * j =(i, j)
  //! weight is the inner size
  //! height is the outer size
  template <typename T>
  class Array<T, 2> final
  {
  public:
    typedef std::vector<T> ContainterType; // 容器类型

    typedef typename ContainterType::iterator Iterator; // 迭代器

    typedef typename ContainterType::const_iterator ConstIterator; // 常量迭代器

    Array();

    explicit Array(const Size2 &size, const T &initial_val = T()); // forbid a = 1

    Array(const std::initializer_list<std::initializer_list<T>> &lst);

    Array(std::size_t width, std::size_t height, const T &initial_val = T());

    Array(const Array &other);

    Array(Array &&other);

    Iterator begin();

    ConstIterator begin() const;

    Iterator end();

    ConstIterator end() const;

    // ArrayAccessor<T, 1> accessor();

    // ConstArrayAccessor<T, 1> constAccessor() const;

    void swap(Array &other);

    Size2 size() const;

    //! resize the array with \p size and fill the new element with \p initial_val.
    void resize(const Size2 &size, const T &initial_val = T());

    void resize(std::size_t width, std::size_t height, const T &initial_val = T());

    void set(const T &value);

    void set(const std::initializer_list<std::initializer_list<T>> &lst);

    void set(const Array &other);

    T &at(std::size_t i);

    const T &at(std::size_t i) const;

    T &at(std::size_t i, std::size_t j);

    const T &at(std::size_t i, std::size_t j) const;

    void clear();

    std::size_t width() const;

    std::size_t height() const;

    T *data();

    const T *const data() const;

    // void swap(Array &newVal);

    // void append(const T &newVal);

    // void append(const Array &other);

    T &operator[](std::size_t i);

    const T &operator[](std::size_t i) const;

    T &operator()(std::size_t i, std::size_t j);

    const T &operator()(std::size_t i, std::size_t j) const;

    Array &operator=(const Array &other); // copy

    Array &operator=(Array &&other); // move

    Array &operator=(const T &value);

    Array &operator=(const std::initializer_list<std::initializer_list<T> > &lst);

    // template <typename Callback>
    // void forEach(Callback func) const;

    // template <typename Callback>
    // void forEachIndex(Callback func) const;

    // explicit operator ArrayAccessor<T, 2>();

    // explicit operator ConstArrayAccessor<T, 2>();

  private:
    ContainterType _data;
    Size2 _size;
  };

  template <typename T>
  using Array2 = Array<T, 2>;

} // namespace big

#include "detail/array2-inl.h"
#endif