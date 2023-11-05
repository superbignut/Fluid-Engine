#include <iostream>
#include "sphere2.h"
int main()
{

    big::Vector<double, 2> center_{1, 2};

    big::Vector<double, 2> center_1(1, 2);

    auto sph2_Ptr = big::Sphere2::builder().withCenter(center_).withRadius(2.0).makeShared();

    auto sph2 = big::Sphere2::builder().withCenter(center_).withRadius(2.0).build();

    std::cout<< sph2_Ptr->_center.x<< sph2_Ptr->_center.y;

    
    return 0;
}