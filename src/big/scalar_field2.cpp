#include "scalar_field2.h"

namespace big
{

    ScalarField2::ScalarField2()
    {
    }

    ScalarField2::~ScalarField2()
    {
    }

    Vector2D ScalarField2::gradient(const Vector2D &x) const
    {
        return Vector2D();
    }

    double ScalarField2::laplacian(const Vector2D &x) const
    {
        return 0.0;
    }

    std::function<double(const Vector2D &)> ScalarField2::sampler() const
    {
        // const ScalarField2 *self = this;
        return [this](const Vector2D &x)
        {
            return this->sample(x);
        };
    }

}