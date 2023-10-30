#include <iostream>
#include "quaternion.h"
#include "vector3.h"
#include <cmath>
#include "transform3.h"
int main()
{
    big::Vector3D axis(1, 1, 1);

    big::Quaternion<double> q(axis, 60.0 / 180.0 * 3.1415);

    big::Transform3 trans3({3, 4, 5}, q);

    big::Vector3D local_v({1, 2, 3});

    auto ans1 = q * local_v;

    ans1.show();

    auto world_v = trans3.toWorld(local_v);

    world_v.show();

    return 0;
}