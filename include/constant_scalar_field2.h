#ifndef INCLUDE_BIG_CONSTANT_SCALAR_FIELD2_H_
#define INCLUDE_BIG_CONSTANT_SCALAR_FIELD2_H_

#include "scalar_field2.h"
namespace big
{
    class ConstantScalarField2 final : public ScalarField2
    {
    public:
        class Builder;

        /// @brief
        /// @param value
        explicit ConstantScalarField2(double value);

        /// @brief
        /// @param x
        /// @return
        double sample(const Vector2D &x) const override;

        /// @brief
        /// @return
        std::function<double(const Vector2D &)> sampler() const override;

        /// @brief
        /// @return
        static Builder builder();

    private:
        double _value = 0.0;
    };

    typedef std::shared_ptr<ConstantScalarField2> ConstantScalarField2Ptr;

    class ConstantScalarField2::Builder final
    {
    public:
        Builder &withValue(double value);

        ConstantScalarField2 build() const;

        ConstantScalarField2Ptr makeShared() const;

    private:
        double _value = 0.0;
    };
}

#endif