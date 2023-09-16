#ifndef INCLUDE_BIG_ARRAY_ACCESOR2_H_
#define INCLUDE_BIG_ARRAY_ACCESOR2_H_
#include <array_accessor.h>
#include <size2.h>
#include <point2.h>
#include <utility> // std::move

namespace big
{

    template <typename T>
    class ArrayAccessor<T, 2> final
    {
    public:
        constexpr ArrayAccessor() : _size(0, 0), _data(nullptr){};

        ArrayAccessor(Size2 size, T *const data); // no check for size > 0

        ArrayAccessor(std::size_t width, std::size_t height, T *const data);

        ArrayAccessor(const ArrayAccessor &other);

        void reset(Size2 size, T *const data);

        void reset(std::size_t width, std::size_t height, T *const data);

        void set(const ArrayAccessor &other);

        T &at(std::size_t i);

        const T &at(std::size_t i) const;

        T &at(std::size_t i, std::size_t j);

        const T &at(std::size_t i, std::size_t j) const;

        T &at(const Point2UI &pt);

        const T &at(const Point2UI &pt) const;        

        T *begin();

        T *end();

        const T *begin() const;

        const T *end() const;

        T width() const;

        T height() const; 

        Size2 size() const;

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

        std::size_t index(std::size_t i, std::size_t j) const;

        std::size_t index(const Point2UI &pt) const;

        T &operator[](std::size_t i);

        const T &operator[](std::size_t i) const;

        T &operator()(std::size_t i, std::size_t j);

        const T &operator()(std::size_t i, std::size_t j) const;

        T &operator()(const Point2UI &pt);

        const T &operator()(const Point2UI &pt) const;

        ArrayAccessor &operator=(const ArrayAccessor &other);

        explicit operator ConstArrayAccessor<T, 2>() const;

    private:
        Size2 _size;
        T *_data;
    };

    template <typename T>
    using ArrayAccessor2 = ArrayAccessor<T, 2>;

    template <typename T>
    class ConstArrayAccessor<T, 2>
    {
    public:
        ConstArrayAccessor();

        ConstArrayAccessor(const Size2 &size, const T *const data);

        ConstArrayAccessor(std::size_t width, std::size_t height, T *const data);

        explicit ConstArrayAccessor(const ArrayAccessor<T, 2> &other);

        ConstArrayAccessor(const ConstArrayAccessor &other);

         const T &at(std::size_t i) const;

        const T &at(std::size_t i, std::size_t j) const;

        const T &at(const Point2UI &pt) const;

        const T *begin() const;

        const T *end() const;

        Size2 size() const;

        std::size_t width() const;

        std::size_t height() const;

        const T *const data() const;

        template <typename Callback>
        void forEach(Callback func) const;

        template <typename Callback>
        void forEachIndex(Callback func) const;

        std::size_t index(std::size_t i, std::size_t j) const;

        std::size_t index(const Point2UI &pt) const;

        const T &operator[](std::size_t i) const;

        const T &operator()(std::size_t i, std::size_t j) const;

        const T &operator()(const Point2UI &pt) const;

    private:
        Size2 _size;
        const T *_data;
    };

    template <typename T>
    using ConstArrayAccessor2 = ConstArrayAccessor<T, 2>;

} // namespace big

#include "detail/array_accessor2-inl.h"
#endif