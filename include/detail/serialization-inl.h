#ifndef INCLUDE_BIG_SERIALIZATION_INL_H_
#define INCLUDE_BIG_SERIALIZATION_INL_H_
#include <cstring>
namespace big
{

    template <typename T>
    void serialize(const ConstArrayAccessor1<T> &array, std::vector<uint8_t> *buffer)
    {
        std::size_t size = sizeof(T) * array.size(); //总共有多少个字节 size
        serialize(reinterpret_cast<uint8_t*>(array.data()), size, buffer); // 把T指针转为字节指针 然后结合字节个数size进行序列化
    }

    template <typename T>
    void deserialize(const std::vector<uint8_t> &buffer, Array1<T> *array)
    {
        std::vector<uint8_t> data;
        deserialize(buffer, &data); // 反序列化
        array->resize(data.size() / sizeof(T)); // 计算原始数据的大小 
        memcpy(reinterpret_cast<uint8_t*>(array->data()), data.data(),data.size()); //按照uint8_t进行copy
    }

}

#endif