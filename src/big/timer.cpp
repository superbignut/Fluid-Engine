#include "timer.h"
namespace big
{
    Timer::Timer()
    {
        _startingPoint = _clock.now();
    }

    double Timer::durationInSeconds() const
    {
        auto end = _clock.now();   
        auto interval = std::chrono::duration_cast<std::chrono::microseconds>(end - _startingPoint).count(); //us
        return interval / 1000.0 / 1000.0;
    }

    void Timer::reset()
    {
        _startingPoint = _clock.now();
    }

} // namespace big
