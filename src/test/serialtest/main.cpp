#include <big.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "particle_system_data2.h"

using namespace big;

int main() {
    ::testing::InitGoogleMock();
    ::testing::InitGoogleTest();

    // ParticleSystemData2 a(5);

    int ret = RUN_ALL_TESTS();
    return ret;
    // return 0;
}