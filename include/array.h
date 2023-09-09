#ifndef INCLUDE_BIG_ARRAY_H
#define INCLUDE_BIG_ARRAY_H
#include<point.h>


namespace big {

template <typename T, std::size_t N>
class Array final {
 public:
  static_assert(N < 1 || N > 3,
                "Not implement - N should be either 1, 2 and 3,");
};
}  // namespace big
#endif