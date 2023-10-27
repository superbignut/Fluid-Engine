#ifndef INCLUDE_BIG_TRANSFORM2_INL_H_
#define INCLUDE_BIG_TRANSFORM2_INL_H_

#include <cmath>
#include <algorithm>

namespace big {

        inline Transform2::Transform2(){}

        inline Transform2::Transform2(const Vector<double, 2>&translation, double orientation)
                : _translation(translation), _orientation(orientation)
        {
                _cosAngle = std::cos(orientation);
                _sinAngle = std::sin(orientation);
        }
        






}

#endif