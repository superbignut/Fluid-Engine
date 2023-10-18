#ifndef INCLUDE_BIG_SCALAR_FIELD3_H_
#define INCLUDE_BIG_SCALAR_FIELD3_H_
#include "field3.h"
#include "vector3.h"
#include <functional>

namespace big
{
    class ScalarField3 : public Field3
    {
    public:

        //! default constructor
        ScalarField3();

        //! default destructor
        virtual ~ScalarField3();

        //! return scalar at x
        virtual double sample(const Vector3D &x) const = 0;
        
        //! return gradient at x
        virtual Vector3D gradient(const Vector3D& x) const;

        //! return laplacian at x
        virtual double laplacian(const Vector3D& x) const;

        //! return function object
        virtual std::function<double(const Vector3D&)> sampler() const;

    };
    //! shared_ptr for ScalarField3
    typedef std::shared_ptr<ScalarField3> ScalarField3Ptr;

}
    


#endif