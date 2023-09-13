#ifndef INCLUDE_BIG_ARRAY_ACCESOR1_H_
#define INCLUDE_BIG_ARRAY_ACCESOR1_H_
#include <array_accessor.h>

#include <utility> // std::move

namespace big
{

  template <typename T>
  class ArrayAccessor<T, 1> final
  {
  public:
    ArrayAccessor();

    ArrayAccessor(std::size_t size, T *const data); // no check for size > 0

    ArrayAccessor(const ArrayAccessor &other);

    void reset(std::size_t size, T *const data);

    void set(const ArrayAccessor &other);

    T &at(std::size_t i);

    const T &at(std::size_t i) const;

    T *begin();

    T *end();

    const T *begin() const;

    const T *end() const;

    std::size_t size() const;

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

    T &operator[](std::size_t i);

    const T &operator[](std::size_t i) const;

    ArrayAccessor &operator=(const ArrayAccessor &other);

    explicit operator ConstArrayAccessor<T, 1>() const;

  private:
    std::size_t _size;
    T *_data;
  };

  template <typename T>
  using ArrayAccessor1 = ArrayAccessor<T, 1>;

  template <typename T>
  class ConstArrayAccessor<T, 1>
  {
  public:
    ConstArrayAccessor();

    ConstArrayAccessor(std::size_t size, const T *const data);

    explicit ConstArrayAccessor(const ConstArrayAccessor &other);

    const T &at(std::size_t i) const;

    const T *begin() const;

    const T *end() const;

    std::size_t size() const;

    const T *const data() const;

    template <typename Callback>
    void forEach(Callback func) const;

    template <typename Callback>
    void forEachIndex(Callback func) const;

    const T &operator[](std::size_t i) const;

  private:
    std::size_t _size;
    const T *_data;
  };

  template <typename T>
  using ConstArrayAccessor1 = ConstArrayAccessor<T, 1>;

} // namespace big
#include "detail/array_accessor1-inl.h"
#endif