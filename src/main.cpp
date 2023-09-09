#include <cstdio>
#include <array>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>
const size_t kBufferSize = 80; // 占8个字节

const char *kGrayScaleTable = " .:-=+*#%@";
const size_t kGrayScaleTableSize = sizeof(kGrayScaleTable) / sizeof(char);

void accumulateWaveToHeightField(const double x, const double waveLength, const double maxHeight, std::array<double, kBufferSize> *heightField)
{
    const double quarterWaveLength = 0.25 * waveLength;
    const int start = static_cast<int>((x - quarterWaveLength) * kBufferSize);
    const int end = static_cast<int>((x + quarterWaveLength) * kBufferSize);
    for (int i = start; i < end; ++i)
    {
        int iNew = i;
        if (i < 0)
        {
            iNew = -i - 1; // 减1是为了把-1映射到0
        }
        else if (i >= static_cast<int>(kBufferSize))
        {
            iNew = 2 * kBufferSize - i - 1;
        }

        double distance = fabs((i + 0.5) / kBufferSize - x);
        double height = maxHeight * 0.5 * (cos(std::min(distance * M_PI / quarterWaveLength, M_PI)) + 1.0);
        (*heightField)[iNew] += height;
    }
}
void updateWave(const double timeINterval, double *x, double *speed)
{
    (*x) += timeINterval * (*speed);

    if ((*x) > 1)
    {
        (*speed) *= -1.0;
        (*x) += timeINterval * (*speed);
    }
    else if ((*x) < 0)
    {
        (*speed) *= -1.0;
        (*x) += timeINterval * (*speed);
    }
}

void draw(const std::array<double, kBufferSize> &heightField)
{
    std::string buffer(kBufferSize, ' ');

    for (size_t i = 0; i < kBufferSize; ++i)
    {
        double height = heightField[i];
        size_t tableIndex = std::min(static_cast<size_t>(std::floor(kGrayScaleTableSize * height)), kGrayScaleTableSize - 1);
        buffer[i] = kGrayScaleTable[tableIndex];
    }
    for (size_t i = 0; i < kBufferSize; ++i)
    {
        printf("\b");
    }
    printf("%s", buffer.c_str());
    fflush(stdout);
}
int main()
{
    const double waveLengthX = 0.8; // 波长？
    const double waveLengthY = 1.2;
    const double maxHeightX = 0.5; // 最大高度？
    const double maxHeightY = 0.4;

    double x = 0.0; // 中心点
    double y = 1.0;
    double speedX = 1.0; // 速度
    double speedY = -0.5;

    const int fps = 100; // 每秒100帧
    const double timeInterval = 1.0 / fps;

    std::array<double, kBufferSize> heightField;
    for (int i = 0; i < 1000; ++i)
    {
        updateWave(timeInterval, &x, &speedX);
        updateWave(timeInterval, &y, &speedY);

        for (double &height : heightField)
        {
            height = 0.0;
        }

        accumulateWaveToHeightField(x, waveLengthX, maxHeightX, &heightField);
        accumulateWaveToHeightField(y, waveLengthY, maxHeightY, &heightField);
        draw(heightField);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }
    // printf("%d", sizeof(int));
    printf("\n");
    fflush(stdout);
    // std::cout << sizeof(kGrayScaleTable) <<" , "<< sizeof(char)<<std::endl;
    // for(int i = 0;i < sizeof(kGrayScaleTable);++i){
    //     std::cout << kGrayScaleTable[i]<<" ";
    // }
    return 0;
}