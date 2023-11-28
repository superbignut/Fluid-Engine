#include <iostream>
#include "point_parallel_hash_grid_searcher2.h"

int main()
{

    big::Size2 size2(100, 100);
    double gridspace = 2.0;
    big::PointParallelHashGridSearcher2 ppp(size2, gridspace);

    big::Array1<big::Vector2D> pos{{1, 2}, {2, 3},{3,4},{-4,-3}, {5, 6}, {1, 3.0}, {2, 5}, {5, 1},{2, 7}};

    // std::cout << pos.size() << std::endl;

    ppp.build(pos.constAccessor());

    std::vector<uint8_t> *buffer; //create a serialize buffer.
    
    ppp.show();
    ppp.serialize(buffer);

    return 0;
}