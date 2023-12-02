#include <iostream>
#include "inner_data_test_generated.h"
#include "vector2.h"
#include <vector>

int main()
{
    flatbuffers::FlatBufferBuilder builder(1024);
    auto fbsname = builder.CreateString("bignut");
    double age = 23;
    auto heightAndWeight = big::Vector2D(180.0, 160.0);
    // auto fbsHeightAndWeight = builder.

    std::vector<big::Vector2D> usedHAW = {{170.0,130.0}, {175.0,140.0},{180.0,160.0}};
    return 0;
}