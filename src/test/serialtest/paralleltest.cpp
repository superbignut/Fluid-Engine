#include <gtest/gtest.h>
#include "serialization.h"
#include "particle_system_data2.h"
#include <stdexcept>
#include "parallel.h"
#include <vector>

TEST(parallelTest, try1)
{
    std::vector<int> vec(100, 4);
    std::cout << vec.size() << std::endl;
    big::parallelFill(vec.begin(), vec.end(), 11);
    
    for (auto ele : vec)
    {
        std::cout << ele << " ";
    }
}