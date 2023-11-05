#include <iostream>
#include "sphere3.h"
int main()
{

    big::Vector<double, 3> center_{1, 2, 3};

    big::Vector<double, 3> otherpoint_{1, 3, 2};

    auto sph3_Ptr = big::Sphere3::builder().withCenter(center_).withRadius(2.0).makeShared();

    auto sph3 = big::Sphere3::builder().withCenter(center_).withRadius(2.0).build();

    // std::cout<< sph3_Ptr->_center.x<< sph3_Ptr->_center.y << sph3_Ptr->_center.y;

    std::cout << sph3.closestDistance(otherpoint_); 

    sph3.closestNormal(otherpoint_).x; 

    return 0;
}