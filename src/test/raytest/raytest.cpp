#include <iostream>
#include "ray2.h"
#include "bounding_box2.h"
#include "vector2.h"
int main()
{
    big::Vector2F a_origin{0, 0};
    big::Vector2F a_direction{0, 1};
    big::Ray<float, 2> ray2(a_origin, a_direction);

    big::BoundingBox<float, 2> box2({1, 0},{5, 5});

   if(box2.intersects(ray2)){
         std::cout << "True" << std::endl;
    }
    else{
        std::cout <<"False" << std::endl;
    }

    box2.midPoint();

    std::cout <<box2.diagonalLength();

    box2.clamp(a_origin);

    return 0;
}