#ifndef INCLUDE_BIG_CONSTANT_VECTOR_FIELD3_H_
#define INCLUDE_BIG_CONSTANT_VECTOR_FIELD3_H_

#include "vector_field3.h"

namespace big
{
    class ConstantVectorField3 final : public VectorField3
    {
    public:
        class Builder;

        /// @brief
        /// @param value
        explicit ConstantVectorField3(const Vector<double, 3> &value);

        /// @brief
        /// @param x
        /// @return
        Vector3D sample(const Vector3D &x) const override;

        /// @brief
        /// @return
        std::function<Vector3D(const Vector3D &)> sampler() const override;

        /// @brief
        /// @return
        static Builder builder();

    private:
        Vector<double, 3> _value;
    };
    typedef std::shared_ptr<ConstantVectorField3> ConstantVectorField3Ptr;

    class ConstantVectorField3::Builder final
    {
    public:
        Builder &withValue(const Vector<double, 3> &value);

        ConstantVectorField3 build() const;

        ConstantVectorField3Ptr makeShared() const;
    private:
        Vector<double, 3> _value{0,0,0};
    };
}

#endif