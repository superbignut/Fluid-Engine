#include <big.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace big;

int main() {
    ::testing::InitGoogleMock();
    ::testing::InitGoogleTest();


    int ret = RUN_ALL_TESTS();
    return ret;
}