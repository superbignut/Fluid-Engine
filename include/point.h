#ifndef INCLUDE_BIG_POINT_H_
#define INCLUDE_BIG_POINT_H_

#include <array>
#include <utility>
// #include <type_traits>

namespace big
{

template <typename T, std::size_t N> class Point final
{
  public:
    static_assert(N > 0, "dimension should greater than 0.");
    static_assert(std::is_arithmetic<T>::value, "point only can be instantiated with  arithmetic types.");

    Point();

    template <typename... Params> explicit Point(Params... param);

    template <typename U> explicit Point(const std::initializer_list<U> &lst);

    Point(const Point &other);

    template <typename U> void set(const std::initializer_list<U> &lst);

    void set(const Point &other);

    template <typename U> Point &operator=(const std::initializer_list<U> &lst);

    Point &operator=(const Point &other);

    const T &operator[](std::size_t i) const;

    T &operator[](std::size_t);

  private:
    std::array<T, N> _elements;
    template <typename... Params> void setAt(std::size_t i, T v, Params... params);

    void setAt(std::size_t i, T v);
};

} // namespace big

#include "detail/point-inl.h"
#endif
