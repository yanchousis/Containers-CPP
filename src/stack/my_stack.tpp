#include "my_stack.h"

namespace my {

template <typename T>
stack<T>::stack() noexcept {
  this->n = 0;
  this->array = nullptr;
}

template <typename T>
stack<T>::~stack() {
  free();
}

template <typename T>
stack<T>::stack(std::initializer_list<T> const &items) noexcept {
  this->allocate(items.size());
  int i = 0;
  for (auto elem : items) {
    this->array[i++] = elem;
  }
}

template <typename T>
stack<T>::stack(const stack &s) noexcept {
  this->allocate(s.n);
  for (int i = 0; i < n; ++i) {
    this->array[i] = s.array[i];
  }
}

template <typename T>
stack<T>::stack(stack &&s) noexcept : n(s.n), array(s.array) {
  s.array = nullptr;
  s.n = 0;
}

template <typename T>
stack<T> &stack<T>::operator=(stack &&s) noexcept {
  this->free();
  this->array = s.array;
  this->n = s.n;
  s.array = nullptr;
  s.n = 0;
  return *this;
}

template <typename T>
bool stack<T>::empty() const {
  return (this->array == nullptr);
}

template <typename T>
typename stack<T>::size_type stack<T>::size() {
  return this->n;
}

template <typename T>
void stack<T>::swap(stack &new_arr) {
  value_type *copy = new_arr.array;
  int n_ = new_arr.n;
  new_arr.n = this->n;
  new_arr.array = this->array;
  this->n = n_;
  this->array = copy;
}

template <typename T>
void stack<T>::pop() {
  if (!this->empty()) {
    stack<T> copy;
    copy.allocate(n - 1);
    for (int i = 0; i < copy.n; ++i) {
      copy.array[i] = this->array[i];
    }
    this->free();
    n = copy.n;
    allocate(n);
    for (int i = 0; i < n; ++i) {
      this->array[i] = copy.array[i];
    }
  } else {
    throw std::logic_error("error");
  }
}

template <typename T>
void stack<T>::push(const_reference k) {
  if (this->n != 0) {
    stack<T> copy;
    copy.allocate(n + 1);
    for (int i = 0; i < copy.n - 1; ++i) {
      copy.array[i] = this->array[i];
    }
    copy.array[copy.size() - 1] = k;
    this->free();

    this->allocate(copy.n);
    for (int i = 0; i < this->n; ++i) {
      this->array[i] = copy.array[i];
    }

  } else {
    this->allocate(1);
    this->array[0] = k;
  }
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() {
  if (n == 0) {
    throw std::logic_error("error");
  }
  return array[n - 1];
}

template <typename T>
void stack<T>::allocate(int n) {
  this->n = n;
  this->array = new T[n];
  fill(0, 0);
}

template <typename T>
void stack<T>::free() {
  delete[] array;
  n = 0;
}

template <typename T>
void stack<T>::fill(int k, int q) {
  for (int i = 0; i < n; ++i) {
    array[i] = k;
    k += q;
  }
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_back(Args &&...args) {
  ((this->push(std::forward<Args>(args))), ...);
}
}  // namespace my