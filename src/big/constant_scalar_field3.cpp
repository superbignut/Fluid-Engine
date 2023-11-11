#include "constant_scalar_field3.h"

namespace big
{

    ConstantScalarField3::ConstantScalarField3(double value)
        : _value(value)
    {
    }

    double ConstantScalarField3::sample(const Vector3D &x) const
    {
        return _value;
    }

    std::function<double(const Vector3D &)> ConstantScalarField3::sampler() const
    {
        return [this](const Vector3D &x)
        {
            return this->sample(x);
        };
    }
    ConstantScalarField3::Builder ConstantScalarField3::builder()
    {
        return Builder();
    }

    ConstantScalarField3::Builder &ConstantScalarField3::Builder::withValue(double value)
    {
        _value = value;
        return *this;
    }

    ConstantScalarField3 ConstantScalarField3::Builder::build() const
    {
        return ConstantScalarField3(_value);
    }

    ConstantScalarField3Ptr ConstantScalarField3::Builder::makeShared() const
    {
        return std::make_shared<ConstantScalarField3>(_value);
    }

}