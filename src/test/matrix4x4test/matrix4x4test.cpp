#include <iostream>
#include "matrix4x4.h"

int main()
{

    big::Matrix4x4D m(1, 2, 3, 4,
                      10, 9, 6, 13,
                      4, 5, 13, 33,
                      9, 7, 11, 23);

    auto mi = m;

    mi.invert();

    auto ans = mi * m;

    ans.show();

    std::cout << m.determinant()<<std::endl;

    return 0;
}