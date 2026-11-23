#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <iostream>
#include <stdexcept>
#include <utility>

namespace my {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  size_type n;
  size_type capacity_;
  T *array;

 public:
  vector() : n(0) {
    this->array = nullptr;
    capacity_ = 0;
  }

  explicit vector(size_type n_);

  vector(std::initializer_list<T> const &items);

  vector(const vector &v);

  vector(vector &&v) noexcept;

  vector &operator=(vector &&v) noexcept;

  ~vector();

  reference at(size_type pos);

  reference operator[](size_type pos);

  const_reference front();

  const_reference back();

  iterator data();

  iterator begin();

  iterator end();

  bool empty() const noexcept;

  size_type size();

  size_type max_size();

  void reserve(size_type size);

  size_type capacity();

  void shrink_to_fit();

  void clear();

  iterator insert(const T *position, const T &value);

  void erase(T *pos);

  void push_back(const T &k);

  void pop_back();

  void swap(vector &new_arr) noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  void allocate(size_type n);

  void free();

  void fill(value_type k, int q);

  void allocate_capacity(size_type size);
};

}  // namespace my

#endif  // my_VECTOR_H_