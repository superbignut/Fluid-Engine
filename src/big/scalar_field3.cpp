#include "scalar_field3.h"

namespace big
{

    ScalarField3::ScalarField3()
    {
    }

    ScalarField3::~ScalarField3()
    {
    }

    Vector3D ScalarField3::gradient(const Vector3D &x) const
    {
        return Vector3D();
    }

    double ScalarField3::laplacian(const Vector3D &x) const
    {
        return 0.0;
    }

    std::function<double(const Vector3D &)> ScalarField3::sampler() const
    {
        // const ScalarField3 *self = this;
        return [this](const Vector3D &x)
        {
            return this->sample(x);
        };
    }

}