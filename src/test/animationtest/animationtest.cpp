#include <iostream>
#include "animation.h"
#include "timer.h"
#include "logging.h"
#include <thread>
#include <future>
#include <vector>
int main()
{
    big::Frame a;
    big::Timer t;
    std::cout << t.durationInSeconds() << std::endl;
    std::cout << a._timeIntervalInSeconds << std::endl;
    std::cout << t.durationInSeconds() << std::endl;
    t.reset();
    std::cout << t.durationInSeconds() << std::endl;

    
    // big::LoggingLeve level = big::LoggingLeve::Info;

    // big::Logger logger(level);

    // std::vector<std::future<void>> pool;
    // for(int i =0; i< 10; ++i)
    // {
    //     pool.push_back(std::async([i=i, &logger](){logger << std::to_string(i);}));
    // }

    // big::infoLogger << "aaaa";
    // big::infoLogger << "ccccc" <<__FILE__;
    int(10);
    int(20);
    return 0;
}