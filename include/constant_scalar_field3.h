#ifndef INCLUDE_BIG_CONSTANT_SCALAR_FIELD3_H_
#define INCLUDE_BIG_CONSTANT_SCALAR_FIELD3_H_

#include "scalar_field3.h"
namespace big
{
    class ConstantScalarField3 final : public ScalarField3
    {
    public:
        class Builder;

        /// @brief
        /// @param value
        explicit ConstantScalarField3(double value);

        /// @brief
        /// @param x
        /// @return
        double sample(const Vector3D &x) const override;

        /// @brief
        /// @return
        std::function<double(const Vector3D &)> sampler() const override;

        /// @brief
        /// @return
        static Builder builder();

    private:
        double _value = 0.0;
    };

    typedef std::shared_ptr<ConstantScalarField3> ConstantScalarField3Ptr;

    class ConstantScalarField3::Builder final
    {
    public:
        Builder &withValue(double value);

        ConstantScalarField3 build() const;

        ConstantScalarField3Ptr makeShared() const;

    private:
        double _value = 0.0;
    };
}

#endif