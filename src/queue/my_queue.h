#ifndef MY_QUEUE_H_
#define MY_QUEUE_H_

#include <initializer_list>
#include <stdexcept>

namespace my {

template <typename T>
class queue {
 public:
  using size_type = size_t;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

 private:
  size_type n;
  T *array;

 public:
  queue();

  queue(std::initializer_list<value_type> const &items);

  queue(const queue &v);

  queue(queue &&v) noexcept;

  ~queue();

  queue &operator=(queue &&v) noexcept;

  queue &operator=(queue &v) noexcept;

  const_reference front();

  const_reference back();

  bool empty() const noexcept;

  size_type size();

  void push(const T &k);

  void pop();

  void swap(queue &new_arr) noexcept;

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  void allocate(int n);

  void free();

  void fill(int k, int q);
};

}  // namespace my

#endif  // my_QUEUE_H_