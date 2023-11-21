#include <gtest/gtest.h>
#include "serialization.h"
#include "particle_system_data2.h"
#include <stdexcept>
#include "parallel.h"

TEST(Serialization, Try1)
{
    EXPECT_EQ(1, 1);
}

TEST(Particle_system_data2, Try1)
{
    big::ParticleSystemData2 a(5);
}

TEST(Parallel, Try1)
{
    
}
