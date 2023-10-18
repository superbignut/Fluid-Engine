#ifndef INCLUDE_BIG_SCALAR_FIELD2_H_
#define INCLUDE_BIG_SCALAR_FIELD2_H_
#include "field2.h"
#include "vector2.h"
#include <functional>

namespace big
{
    class ScalarField2 : public Field2
    {
    public:

        //! default constructor
        ScalarField2();

        //! default destructor
        virtual ~ScalarField2();

        //! return scalar at x
        virtual double sample(const Vector2D &x) const = 0;
        
        //! return gradient at x
        virtual Vector2D gradient(const Vector2D& x) const;

        //! return laplacian at x
        virtual double laplacian(const Vector2D& x) const;

        //! return function object
        virtual std::function<double(const Vector2D&)> sampler() const;

    };
    //! shared_ptr for ScalarField2
    typedef std::shared_ptr<ScalarField2> ScalarField2Ptr;

}

#endif