#ifndef INCLUDE_BIG_POINT_H
#define INCLUDE_BIG_POINT_H

#include <array>
#include <type_traits>

namespace big {

//! \brief Generic N-dimensional point class.
//! \param T type
//! \param N dimension
//!
template <typename T, std::size_t N>
class Point final {
 public:
  static_assert(N > 0, "dimension should greater than 0.");
  static_assert(std::is_arithmetic<T>::value,
                "point only can be instantiated with  arithmetic types.");

  //! construct with zero parameters
  Point();

  //! construct instance with parameters
  //! ... Params 表示接受可变数量的参数
  //! explicit 表示不能被隐式转换和拷贝初始化
  template <typename... Params> 
  explicit Point(Params... param); 


};

}  // namespace big

#endif
