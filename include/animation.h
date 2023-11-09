#ifndef INCLUDE_BIG_ANNIMATION_H_
#define INCLUDE_BIG_ANNIMATION_H_
#include <memory>
namespace big
{
    //! \brief Representation of an animation frame.
    //!
    //! The struct holds current animation frame index and frame interva in seconds.
    //!
    struct Frame final
    {
        unsigned int _index = 0;

        double _timeIntervalInSeconds = 1.0 / 60.0;

        Frame() = default;

        Frame(unsigned int newIndex, double newTimeIntervalInSeconds);

        // Return the elapsed time in seconds.
        double timeInSeconds() const;

        // Advance single frame.
        void advance();

        // Advance multi frame.
        void advance(int delta);

        // Advance single frame. ++a return a reference.
        Frame &operator++();

        // Advance single frame. a++ return a copy.
        Frame operator++(int);
    };

    //! \brief Abstract base class for animaton-related class.
    //! This class represents  the animation logic in very abstract level.
    //! Generally animation is a function of the time and the previoud state.
    class Animation
    {
    public:
        Animation() = default;

        virtual ~Animation() = default;

        //! \brief This func update the animation by calling Animation::onUpdate()
        ///        Update the animation to this specific frame.
        void update(const Frame &frame);

    protected:
        //! \brief This func is called from undate()
        //! This func needed to be overrided by deriveded class.
        virtual void onUpdate(const Frame &frame) = 0;
    };

    typedef std::shared_ptr<Animation> AnimationPtr;
}

#endif