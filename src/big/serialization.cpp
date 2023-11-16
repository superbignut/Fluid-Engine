#include "serialization.h"
#include <vector>

namespace big
{

    void serialize(const Serializable *serializable, std::vector<uint8_t> *buffer)
    {
        serializable->serialize(buffer);
    }
    

}
