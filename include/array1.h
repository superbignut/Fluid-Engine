#ifndef INCLUDE_BIG_ARRAY1_H
#define INCLUDE_BIG_ARRAY1_H

#include <array.h>
#include <point.h>

#include <vector>
namespace big {
//!
//! \brief This class represent the 1-D data structure;
//!
//! \param T - Real number type.
//! \param N - Dimension.
//!
template <typename T>
class Array<T, 1> final {
 public:
  typedef std::vector<T> ContainterType; // 容器类型
  typedef typename ContainterType::iterator Iterator; // 迭代器
  typedef typename ContainterType::const_iterator ConstIterator; // 常量迭代器

  //! construct
  Array();

  //! \brief 1-D array with given \p size and fill it with \p interval.
  //! \param size Initial size of the array.
  //! \param interval Initial value of each array element.
  //! \attention if interval is not given, it's default value is T(),which uses
  //! the T's construct.
  explicit Array(std::size_t size, const T& interval = T());

  //! \brief
  //! \param
  //! \param
  //! \attention
  //!

  //! \brief construct with initializer_list
  //! \param lst initializer_list
  //! \param
  //! \attention
  //!
  Array(const std::initializer_list<T>& lst);

  //! \brief copy construct
  //! \param
  //! \param
  //! \attention
  //!
  Array(const Array& other);

  //! \brief Move constructor.
  //! \param
  //! \param
  //! \attention
  //!
  Array(Array&& other);
};

}  // namespace big

#endif