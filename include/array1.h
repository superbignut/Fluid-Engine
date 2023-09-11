#ifndef INCLUDE_BIG_ARRAY1_H_
#define INCLUDE_BIG_ARRAY1_H_

#include <array.h>
#include <point.h>

#include <iostream>
#include <vector>
namespace big
{

  template <typename T>
  class Array<T, 1> final
  {
  public:
    typedef std::vector<T> ContainterType; // 容器类型

    typedef typename ContainterType::iterator Iterator; // 迭代器

    typedef typename ContainterType::const_iterator ConstIterator; // 常量迭代器

    Array();

    explicit Array(std::size_t size, const T &initial_val = T());

    Array(const std::initializer_list<T> &lst);

    Array(const Array &other);

    Array(Array &&other);

    Iterator begin();

    ConstIterator begin() const;

    Iterator end();

    ConstIterator end() const;

    std::size_t size() const;

    void resize(std::size_t size, const T &initial_val = T());

    void set(const T &value);

    void set(const std::initializer_list<T> &lst);

    void set(const Array &other);
    
    T &at(std::size_t i);

    const T &at(std::size_t i) const;

    

    // void test(void) const;

    //! Return the reference to ith value.
    T &operator[](std::size_t i);

    //! Return the const reference to ith value.
    const T &operator[](std::size_t i) const;

    Array &operator=(Array &&other);

  private:
    ContainterType _data;
  };

  template <typename T>
  using Array1 = Array<T, 1>;

} // namespace big

#include "detail/array1-inl.h"
#endif