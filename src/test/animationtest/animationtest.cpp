#include <iostream>
#include "animation.h"
#include "timer.h"
#include "logging.h"
int main()
{
    big::Frame a;
    big::Timer t;
    std::cout << t.durationInSeconds() << std::endl;
    std::cout << a._timeIntervalInSeconds << std::endl;
    std::cout << t.durationInSeconds() << std::endl;
    t.reset();
    std::cout << t.durationInSeconds() << std::endl;

    big::LoggingLeve level = big::LoggingLeve::Info;

    big::Logger logger(level);
    logger << "aaaa";
    return 0;
}