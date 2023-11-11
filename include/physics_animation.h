#ifndef INCLUDE_BIG_PHYSICS_ANNIMATION_H_
#define INCLUDE_BIG_PHYSICS_ANNIMATION_H_
#include "animation.h"
/// @brief 
/// update(Frame) -> virtual onUpdate(Frame) -> advanceTimeStep(_timeIntervalInSeconds) -> onAdvanceTimeStep 
namespace big
{
    class PhysicsAnimation : public Animation
    {
    public:
        /// Default constructor.
        PhysicsAnimation();

        /// Destructor
        virtual ~PhysicsAnimation() = default;

        /// @brief Return true if fixed sub-time-step is used.
        ///        SubTimeStep means
        /// @return
        bool isUsingFixedSubTimeSteps() const;

        /// @brief Set true if using
        /// @param isUsing
        void setIsUsingFixedSubTimeSteps(bool isUsing);

        /// @brief Return the number of fixed sub-timesteps
        /// @return
        unsigned int numOfFixedSubTimeSteps() const;

        /// @brief Set the number ...
        /// @param numberOfSteps
        void setNumberOfFixedSubTimeSteps(unsigned int numberOfSteps);

        /// @brief Advance a single Frame.
        void advanceSingleFrame();

        /// @brief Current Frame.
        /// @return
        Frame currentFrame() const;

        /// @brief Set ...
        /// @param frame
        void setCurrentFrame(const Frame &frame);

        /// @brief Return ...
        /// @return
        double currentTimeInSeconds() const;

    private:
        ///
        /// @brief Called when a single subTimeInterval should be advanced.
        ///        
        /// @param actualTimeIntervalInSeconds 
        virtual void onAdvanceTimeStep(double actualTimeIntervalInSeconds) = 0;

        /// @brief Which is different from the Fixed-SubTimeStep.The required number of 
        ///        sub-timestep can be different depending on the physics model.       
        /// @param timeIntervalInSeconds Input the remaining time
        /// @return return a reasonable SubTimeSteps, such approching to 0 as remaining time approching 0.
        virtual unsigned int numberOfTimeSteps(double timeIntervalInSeconds) const;

        ///
        /// @brief Called at frame 0 to initialize the physics state.
        ///        Inheriting classes can override this function to setup initial condition
        ///        for the simulation.
        virtual void onInitialize();
        
        /// Member variables
        Frame _currentFrame;

        bool _isUsingFixedSubTimeSteps = true;

        /// @brief Split a frame->_timeIntervalInSeconds into  mutil-subTimeSteps.
        unsigned int _numberOfFixedSubTimeSteps = 1;

        /// @brief Frame._index * Frame._timeIntervalInSeconds
        double _currentTime = 0.0;

        //! Member funcs:
        void onUpdate(const Frame &frame) final;

        // ！ Advance ...
        void advanceTimeStep(double timeIntervalInSeconds);

        void initialize();
    };

} // namespace big

#endif