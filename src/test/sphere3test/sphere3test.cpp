#include <iostream>
#include "sphere3.h"
int main()
{

    big::Vector<double, 3> center_{1, 2, 3};

    big::Vector<double, 3> otherpoint_{1, 3, 2};

    // big::Ray<double, 3> ray3({0, 0, 0}, {1, 1, 0.5});

    auto sph3_Ptr = big::Sphere3::builder().withCenter(center_).withRadius(2.0).makeShared();

    auto sph3 = big::Sphere3::builder().withCenter(center_).withRadius(2.0).build();

    // std::cout<< sph3_Ptr->_center.x<< sph3_Ptr->_center.y << sph3_Ptr->_center.y;

    std::cout << sph3.closestDistance(otherpoint_) << std::endl;

    sph3.closestNormal(otherpoint_).show();

    double t = 0;
    while (true)
    {
        big::Ray<double, 3> ray3({-10, -10, 0}, {11, 12+t, 3+t});
        if(sph3.intersects(ray3)){
            std::cout << "Yes : t is:" << t<<std::endl;
            t += 0.1;
            auto temp = sph3.closestIntersection(ray3);
            temp.point.show();
            temp.normal.show();
            std::cout <<"dis is :" << temp.distance<<std::endl;
        }
        else
        {
            std::cout << "No : t is:" << t<<std::endl;

            break;
        }
    }

    return 0;
}