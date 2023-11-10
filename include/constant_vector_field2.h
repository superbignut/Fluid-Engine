#ifndef INCLUDE_BIG_CONSTANT_VECTOR_FIELD2_H_
#define INCLUDE_BIG_CONSTANT_VECTOR_FIELD2_H_

#include "vector_field2.h"

namespace big
{
    class ConstantVectorField2 final : public VectorField2
    {
    public:
        class Builder;

        /// @brief
        /// @param value
        explicit ConstantVectorField2(const Vector<double, 2> &value);

        /// @brief
        /// @param x
        /// @return
        Vector2D sample(const Vector2D &x) const override;

        /// @brief
        /// @return
        std::function<Vector2D(const Vector2D &)> sampler() const override;

        /// @brief
        /// @return
        static Builder builder();

    private:
        Vector<double, 2> _value;
    };
    typedef std::shared_ptr<ConstantVectorField2> ConstantVectorField2Ptr;

    class ConstantVectorField2::Builder final
    {
    public:
        Builder &withValue(const Vector<double, 2> &value);

        ConstantVectorField2 build() const;

        ConstantVectorField2 makeShared() const;
    private:
        Vector<double, 2> _value{0,0};
    };
}

#endif