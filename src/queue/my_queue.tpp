#include "my_queue.h"

namespace my {

template <typename T>
queue<T>::queue() {
  n = 0;
  array = nullptr;
}

template <typename T>
queue<T>::queue(std::initializer_list<T> const &items) {
  this->allocate(items.size());
  int i = 0;
  for (auto it = items.begin(); it != items.end(); ++it) {
    this->array[i++] = *it;
  }
}

template <typename T>
queue<T>::queue(const queue &v) {
  this->allocate(v.n);
  for (size_type i = 0; i < n; ++i) {
    this->array[i] = v.array[i];
  }
}

template <typename T>
queue<T>::queue(queue &&v) noexcept : n(v.n), array(v.array) {
  v.array = nullptr;
  v.n = 0;
}

template <typename T>
queue<T>::~queue() {
  this->free();
}

template <typename T>
queue<T> &queue<T>::operator=(queue &&v) noexcept {
  this->free();
  n = v.n;
  array = v.array;
  v.array = nullptr;
  v.n = 0;
  return *this;
}

template <typename T>
queue<T> &queue<T>::operator=(queue &v) noexcept {
  this->free();
  allocate(v.n);
  for (size_type i = 0; i < n; ++i) {
    this->array[i] = v.array[i];
  }
  return *this;
}

template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return n;
}

template <typename T>
bool queue<T>::empty() const noexcept {
  return (array == nullptr);
}

template <typename T>
void queue<T>::push(const T &k) {
  if (this->n != 0) {
    queue<T> copy;
    copy.allocate(n + 1);
    for (size_type i = 0; i < copy.n - 1; ++i) {
      copy.array[i] = this->array[i];
    }
    copy.array[copy.size() - 1] = k;
    this->free();
    this->allocate(copy.n);
    for (size_type i = 0; i < this->n; ++i) {
      this->array[i] = copy.array[i];
    }
  } else {
    this->allocate(1);
    this->array[0] = k;
  }
}

template <typename T>
void queue<T>::pop() {
  if (!this->empty()) {
    queue<T> copy;
    copy.allocate(n - 1);
    int j = 0;
    for (size_type i = 1; i < this->n; ++i) {
      copy.array[j++] = this->array[i];
    }
    this->free();
    allocate(copy.n);
    for (size_type i = 0; i < n; ++i) {
      this->array[i] = copy.array[i];
    }
  } else {
    throw std::logic_error("error");
  }
}

template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  if (n == 0) {
    throw std::logic_error("error");
  }
  return array[0];
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  if (n == 0) {
    throw std::logic_error("error");
  }
  return array[n - 1];
}

template <typename T>
void queue<T>::swap(queue &new_arr) noexcept {
  T *copy = new_arr.array;
  size_type n_ = new_arr.n;
  new_arr.n = this->n;
  new_arr.array = this->array;
  this->n = n_;
  this->array = copy;
}

template <typename T>
void queue<T>::allocate(int _n) {
  this->n = _n;
  this->array = new T[_n];
  fill(0, 0);
}

template <typename T>
void queue<T>::free() {
  if (array != nullptr) {
    delete[] array;
  }
  n = 0;
}

template <typename T>
void queue<T>::fill(int k, int q) {
  for (size_type i = 0; i < n; ++i) {
    array[i] = k;
    k += q;
  }
}

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  ((this->push(std::forward<Args>(args))), ...);
}

}  // namespace my