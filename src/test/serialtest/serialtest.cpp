#include <gtest/gtest.h>
#include "serialization.h"

TEST(Serialization, Try1)
{
    EXPECT_EQ(1, 1);
}

TEST(Serialization, Try2)
{
    std::vector<int> v;

    std::cout << v.size() << v.capacity() << std::endl;
}
