#include "serialization.h"
#include <vector>
#include <cstddef>
#include "generated/flat_data_generated.h"

namespace big
{

    void serialize(const Serializable *serializable, std::vector<uint8_t> *buffer)
    {
        serializable->serialize(buffer);
    }
    
    /// @brief 序列化一段具有flat_data.fbs格式的缓冲区
    /// @param data 指向原始数据的指针
    /// @param size 原始数据的大小
    /// @param buffer 指向存储序列化之后数据的指针
    void serialize(const uint8_t* data, std::size_t size, std::vector<uint8_t>* buffer)
    {
        flatbuffers::FlatBufferBuilder builder(1024);

        auto fbsData = fbs::CreateFlatData(builder, builder.CreateVector(data, size));

        builder.Finish(fbsData);

        uint8_t*buf = builder.GetBufferPointer();

        std::size_t sz = builder.GetSize();

        buffer->resize(sz);
        memcpy(buffer->data(), buf, sz);
    }

    void deserialize(const std::vector<uint8_t>& buffer, Serializable* serializable)
    {
        serializable->deserialize(buffer);
    }

    /// @brief 与序列化一段具有flat_data.fbs格式的缓冲区的serialize
    /// 函数相对应，deserialize为反序列化这段缓冲区
    /// @param buffer 
    /// @param data 
    void deserialize(const std::vector<uint8_t> &buffer, std::vector<uint8_t> *data)
    {
        auto fbsData = fbs::GetFlatData(buffer.data());
        data->resize(fbsData->data()->size());
        std::copy(fbsData->data()->begin(), fbsData->data()->end(), data->begin());
    }
}
