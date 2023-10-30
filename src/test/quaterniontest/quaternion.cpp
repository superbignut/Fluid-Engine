#include <iostream>
#include "quaternion.h"
#include "vector3.h"
#include <cmath>
int main()
{

    big::Vector3F axis(1, 1, 1);

    big::Vector3F vt(2, 3, -1);

    big::Quaternion<float> qft;

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