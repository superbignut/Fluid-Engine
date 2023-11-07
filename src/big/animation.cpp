#include "animation.h"
#include "timer.h"
#include "logging.h"
namespace big
{
    Frame::Frame(unsigned int newIndex, double newTimeIntervalInSeconds)
        : _index(newIndex), _timeIntervalInSeconds(newTimeIntervalInSeconds)
    {
    }

    double Frame::timeInSeconds() const
    {
        return _index * _timeIntervalInSeconds;
    }

    void Frame::advance()
    {
        _index++;
    }

    // Advance multi frame.
    void Frame::advance(int delta)
    {
        _index += delta;
    }

    // Advance single frame.
    Frame &Frame::operator++()
    {
        advance();
        return *this;
    }

    // Advance multi frame.
    Frame Frame::operator++(int delta)
    {
        auto result = *this;
        advance();
        return result;
    }

    void Animation::update(const Frame &frame)
    {
        Timer timer;
        onUpdate(frame);
    }

}