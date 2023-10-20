#ifndef INCLUDE_BIG_VECTOR_FIELD3_H_
#define INCLUDE_BIG_VECTOR_FIELD3_H_
#include "field3.h"
#include "vector3.h"
namespace big
{

    class VectorField3 : public Field3
    {
    public:
        VectorField3();

        virtual ~VectorField3();

        virtual Vector3D sample(const Vector3D &x) const = 0;

        virtual double divergence(const Vector3D &x);

        virtual double curl(const Vector3D &x) const;

        virtual std::function<Vector3D(const Vector3D &)> sampler() const;
    };

    typedef std::shared_ptr<VectorField3> VectorField3Ptr;
}


    


#endif