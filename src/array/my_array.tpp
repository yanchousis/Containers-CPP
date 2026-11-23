#include "my_array.h"

namespace my {

template <typename T, size_t N>
array<T, N>::array() : size_(N) {}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) : array() {
  for (size_type i = 0; i < items.size(); ++i) {
    arr[i] = *(items.begin() + i);
  }
}

template <typename T, size_t N>
array<T, N>::array(const array &a) {
  size_ = a.size_;
  for (size_type i = 0; i < a.size_; ++i) {
    this->arr[i] = a.arr[i];
  }
}

template <typename T, size_t N>
array<T, N>::array(array &&a) : size_(a.size_), arr{} {
  for (size_type i = 0; i < a.size_; ++i) {
    this->arr[i] = std::move(a.arr[i]);
  }
}

template <typename T, size_t N>
array<T, N>::~array() {}

template <typename T, size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  size_ = a.size_;
  for (size_type i = 0; i < a.size_; ++i) {
    this->arr[i] = std::move(a.arr[i]);
  }
  return *this;
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return arr[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("error");
  }
  return arr[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return arr[0];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return arr[size_ - 1];
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return arr;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return arr;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return (arr + size_);
}

template <typename T, size_t N>
bool array<T, N>::empty() {
  if (size_ == 0) {
    return true;
  }
  return false;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return size_;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return size();
}

template <typename T, size_t N>
void array<T, N>::swap(array &other) {
  T copy[other.size_];

  for (size_type i = 0; i < other.size_; ++i) {
    copy[i] = other.arr[i];
  }

  for (size_type i = 0; i < other.size_; ++i) {
    other.arr[i] = this->arr[i];
  }

  for (size_type i = 0; i < other.size_; ++i) {
    this->arr[i] = copy[i];
  }
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) {
    arr[i] = value;
  }
}
}  // namespace my