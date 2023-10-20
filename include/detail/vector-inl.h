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
        setAt(0, params...);
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
    void Vector<T, N>::set(const VectorExpression<T, E> &other) // other can be VectorExpression and his son.
    {
        assert(size() == other.size()); // call VectorExpression's size() const

        const E &expression = other(); // call ()(), return CRTP's son class

        forEachIndex([&](std::size_t i)
                     { _elements[i] = expression[i]; });
    }

    template <typename T, std::size_t N>
    constexpr std::size_t Vector<T, N>::size() const
    {
        // std::cout << "son size\n"
        //   << std::endl;
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
        idiv(length());
    }

    template <typename T, std::size_t N>
    template <typename E>
    VectorAdd<T, Vector<T, N>, E> Vector<T, N>::add(const E &v) const
    {
        return VectorAdd<T, Vector, E>(*this, v);
    }

    template <typename T, std::size_t N>
    VectorScalarAdd<T, Vector<T, N>> Vector<T, N>::add(const T &s) const
    {
        return VectorScalarAdd<T, Vector>(*this, s);
    }
    template <typename T, std::size_t N>
    template <typename E>
    VectorSub<T, Vector<T, N>, E> Vector<T, N>::sub(const E &v) const
    {
        return VectorSub<T, Vector, E>(*this, v);
    }

    template <typename T, std::size_t N>
    VectorScalarSub<T, Vector<T, N>> Vector<T, N>::sub(const T &s) const
    {
        return VectorScalarSub<T, Vector>(*this, s);
    }
    template <typename T, std::size_t N>
    template <typename E>
    VectorMul<T, Vector<T, N>, E> Vector<T, N>::mul(const E &v) const
    {
        return VectorMul<T, Vector, E>(*this, v);
    }

    template <typename T, std::size_t N>
    VectorScalarMul<T, Vector<T, N>> Vector<T, N>::mul(const T &s) const
    {
        return VectorScalarMul<T, Vector>(*this, s);
    }
    template <typename T, std::size_t N>
    template <typename E>
    VectorDiv<T, Vector<T, N>, E> Vector<T, N>::div(const E &v) const
    {
        return VectorDiv<T, Vector, E>(*this, v);
    }

    template <typename T, std::size_t N>
    VectorScalarDiv<T, Vector<T, N>> Vector<T, N>::div(const T &s) const
    {
        return VectorScalarDiv<T, Vector>(*this, s);
    }

    template <typename T, std::size_t N>
    template <typename E>
    VectorSub<T, Vector<T, N>, E> Vector<T, N>::rsub(const E &v) const
    {
        return VectorSub<T, Vector, E>(v, *this);
    }

    template <typename T, std::size_t N>
    VectorScalarRSub<T, Vector<T, N>> Vector<T, N>::rsub(const T &s) const
    {
        return VectorScalarRSub<T, Vector>(*this, s);
    }
    template <typename T, std::size_t N>
    template <typename E>
    VectorDiv<T, Vector<T, N>, E> Vector<T, N>::rdiv(const E &v) const
    {
        return VectorDiv<T, Vector, E>(v, *this);
    }

    template <typename T, std::size_t N>
    VectorScalarRDiv<T, Vector<T, N>> Vector<T, N>::rdiv(const T &s) const
    {
        return VectorScalarRDiv<T, Vector>(*this, s);
    }
    template <typename T, std::size_t N>
    void Vector<T, N>::iadd(const T &s)
    {
        set(add(s));
    }

    template <typename T, std::size_t N>
    template <typename E>
    void Vector<T, N>::iadd(const E &v)
    {
        set(add(v));
    }
    template <typename T, std::size_t N>
    void Vector<T, N>::isub(const T &s)
    {
        set(sub(s));
    }

    template <typename T, std::size_t N>
    template <typename E>
    void Vector<T, N>::isub(const E &v)
    {
        set(sub(v));
    }
    template <typename T, std::size_t N>
    void Vector<T, N>::imul(const T &s)
    {
        set(mul(s));
    }

    template <typename T, std::size_t N>
    template <typename E>
    void Vector<T, N>::imul(const E &v)
    {
        set(mul(v));
    }
    template <typename T, std::size_t N>
    void Vector<T, N>::idiv(const T &s)
    {
        set(div(s));
    }

    template <typename T, std::size_t N>
    template <typename E>
    void Vector<T, N>::idiv(const E &v)
    {
        set(div(v));
    }
    template <typename T, std::size_t N>
    T &Vector<T, N>::operator[](std::size_t i)
    {
        return _elements[i];
    }
    template <typename T, std::size_t N>
    const T &Vector<T, N>::operator[](std::size_t i) const
    {
        return _elements[i];
    }

    template <typename T, std::size_t N>
    template <typename E>
    Vector<T, N> &Vector<T, N>::operator=(const VectorExpression<T, E> &other)
    {
        set(other);
        return *this;
    }
    template <typename T, std::size_t N>
    template <typename U>
    Vector<T, N> &Vector<T, N>::operator=(const std::initializer_list<U> &lst)
    {
        set(lst);
        return *this;
    }
    template <typename T, std::size_t N>
    Vector<T, N> &Vector<T, N>::operator+=(T &val)
    {
        iadd(val);
        return *this;
    }
    template <typename T, std::size_t N>
    template <typename E>
    Vector<T, N> &Vector<T, N>::operator+=(const E &other)
    {
        iadd(other);
        return *this;
    }
    template <typename T, std::size_t N>
    Vector<T, N> &Vector<T, N>::operator-=(T &val)
    {
        isub(val);
        return *this;
    }
    template <typename T, std::size_t N>
    template <typename E>
    Vector<T, N> &Vector<T, N>::operator-=(const E &other)
    {
        isub(other);
        return *this;
    }
    template <typename T, std::size_t N>
    Vector<T, N> &Vector<T, N>::operator*=(T &val)
    {
        imul(val);
        return *this;
    }
    template <typename T, std::size_t N>
    template <typename E>
    Vector<T, N> &Vector<T, N>::operator*=(const E &other)
    {
        imul(other);
        return *this;
    }
    template <typename T, std::size_t N>
    Vector<T, N> &Vector<T, N>::operator/=(T &val)
    {
        idiv(val);
        return *this;
    }
    template <typename T, std::size_t N>
    template <typename E>
    Vector<T, N> &Vector<T, N>::operator/=(const E &other)
    {
        idiv(other);
        return *this;
    }

    template <typename T, std::size_t N>
    template <typename E>
    bool Vector<T, N>::operator==(const E &other) const
    {
        return isEqual(other);
    }
    template <typename T, std::size_t N>
    template <typename E>
    bool Vector<T, N>::operator!=(const E &other) const
    {
        return !isEqual(other);
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
    typename Vector<T, N>::ContainerType::iterator Vector<T, N>::end()
    {
        return _elements.end();
    }

    template <typename T, std::size_t N>
    typename Vector<T, N>::ContainerType::const_iterator Vector<T, N>::end() const
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
            temp = std::min(temp, ele);
        }
        return temp;
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::max() const
    {
        T temp = *_elements.data();

        for (auto &ele : _elements)
        {
            temp = std::max(temp, ele);
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
    Vector<T, N> Vector<T, N>::random()
    {
        Vector temp;
        for (std::size_t i = 0; i < N; ++i)
        {
            temp[i] = (i * 7 + 13) % 3 + 1;
        }
        return temp;
    }
    template <typename T, std::size_t N>
    void Vector<T, N>::show()
    {
        for(std::size_t i =0 ;i < N; ++i)
        {
            std::cout << at(i) << " ";
        }
        std::cout << std::endl;
    }

    template <typename T, std::size_t N>
    std::size_t Vector<T, N>::dominantAxis() const
    {
        auto iter = std::max_element(begin(), end(), [](const T &a, const T &b)
                                     { return fabs(a) < fabs(b); });
        return iter - begin();
    }

    template <typename T, std::size_t N>
    std::size_t Vector<T, N>::subminantAxis() const
    {
        auto iter = std::max_element(begin(), end(), [](const T &a, const T &b)
                                     { return fabs(a) > fabs(b); });
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

        return sqrt(lengthSquared());
    }

    template <typename T, std::size_t N>
    T Vector<T, N>::lengthSquared() const
    {

        return dot(*this);
    }

    template <typename T, std::size_t N>
    template <typename E>
    bool Vector<T, N>::isEqual(const E &other) const
    {
        if (size() != other.size())
            return false;
        for (std::size_t i = 0; i < N; ++i)
        {
            if (at(i) != other[i])
                return false;
        }
        return true;
    }

    template <typename T, std::size_t N>
    template <typename E>
    bool Vector<T, N>::isSimilar(const E &other, T epsilon) const
    {
        if (size() != other.size())
            return false;
        for (std::size_t i = 0; i < N; ++i)
        {
            if (std::abs(at(i) - other[i]) > epsilon)
                return false;
        }
        return true;
    }

    template <typename T, std::size_t N>
    template <typename E>
    T Vector<T, N>::distanceTo(const E &other) const
    {
        return sqrt(distanceSquaredTo(other));
    }

    template <typename T, std::size_t N>
    template <typename E>
    T Vector<T, N>::distanceSquaredTo(const E &other) const
    {
        T ret = 0;
        for (std::size_t i = 0; i < N; ++i)
        {
            T diff = at[i] - other[i];
            ret += diff * diff;
        }
        return ret;
    }
    template <typename T, std::size_t N>
    template <typename U>
    VectorTypeCast<U, Vector<T, N>, T> Vector<T, N>::castTo() const
    {
        return VectorTypeCast<U, Vector, T>(*this);
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
    template <typename Callback>
    void Vector<T, N>::forEach(Callback func) const
    {
        ConstAccessor().forEach(func);
    }

    template <typename T, std::size_t N>
    template <typename Callback>
    void Vector<T, N>::forEachIndex(Callback func) const
    {
        ConstAccessor().forEachIndex(func);
    }

    template <typename T, std::size_t N>
    template <typename... Params>
    void Vector<T, N>::setAt(std::size_t i, T v, Params... params)
    {
        _elements[i] = v;
        setAt(i + 1, params...);
    }

    template <typename T, std::size_t N>
    void Vector<T, N>::setAt(std::size_t i, T v)
    {
        _elements[i] = v;
    }

} // namespace big

#endif