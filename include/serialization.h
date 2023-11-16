#ifndef INCLUDE_BIG_SERIALIZATION_H_
#define INCLUDE_BIG_SERIALIZATION_H_
#include <array1.h>
#include <vector>
namespace big
{
    
    //! Abstract base class for any serialization class.
    class Serializable
    {
    public:
        Serializable() = default;

        virtual ~Serializable() = default;

        /// @brief Serializes this instance into the flat buffer.
        /// @param buffer
        virtual void serialize(std::vector<uint8_t> *buffer) const = 0;

        /// @brief Deserialize this instance from the flat buffer.
        /// @param buffer
        virtual void deserialize(const std::vector<uint8_t> &buffer) = 0;
    };

    void serialize(const Serializable *serializable, std::vector<uint8_t> *buffer);

    void serialize(const uint8_t *data, std::size_t size, std::vector<uint8_t> *buffer);

    template <typename T>
    void serialize(const ConstArrayAccessor1<T> &array, std::vector<uint8_t> *buffer);

    void deserialize(const std::vector<uint8_t>& buffer, Serializable* serializable);

    void deserialize(const std::vector<uint8_t> &buffer, std::vector<uint8_t> *data);

    template <typename T>
    void deserialize(const std::vector<uint8_t> &buffer, Array1<T> *array);
}


#include "detail/serialization-inl.h"
#endif