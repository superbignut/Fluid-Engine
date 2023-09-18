#ifndef INCLUDE_BIG_VECTOR_EXPRESSION_INL_H_
#define INCLUDE_BIG_VECTOR_EXPRESSION_INL_H_

namespace big {

    template <typename T, typename E>
    std::size_t VectorExpression<T, E>::size()
    {
        return static_cast<const E&>(*this).size();
    }
    




}  // namespace big

#endif