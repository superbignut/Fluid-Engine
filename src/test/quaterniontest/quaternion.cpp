#include <iostream>
#include "quaternion.h"
#include "vector3.h"
#include <cmath>
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

    auto m_axis_rad = big::Matrix3x3F::makeRotationMatrix(axis, 104.0 / 180.0 * 3.1415);

    auto ans1 = m_axis_rad * vt;

    qft.set(axis, 104.0 / 180.0 * 3.1415);

    auto ans2 = qft.mul(vt);

    ans1.show();
    ans2.show();

    big::Quaternion<float> q4(1, 2, 3, 4);
    big::Quaternion<float> q5(1, -2, -3, -4);

    auto ans3 = q4.mul(q5);
    ans3.show();
    return 0;
}