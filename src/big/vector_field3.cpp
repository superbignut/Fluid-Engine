#include "vector_field3.h"

namespace big
{

    VectorField3::VectorField3()
    {
    }

    VectorField3::~VectorField3()
    {
    }
    double VectorField3::divergence(const Vector3D &x)
    {
        return 0.0;
    }

    double VectorField3::curl(const Vector3D &x) const
    {
        return 0.0;
    }

    std::function<Vector3D(const Vector3D &)> VectorField3::sampler() const
    {
        return [this](const Vector3D &x)
        {
            return this->sample(x);
        };
    }

} // namespace big
