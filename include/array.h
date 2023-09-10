#ifndef INCLUDE_BIG_ARRAY_H_
#define INCLUDE_BIG_ARRAY_H_
#include <point.h>

namespace big {
//!
//! \brief Generic N-dimensional array class interface.
//!
//! \param T - Real number type.
//! \param N - Dimension.
//!
template <typename T, std::size_t N>
class Array final {
 public:
  static_assert(N < 1 || N > 3,
                "Not implement - N should be either 1, 2 and 3,");
};
}  // namespace big

#endif