#include <gtest/gtest.h>
#include "serialization.h"

TEST(Serialization, Try1)
{
    EXPECT_EQ(1, 1);
}

TEST(Serialization, Try2)
{
    uint8_t data[] = {1, 2, 3, 5, 6, 255};
    for (auto element : data)
    {
        printf("%d ", element);
    }
    std::cout << std::endl;
    std::size_t size = 6;

    std::vector<uint8_t> buffer;

    big::serialize(data, size, &buffer);

    for (auto ele : buffer)
    {
        printf("%d ", ele);
    }

    std::cout << std::endl;
}
