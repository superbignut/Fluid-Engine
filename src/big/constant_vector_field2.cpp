#include "constant_vector_field2.h"

namespace big
{

    ConstantVectorField2::ConstantVectorField2(const Vector<double, 2> &value)
        : _value(value)
    {
    }

    Vector2D ConstantVectorField2::sample(const Vector2D &x) const
    {
        return _value;
    }

    std::function<Vector2D(const Vector2D &)> ConstantVectorField2::sampler() const
    {
        return [this](const Vector2D &x)
        {
            return this->sample(x);
        };
    }

    ConstantVectorField2::Builder ConstantVectorField2::builder()
    {
        return Builder();
    }

    ConstantVectorField2::Builder &ConstantVectorField2::Builder::withValue(const Vector<double, 2> &value)
    {
        _value = value;
        return *this;
    }

    ConstantVectorField2 ConstantVectorField2::Builder::build() const
    {
        return ConstantVectorField2(_value);
    }

    ConstantVectorField2Ptr ConstantVectorField2::Builder::makeShared() const
    {
        return std::make_shared<ConstantVectorField2>(_value);
    }
}