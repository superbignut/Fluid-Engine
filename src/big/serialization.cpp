#include "serialization.h"
#include <vector>
#include <cstddef>
#include "generated/basic_types_generated.h"

namespace big
{

    void serialize(const Serializable *serializable, std::vector<uint8_t> *buffer)
    {
        serializable->serialize(buffer);
    }
    
    void serialize(const uint8_t* data, std::size_t size, std::vector<uint8_t>* buffer)
    {
        flatbuffers::FlatBufferBuilder builder(1024);
    }

}
