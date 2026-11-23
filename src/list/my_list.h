#ifndef MY_LIST_H_
#define MY_LIST_H_

#include <initializer_list>
#include <stdexcept>

namespace my {

template <typename T>
struct DataNode {
  DataNode<T> *prev_ptr = nullptr;
  DataNode<T> *next_ptr = nullptr;
  T value;

  DataNode() : value() {}
  explicit DataNode(const T &v) : value(v) {}
};

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  DataNode<T> *ptr_first_node = nullptr;
  DataNode<T> *ptr_last_node = nullptr;
  size_t n = 0;

 public:
  template <bool IsConst>
  class ListIterator {
   public:
    using reference = std::conditional_t<IsConst, const T &, T &>;
    using pointer = std::conditional_t<IsConst, const T *, T *>;

    explicit ListIterator(DataNode<T> *node) : current(node) {}

    template <bool OtherIsConst,
              typename = std::enable_if_t<IsConst || !OtherIsConst>>
    ListIterator(const ListIterator<OtherIsConst> &other)
        : current(other.current) {}

    bool operator==(const ListIterator &other) const {
      return current == other.current;
    }
    bool operator!=(const ListIterator &other) const {
      return !(*this == other);
    }

    ListIterator &operator++() {
      if (current) current = current->next_ptr;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    ListIterator &operator--() {
      if (current) current = current->prev_ptr;
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator tmp(*this);
      --(*this);
      return tmp;
    }

    reference operator*() const { return current->value; }
    pointer operator->() const { return &current->value; }

   private:
    DataNode<T> *current;

    template <bool B>
    friend class ListIterator;

    friend class list<T>;
  };

  using iterator = ListIterator<false>;
  using const_iterator = ListIterator<true>;

  list() noexcept;

  list(size_type n_) noexcept;

  list(std::initializer_list<value_type> const &items) noexcept;

  list(const list &l) noexcept;

  list(list &&l) noexcept;

  ~list();

  list &operator=(std::initializer_list<value_type> const &items) noexcept;

  list &operator=(const list &l) noexcept;

  list &operator=(list &&l) noexcept;

  bool operator==(const list &l) const noexcept;

  reference front() const;

  reference back() const;

  bool empty() const;

  size_type size() const;

  size_type max_size();

  void clear();

  iterator insert(iterator pos, const T &value);

  void erase(iterator pos);

  void push_back(const_reference val);

  void pop_back();

  void pop_front();

  void push_front(const_reference data);

  void swap(list &new_arr) noexcept;

  void merge(list &other) noexcept;

  void splice(const_iterator pos, list &other);

  void reverse();

  void unique();

  void sort();

  iterator begin();

  iterator end();

  const_iterator begin() const;

  const_iterator end() const;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  void allocate(int n);

  void free();

  void fill(int k, int q);

  static DataNode<T> *merge_node(DataNode<T> *first, DataNode<T> *second);

  static std::pair<DataNode<T> *, DataNode<T> *> split(DataNode<T> *head);

  static DataNode<T> *split_and_merge(DataNode<T> *head);
};

}  // namespace my

#endif  // my_LIST_H_