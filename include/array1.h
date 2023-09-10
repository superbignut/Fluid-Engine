#ifndef INCLUDE_BIG_ARRAY1_H_
#define INCLUDE_BIG_ARRAY1_H_

#include <array.h>
#include <point.h>

#include <iostream>
#include <vector>
namespace big {

template <typename T> class Array<T, 1> final {
public:
  typedef std::vector<T> ContainterType;                         // 容器类型
  typedef typename ContainterType::iterator Iterator;            // 迭代器
  typedef typename ContainterType::const_iterator ConstIterator; // 常量迭代器

  Array() { std::cout << "default constrcut." << std::endl; };

  explicit Array(std::size_t size, const T &interval = T()) {
    std::cout << "interval constrcut." << std::endl;
  };

  Array(const std::initializer_list<T> &lst) {
    std::cout << "initializer_list constrcut." << std::endl;
  };

  Array(const Array &other) { std::cout << "copy constrcut." << std::endl; };

  Array(Array &&other) { std::cout << "move constrcut." << std::endl; };

  Iterator begin();

  ConstIterator begin() const;

  Iterator end();

  ConstIterator end() const;
};

} // namespace big

#endif