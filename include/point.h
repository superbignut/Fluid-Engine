#ifndef INCLUDE_BIG_POINT_H
#define INCLUDE_BIG_POINT_H

#include <array>
#include <type_traits>

namespace big {

//! \brief Generic N-dimensional point class. final means the class can't be
//! derived from. \param T type \param N dimension
// ！
template <typename T, std::size_t N>
class Point final {
 public:
  static_assert(N > 0, "dimension should greater than 0.");
  static_assert(std::is_arithmetic<T>::value,
                "point only can be instantiated with  arithmetic types.");

  //! construct with zero parameters.
  //!
  Point();

  //! construct point instance with parameters...Params means variable number of
  //! arguments. explicit means it cannot be used for implicit conversions and
  //! copy-initialization.
  //!
  template <typename... Params>
  explicit Point(Params... param);

  //! contruct point instance with initializer_list. both const and init_list
  //! ensure lst can't be changed
  //!
  template <typename U>
  explicit Point(const std::initializer_list<U>& lst);

  //! copy constructor
  //!
  Point(const Point& other);

  //! set point instance with initializer list
  //!
  template <typename U>
  void set(const std::initializer_list<U>& lst);

  //! set ...
  void set(const Point& other);

  //! copy assignment operator means a=b same as a.operator=(b) return type is
  //! Point& means u can do many assign operate.
  //!
  template <typename U>
  Point& operator=(const std::initializer_list<U>& lst);

  //! copy assignment operator
  //!
  Point& operator=(const Point& other);

  //! return the const reference to the \p i -th element
  //!
  const T& operator[](std::size_t i) const;

  //! return the const reference to the \p i -th element
  //!
  T& operator[](std::size_t);

 private:
  std::array<T, N> _elements;
  template <typename... Params>
  void setAt(std::size_t i, T v, Params... params);

  void setAt(std::size_t i, T v);
};

}  // namespace big

#include "detail/point-inl.h"
#endif
