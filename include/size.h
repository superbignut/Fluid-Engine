#ifndef INCLUDE_BIG_SIZE_H_
#define INCLUDE_BIG_SIZE_H_
#include <point.h>
namespace big
{
template <std::size_t N> using Size = Point<std::size_t, N>;
}

#endif