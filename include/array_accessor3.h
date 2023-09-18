#ifndef INCLUDE_BIG_ARRAY_ACCESOR3_H_
#define INCLUDE_BIG_ARRAY_ACCESOR3_H_
#include <array_accessor.h>
#include <size3.h>
#include <point3.h>
#include <utility> // std::move

namespace big
{

    template <typename T>
    class ArrayAccessor<T, 3> final
    {
    public:
        constexpr ArrayAccessor() : _size(0, 0, 0), _data(nullptr){};

        ArrayAccessor(Size3 size, T *const data); // no check for size > 0

        ArrayAccessor(std::size_t width, std::size_t height, std::size_t depth, T *const data);

        ArrayAccessor(const ArrayAccessor &other);

        void reset(Size3 size, T *const data);

        void reset(std::size_t width, std::size_t height,std::size_t depth, T *const data);

        void set(const ArrayAccessor &other);

        T &at(std::size_t i);

        const T &at(std::size_t i) const;

        T &at(std::size_t i, std::size_t j, std::size_t k);

        const T &at(std::size_t i, std::size_t j, std::size_t k) const;

        T &at(const Point3UI &pt);

        const T &at(const Point3UI &pt) const;        

        T *begin();

        T *end();

        const T *begin() const;

        const T *end() const;

        T width() const;

        T height() const; 
        
        T depth() const;

        Size3 size() const;

        T *const data() const;

        void swap(ArrayAccessor &other);

        template <typename Callback>
        void forEach(Callback func) const;

        template <typename Callback>
        void forEachIndex(Callback func) const;

        template <typename Callback>
        void parallelForEach(Callback func) const;

        template <typename Callback>
        void parallelForEachIndex(Callback func) const;

        std::size_t index(std::size_t i, std::size_t j, std::size_t k) const;

        std::size_t index(const Point3UI &pt) const;

        T &operator[](std::size_t i);

        const T &operator[](std::size_t i) const;

        T &operator()(std::size_t i, std::size_t j);

        const T &operator()(std::size_t i, std::size_t j, std::size_t k) const;

        T &operator()(const Point3UI &pt);

        const T &operator()(const Point3UI &pt) const;

        ArrayAccessor &operator=(const ArrayAccessor &other);

        explicit operator ConstArrayAccessor<T, 3>() const;

    private:
        Size3 _size;
        T *_data;
    };

    template <typename T>
    using ArrayAccessor3 = ArrayAccessor<T, 3>;

    template <typename T>
    class ConstArrayAccessor<T, 3>
    {
    public:
        ConstArrayAccessor();

        ConstArrayAccessor(const Size3 &size, const T *const data);

        ConstArrayAccessor(std::size_t width, std::size_t height, T *const data);

        explicit ConstArrayAccessor(const ArrayAccessor<T, 3> &other);

        ConstArrayAccessor(const ConstArrayAccessor &other);

         const T &at(std::size_t i) const;

        const T &at(std::size_t i, std::size_t j, std::size_t k) const;

        const T &at(const Point3UI &pt) const;

        const T *begin() const;

        const T *end() const;

        Size3 size() const;

        std::size_t width() const;

        std::size_t height() const;

        std::size_t depth() const;

        const T *const data() const;

        template <typename Callback>
        void forEach(Callback func) const;

        template <typename Callback>
        void forEachIndex(Callback func) const;

        std::size_t index(std::size_t i, std::size_t j, std::size_t k) const;

        std::size_t index(const Point3UI &pt) const;

        const T &operator[](std::size_t i) const;

        const T &operator()(std::size_t i, std::size_t j, std::size_t k) const;

        const T &operator()(const Point3UI &pt) const;

    private:
        Size3 _size;
        const T *_data;
    };

    template <typename T>
    using ConstArrayAccessor3 = ConstArrayAccessor<T, 3>;

} // namespace big

#include "detail/array_accessor3-inl.h"
#endif