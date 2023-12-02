#ifndef SRC_BIG_FACTORY_H_
#define SRC_BIG_FACTORY_H_
#include "point_neighbor_searcher2.h"

namespace big
{
    class Factory
    {
    public:
        static PointNeighborSearcher2Ptr buildPointNeighborSearcher2(const std::string& name);
    }

}
#endif