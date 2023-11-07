#ifndef INCLUDE_BIG_TIMER_H_
#define INCLUDE_BIG_TIMER_H_

#include <chrono>
namespace big
{

    class Timer
    {
    public:
        //! Construct the timer and start ticking.
        Timer();

        //! Return the time duration.
        double durationInSeconds() const;

        //! Reset the timer.
        void reset();

    private:
        std::chrono::steady_clock _clock;
        std::chrono::steady_clock::time_point _startingPoint;
    };

}

#endif