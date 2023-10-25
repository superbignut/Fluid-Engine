#include <iostream>
#include "ray2.h"
int main()
{
    big::Vector2F a_origin{1,1};
    big::Vector2F a_direction{2,2};
    big::Ray<float, 2> ray2(a_origin, a_direction);
    std::cout << ray2.direction.x;


    int a =1;
    int b =2;
    std::swap(a, b);
    std::cout <<a<<" "<<b;
    return 0;
}