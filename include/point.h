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

  //! construct 
  Point();

  //! construct instance with parameters
  template <typename... Params>
  explicit Point(Params... param);
};

}  // namespace big

#endif
