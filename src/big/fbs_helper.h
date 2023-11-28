#ifndef SRC_BIG_FBS_HELPERS_H_
#define SRC_BIG_FBS_HELPERS_H_
#include "generated/basic_types_generated.h"
#include "size2.h"
#include "size3.h"
#include "vector2.h"
#include "vector3.h"
#include <vector>

namespace big
{

    inline fbs::Size2 bigToFbs(const Size2 &vec)
    {
        return fbs::Size2(vec.x, vec.y);
    }

    inline fbs::Vector2D bigToFbs(const Vector2D &vec)
    {
        return fbs::Vector2D(vec.x, vec.y);
    }

    inline Size2 fbsToBig(const fbs::Size2 &vec)
    {
        return Size2(vec.x(), vec.y());
    }

    inline Vector2D fbsToBig(const fbs::Vector2D &vec)
    {
        return Vector2D(vec.x(), vec.y());
    }

}

#endif