#ifndef INCLUDE_BIG_VECTOR_INL_H_
#define INCLUDE_BIG_VECTOR_INL_H_
#include <stddef.h>

namespace big
{

    template <typename T, std::size_t N>
    Vector<T, N>::Vector()
    {
        // for (auto &elem : _elements)
        // {
        //     elem = static_cast<T>(0);
        // }
        _elements.fill(0);
    }

    template <typename T, std::size_t N>
    template <typename... Params>
    Vector<T, N>::Vector(Params... params)
    {
        static_assert(sizeof...(params) == N, "Invalid number of params.");
        setAt(0, params);
    }

    template <typename T, std::size_t N>
    template <typename U>
    Vector<T, N>::Vector(std::initializer_list<U> &lst)
    {
        set(lst);
    }

    template <typename T, std::size_t N>
    template <typename U>
    void Vector<T, N>::set(std::initializer_list<U> &lst)
    {
        static_assert(lst.size() == N, "lst's size is Invalid.");
        std::size_t i = 0;

        for (const auto &ele : lst)
        {
            _elements[i] = static_cast<T>(ele);
            ++i;
        }
    }

    template <typename T, std::size_t N>
    void Vector<T, N>::set(const T &s)
    {
        _elements.fill(s);
    }

    template <typename T, std::size_t N>
    template <typename E>
    Vector<T, N>::Vector(const VectorExpression<T, E> &other)
    {
        set(other);
    }

    template <typename T, std::size_t N>
    template <typename E>
    void Vector<T, N>::set(const VectorExpression<T, E> &other)
    {
        assert(N == other.size());
        const E &expression = other();
    }

    template <typename T, std::size_t N>
    constexpr std::size_t Vector<T, N>::size() const
    {
        return N;
    }

    template <typename T, std::size_t N>
    Vector<T, N>::Vector(const Vector &other) : _elements(other._elements) {}

    template <typename T, std::size_t N>
    void Vector<T, N>::swap(Vector &other)
    {
        std::swap(_elements, other._elements);
    }

    template <typename T, std::size_t N>
    void Vector<T, N>::setZero()
    {
        _elements.fill(0);
    }

    template <typename T, std::size_t N>
    void Vector<T, N>::normalize()
    {
    }

    template <typename T, std::size_t N>
    T *Vector<T, N>::data()
    {
        return _elements.data();
    }

    template <typename T, std::size_t N>
    const T *const Vector<T, N>::data() const
    {
        return _elements.data();
    }

    template <typename T, std::size_t N>
    typename Vector<T, N>::ContainerType::iterator Vector<T, N>::begin()
    {
        return _elements.begin();
    }

    template <typename T, std::size_t N>
    typename Vector<T, N>::ContainerType::const_iterator Vector<T, N>::begin() const
    {
        return _elements.cbegin();
    }

    template <typename T, std::size_t N>
    typename Vector<T, N>::ContainerType::iterator Vector<T, N>::begin()
    {
        return _elements.end();
    }

    template <typename T, std::size_t N>
    typename Vector<T, N>::ContainerType::const_iterator Vector<T, N>::begin() const
    {
        return _elements.cend();
    }

    template <typename T, std::size_t N>
    ArrayAccessor<T, 1> Vector<T, N>::accessor()
    {
        return ArrayAccessor<T, 1>(size(), data());
    }

    template <typename T, std::size_t N>
    ConstArrayAccessor<T, 1> Vector<T, N>::ConstAccessor() const
    {
        return ConstArrayAccessor<T, 1>(size(), data());
    }

    template <typename T, std::size_t N>
    T &Vector<T, N>::at(std::size_t i)
    {
        return _elements[i];
    }

    template <typename T, std::size_t N>
    const T &Vector<T, N>::at(std::size_t i) const
    {
        return _elements[i];
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::sum() const
    {
        T sum = 0;

        for (auto &ele : _elements)
            sum += ele;

        return sum;
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::avg() const
    {
        return sum() / N;
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::min() const
    {
        T temp = *_elements.data();

        for (auto &ele : _elements)
        {
            temp = std::min(temp, ele)
        }
        return temp;
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::max() const
    {
        T temp = *_elements.data();

        for (auto &ele : _elements)
        {
            temp = std::max(temp, ele)
        }
        return temp;
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::absmin() const
    {
        T temp = *_elements.data();

        for (auto &ele : _elements)
        {
            temp = absmin(temp, ele);
        }
        return temp;
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::absmax() const
    {
        T temp = *_elements.data();

        for (auto &ele : _elements)
        {
            temp = absmax(temp, ele);
        }
        return temp;
    }

    template <typename T, std::size_t N>
    std::size_t Vector<T, N>::dominantAxis() const
    {
        auto iter = std::max_element(begin(), end(), [](const T &a, const T &b)
                                     { return std::fabs(a) < std::fabs(b); });
        return iter - begin();
    }

    template <typename T, std::size_t N>
    std::size_t Vector<T, N>::subminantAxis() const
    {
        auto iter = std::max_element(begin(), end(), [](const T &a, const T &b)
                                     { return std::fabs(a) > std::fabs(b); });
        return iter - begin();
    }

    template <typename T, std::size_t N>
    VectorScalarDiv<T, Vector<T, N>> Vector<T, N>::normalized() const
    {
        return VectorScalarDiv<T, Vector>(*this, length());
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::length() const
    {

        return std::sqrt(lengthSquared());
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::lengthSquared() const
    {

        return dot(*this);
    }

    template <typename T, std::size_t N>
    template <typename E>
    T Vector<T, N>::dot(const E &v) const
    {
        assert(size() == v.size());
        T sum = 0;
        for (std::size_t i = 0; i < N; ++i)
        {
            sum += _elements[i] * v[i];
        }
        return sum;
    }

    template <typename T, std::size_t N>
    template <typename... Params>
    void Vector<T, N>::setAt(std::size_t i, T v, Params... params)
    {
        _elements[i] = v;
        setAt(i + 1, params);
    }

    template <typename T, std::size_t N>
    void Vector<T, N>::setAt(std::size_t i, T v)
    {
        _elements[i] = v;
    }

} // namespace big

#endif