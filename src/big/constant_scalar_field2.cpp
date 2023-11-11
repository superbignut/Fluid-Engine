#include "constant_scalar_field2.h"

namespace big
{

    ConstantScalarField2::ConstantScalarField2(double value)
        : _value(value)
    {
    }

    double ConstantScalarField2::sample(const Vector2D &x) const
    {
        return _value;
    }

    std::function<double(const Vector2D &)> ConstantScalarField2::sampler() const
    {
        return [this](const Vector2D &x)
        {
            return this->sample(x);
        };
    }
    ConstantScalarField2::Builder ConstantScalarField2::builder()
    {
        return Builder();
    }

    ConstantScalarField2::Builder &ConstantScalarField2::Builder::withValue(double value)
    {
        _value = value;
        return *this;
    }

    ConstantScalarField2 ConstantScalarField2::Builder::build() const
    {
        return ConstantScalarField2(_value);
    }

    ConstantScalarField2Ptr ConstantScalarField2::Builder::makeShared() const
    {
        return std::make_shared<ConstantScalarField2>(_value);
    }

}