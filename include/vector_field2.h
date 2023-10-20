#ifndef INCLUDE_BIG_VECTOR_FIELD2_H_
#define INCLUDE_BIG_VECTOR_FIELD2_H_
#include "field2.h"
#include "vector2.h"
namespace big
{

    class VectorField2 : public Field2
    {
    public:
        VectorField2();

        virtual ~VectorField2();

        virtual Vector2D sample(const Vector2D &x) const = 0;

        virtual double divergence(const Vector2D &x);

        virtual double curl(const Vector2D &x) const;

        virtual std::function<Vector2D(const Vector2D &)> sampler() const;
    };

    typedef std::shared_ptr<VectorField2> VectorField2Ptr;
}

#endif