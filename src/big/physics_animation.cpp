#include "physics_animation.h"
#include "constants.h"
namespace big
{

    PhysicsAnimation::PhysicsAnimation()
    {
        _currentFrame._index = -1; // Why -1?
    }
    bool PhysicsAnimation::isUsingFixedSubTimeSteps() const
    {
        return _isUsingFixedSubTimeSteps;
    }

    void PhysicsAnimation::setIsUsingFixedSubTimeSteps(bool isUsing)
    {
        _isUsingFixedSubTimeSteps = isUsing;
    }

    unsigned int PhysicsAnimation::numOfFixedSubTimeSteps() const
    {
        return _numberOfFixedSubTimeSteps;
    }

    void PhysicsAnimation::setNumberOfFixedSubTimeSteps(unsigned int numberOfSteps)
    {
        _numberOfFixedSubTimeSteps = numberOfSteps;
    }

    void PhysicsAnimation::advanceSingleFrame()
    {
        Frame f = _currentFrame;
        update(++f);
    }

    Frame PhysicsAnimation::currentFrame() const
    {
        return _currentFrame;
    }

    void PhysicsAnimation::setCurrentFrame(const Frame &frame)
    {
        _currentFrame = frame;
    }

    double PhysicsAnimation::currentTimeInSeconds() const
    {
        return _currentTime;
    }

    unsigned int PhysicsAnimation::numberOfTimeSteps(double timeIntervalInSeconds) const
    {
        // Need to be overrided.
        return _numberOfFixedSubTimeSteps;
    }

    void PhysicsAnimation::onUpdate(const Frame &frame)
    {
        if (frame._index > _currentFrame._index)
        {
            if (_currentFrame._index < 0)
            {
                initialize();
            }

            int32_t numberOfFrames = frame._index - _currentFrame._index;

            for (int32_t i = 0; i < numberOfFrames; ++i)
            {
                advanceTimeStep(frame._timeIntervalInSeconds);
            }
            _currentFrame = frame;
        }
    }

    void PhysicsAnimation::advanceTimeStep(double timeIntervalInSeconds)
    {
        _currentTime = _currentFrame.timeInSeconds();

        if (_isUsingFixedSubTimeSteps)
        {
            const double actualTimeInterval =
                timeIntervalInSeconds / static_cast<double>(_numberOfFixedSubTimeSteps);
            for (unsigned int i = 0; i < _numberOfFixedSubTimeSteps; ++i)
            {
                onAdvanceTimeStep(actualTimeInterval);
                _currentTime += actualTimeInterval;
            }
        }
        else
        {
            double remainingTime = timeIntervalInSeconds;
            while (remainingTime > kEpsilonD)
            {

                auto numsteps = numberOfTimeSteps(remainingTime); // No FIxed, flexiable
                //!
                //! In order to less remainingTime to 0, the return of numberOfTimeSteps() also need to approach 1.
                const double actualTimeInterval =
                    remainingTime / static_cast<double>(numsteps);
                onAdvanceTimeStep(actualTimeInterval);
                //!
                remainingTime -= actualTimeInterval;
                _currentTime += actualTimeInterval;
            }
        }
    }


    void PhysicsAnimation::initialize()
    {
        onInitialize();
    }

    void PhysicsAnimation::onInitialize()
    {

    }
}