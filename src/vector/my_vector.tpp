#ifndef MY_VECTOR_TPP_
#define MY_VECTOR_TPP_
#include "my_vector.h"

namespace my {

template <typename T>
vector<T>::vector(size_type n_) : n(n_) {
  capacity_ = n_;
  this->allocate(n);
}

template <typename T>
vector<T>::vector(std::initializer_list<T> const& items) {
  this->allocate(items.size());
  this->capacity_ = items.size();
  int i = 0;
  for (auto elem : items) {
    this->array[i] = elem;
    ++i;
  }
}

template <typename T>
vector<T>::vector(const vector<T>& v) {
  this->allocate(v.n);
  this->capacity_ = v.capacity_;
  for (size_type i = 0; i < n; ++i) {
    this->array[i] = v.array[i];
  }
}

template <typename T>
vector<T>::vector(vector&& v) noexcept
    : n(v.n), capacity_(v.capacity_), array(v.array) {
  v.array = nullptr;
  v.n = 0;
  v.capacity_ = 0;
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& v) noexcept {
  this->free();

  this->array = v.array;
  this->n = v.n;
  this->capacity_ = v.capacity_;

  v.array = nullptr;
  v.capacity_ = 0;
  v.n = 0;

  return *this;
}

template <typename T>
T& vector<T>::operator[](size_type pos) {
  return array[pos];
}

template <typename T>
vector<T>::~vector() {
  free();
}

template <typename T>
void vector<T>::allocate(size_type n) {
  this->n = n;
  this->array = new T[n];
  //  fill(0, 0);
}

template <typename T>
void vector<T>::free() {
  delete[] array;
  n = 0;
  capacity_ = 0;
}

template <typename T>
void vector<T>::fill(value_type k, int q) {
  for (size_type i = 0; i < n; ++i) {
    array[i] = k;
    k += q;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return n;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
}

template <typename T>
void vector<T>::clear() {
  this->n = 0;
}

template <typename T>
bool vector<T>::empty() const noexcept {
  return (this->n == 0);
}

template <typename T>
void vector<T>::pop_back() {
  if (!this->empty()) {
    --this->n;
  }
}

template <typename T>
T* vector<T>::data() {
  return (&array[0]);
}

template <typename T>
void vector<T>::push_back(const T& k) {
  if (this->n != 0) {
    if (capacity_ >= (n + 1)) {
      this->n++;
      array[n - 1] = k;
    } else {
      vector copy(n + 1);
      for (size_type i = 0; i < copy.n - 1; ++i) {
        copy.array[i] = this->array[i];
      }
      copy.array[copy.size() - 1] = k;
      this->free();

      this->allocate(copy.n);
      for (size_type i = 0; i < this->n; ++i) {
        this->array[i] = copy.array[i];
      }
    }
  } else {
    this->allocate(1);
    this->array[0] = k;
  }
}

template <typename T>
T* vector<T>::begin() {
  return &array[0];
}

template <typename T>
T* vector<T>::end() {
  return array + n;
}

template <typename T>
const T& vector<T>::front() {
  return array[0];
}

template <typename T>
const T& vector<T>::back() {
  return array[n - 1];
}

template <typename T>
void vector<T>::swap(vector& new_arr) noexcept {
  T* copy = new_arr.array;
  size_type n_ = new_arr.n;
  size_type capa = new_arr.capacity_;

  new_arr.n = this->n;
  new_arr.array = this->array;
  new_arr.capacity_ = this->capacity_;

  this->n = n_;
  this->array = copy;
  this->capacity_ = capa;

  copy = nullptr;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (this->n < this->capacity_) {
    size_type k = n;
    T* copy = new T[n];
    for (size_type i = 0; i < n; ++i) {
      copy[i] = this->array[i];
    }
    this->free();

    this->array = copy;
    this->n = k;
    this->capacity_ = k;

    copy = nullptr;
  }
}

template <typename T>
void vector<T>::erase(T* pos) {
  size_type start = (pos - this->begin());
  vector tmp(n - 1);
  size_type j = 0;
  for (size_type i = 0; i < this->n; ++i) {
    if (i != start) {
      tmp.array[j++] = this->array[i];
    }
  }
  this->free();
  this->allocate(tmp.n);
  for (size_type i = 0; i < n; ++i) {
    array[i] = tmp.array[i];
  }
}

template <typename T>
T* vector<T>::insert(const T* position, const T& value) {
  size_type pos = (position - this->begin());
  vector tmp(n + 1);

  size_type i = 0;
  size_type j = 0;
  tmp.array[pos] = value;

  while (i < n) {
    if (j == pos) {
      ++j;
    }
    tmp.array[j] = this->array[i];
    ++i;
    ++j;
  }

  if (capacity_ >= n + 1) {
    for (size_type i = 0; i < n + 1; ++i) {
      array[i] = tmp.array[i];
    }

    this->n = n + 1;

  } else {
    this->free();
    this->array = tmp.array;
    this->n = n + 1;
    this->capacity_ = this->n;
    tmp.array = nullptr;
    tmp.n = 0;
    tmp.capacity_ = 0;
  }
  return (array + pos);
}

template <typename T>
T& vector<T>::at(size_type pos) {
  if (pos >= this->size()) {
    throw std::out_of_range("error");
  }
  return array[pos];
}

template <typename T>
void vector<T>::allocate_capacity(size_type size) {
  if (this->n == 0) {
    this->array = new T[size];
    this->capacity_ = size;
  } else if (this->n < size) {
    T* copy = new T[size];
    for (size_type i = 0; i < this->n; ++i) {
      copy[i] = this->array[i];
    }
    delete[] this->array;
    this->array = copy;
    this->capacity_ = size;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return this->capacity_;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  allocate_capacity(size);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  size_type pos_index = pos - begin();
  size_type count = sizeof...(args);

  T values[] = {std::forward<Args>(args)...};

  if (n + count > capacity_) {
    size_type new_capacity = capacity_;
    while (new_capacity < n + count) {
      new_capacity = (new_capacity == 0) ? 1 : new_capacity * 2;
    }
    allocate_capacity(new_capacity);
  }

  for (size_type i = n; i > pos_index; --i) {
    array[i + count - 1] = array[i - 1];
  }

  for (size_type i = 0; i < count; ++i) {
    array[pos_index + i] = values[i];
  }

  n += count;

  return begin() + pos_index;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  (push_back(std::forward<Args>(args)), ...);
}

}  // namespace my

#endif  // my_VECTOR_TPP_