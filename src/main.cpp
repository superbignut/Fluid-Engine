#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <point.h>


int main()
{   
    big::Point<int, 3> point(1.1, 2.2 ,3.3333);
    big::Point<int, 3> point1(point);

    return 0;
}