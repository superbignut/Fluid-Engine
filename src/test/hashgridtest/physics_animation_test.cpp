#include <iostream>
#include "point_parallel_hash_grid_searcher2.h"

int main(){

    big::Size2 size2(100, 100);
    double gridspace = 2.0;
    big::PointParallelHashGridSearcher2 ppp(size2, gridspace);

    big::Array1<big::Vector2D> pos(100, {2,3});

    ppp.build(pos.constAccessor());

    return 0;
}