#ifndef MY_STACK_H_
#define MY_STACK_H_

#include <initializer_list>
#include <stdexcept>

namespace my {

template <typename T>
class stack {
 public:
  using value_type = T;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;

 private:
  int n;
  T *array;

 public:
  stack() noexcept;

  stack(std::initializer_list<value_type> const &items) noexcept;

  stack(const stack &s) noexcept;

  stack(stack &&s) noexcept;

  ~stack();

  stack &operator=(stack &&s) noexcept;

  const_reference top();

  bool empty() const;

  size_type size();

  void push(const_reference k);

  void pop();

  void swap(stack &new_arr);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  void allocate(int n);

  void free();

  void fill(int k, int q);
};

}  // namespace my

#endif  // my_STACK_H_