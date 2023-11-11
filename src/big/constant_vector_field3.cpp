#include "constant_vector_field3.h"

namespace big
{

    ConstantVectorField3::ConstantVectorField3(const Vector<double, 3> &value)
        : _value(value)
    {
    }

    Vector3D ConstantVectorField3::sample(const Vector3D &x) const
    {
        return _value;
    }

    std::function<Vector3D(const Vector3D &)> ConstantVectorField3::sampler() const
    {
        return [this](const Vector3D &x)
        {
            return this->sample(x);
        };
    }

    ConstantVectorField3::Builder ConstantVectorField3::builder()
    {
        return Builder();
    }

    ConstantVectorField3::Builder &ConstantVectorField3::Builder::withValue(const Vector<double, 3> &value)
    {
        _value = value;
        return *this;
    }

    ConstantVectorField3 ConstantVectorField3::Builder::build() const
    {
        return ConstantVectorField3(_value);
    }

    ConstantVectorField3Ptr ConstantVectorField3::Builder::makeShared() const
    {
        return std::make_shared<ConstantVectorField3>(_value);
    }
}