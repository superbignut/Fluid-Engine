#include <gtest/gtest.h>
#include <fstream>
#include "big.h"
#include "manual_tests.h"


using namespace big;

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);

    creatDirectory(BIG_TESTS_OUTPUT_DIR); // 创建根目录

    int ret = RUN_ALL_TESTS();
    
    return ret;
}