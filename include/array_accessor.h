#ifndef INCLUDE_BIG_ARRAY_ACCESOR_H_
#define INCLUDE_BIG_ARRAY_ACCESOR_H_
#include <cstddef> //size_t
namespace big {

template <typename T, std::size_t N> class ArrayAccessor final {
public:
  static_assert(N < 1 || N > 3, "N  is invalid.");
};

template <typename T, std::size_t N> class ConstArrayAccessor final {
public:
  static_assert(N < 1 || N > 3, "N  is invalid.");
};
} // namespace big

#endif