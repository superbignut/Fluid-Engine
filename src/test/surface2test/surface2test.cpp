#include <iostream>
#include "sphere2.h"
int main()
{

    big::Vector<double, 2> cen{1, 2};

    // auto sph2 = big::Sphere2::builder().withCenter().withCenter().makeShared(); 
    
    double a = 0.1;
    if(a > 0)
    {
        std::cout <<"yes";
    }

    return 0;
}