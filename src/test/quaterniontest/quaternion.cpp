#include <iostream>
#include "quaternion.h"
#include "vector3.h"

int main()
{

    big::Vector3F axis(1, 1, 1);
    big::Quaternion<float> q(axis, 60.0 / 180.0 * 3.1415);
    q.show();
    big::Quaternion<float> q2(axis, 90.0 / 180.0 * 3.1415);
    q2.show();
    big::Quaternion<float> q3(axis, 120.0 / 180.0 * 3.1415);
    q3.show();

    big::Vector3F vt(2, 3, -1);

    auto tu = vt.tangential();

    std::get<0>(tu).show();
    std::get<1>(tu).show();

    big::Vector3F from(2, 7, 4);
    big::Vector3F to(-1, 11, 3);
    big::Quaternion<float> qft(from, to);
    qft.show();

    return 0;
}