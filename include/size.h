#ifndef INCLUDE_BIG_SIZE_H
#define INCLUDE_BIG_SIZE_H
#include <point.h>
    namespace{
    template <std::size_t N> using Size = Point<std::size_t, N>;
    }

#endif