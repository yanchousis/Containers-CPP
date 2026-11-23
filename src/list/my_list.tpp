#include "my_list.h"

namespace my {

template <typename T>
list<T>::list() noexcept {}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T>::list(size_t n_) noexcept : n(n_) {
  ptr_first_node = new DataNode<T>();
  DataNode<T> *current = ptr_first_node;
  for (size_t i = 1; i < n_; ++i) {
    current->next_ptr = new DataNode<T>();
    current->next_ptr->prev_ptr = current;
    current = current->next_ptr;
  }
  ptr_last_node = current;
}

template <typename T>
list<T>::list(const list<T> &l) noexcept {
  DataNode<T> *current = l.ptr_first_node;
  while (current != nullptr) {
    this->push_back(current->value);
    current = current->next_ptr;
  }
}

template <typename T>
list<T>::list(std::initializer_list<T> const &items) noexcept {
  n = 0;
  for (auto it = items.begin(); it != items.end(); ++it) {
    push_back(*it);
  }
}

template <typename T>
list<T>::list(list<T> &&l) noexcept {
  this->ptr_first_node = l.ptr_first_node;
  this->ptr_last_node = l.ptr_last_node;
  this->n = l.n;
  l.ptr_first_node = nullptr;
  l.ptr_last_node = nullptr;
  l.n = 0;
}

template <typename T>
list<T> &list<T>::operator=(std::initializer_list<T> const &items) noexcept {
  clear();
  this->n = 0;
  for (auto it = items.begin(); it != items.end(); ++it) {
    this->push_back(*it);
  }
  return *this;
}

// template <typename T>
// bool list<T>::operator==(const list<T> &l) noexcept {
//   if (this->ptr_first_node != l.ptr_first_node ||
//       this->ptr_last_node != l.ptr_last_node) {
//     return false;
//   }
//   return true;
// }

template <typename T>
bool list<T>::operator==(const list<T> &l) const noexcept {
  if (this->n != l.n) {
    return false;
  }

  auto it1 = this->begin();
  auto it2 = l.begin();

  while (it1 != this->end()) {
    if (*it1 != *it2) {
      return false;
    }
    ++it1;
    ++it2;
  }

  return true;
}

template <typename T>
list<T> &list<T>::operator=(const list<T> &l) noexcept {
  if (!((*this) == l)) {
    clear();
    for (auto it = l.begin(); it != l.end(); ++it) {
      this->push_back(*it);
    }
  }

  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&l) noexcept {
  if (this != &l) {
    clear();

    ptr_first_node = l.ptr_first_node;
    ptr_last_node = l.ptr_last_node;
    n = l.n;

    l.ptr_first_node = nullptr;
    l.ptr_last_node = nullptr;
    l.n = 0;
  }
  return *this;
}

template <typename T>
bool list<T>::empty() const {
  return (ptr_first_node == nullptr);
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return n;
}

template <typename T>
void list<T>::swap(list<T> &new_arr) noexcept {
  DataNode<T> *copy_ptr_first_node;
  DataNode<T> *copy_ptr_last_node;

  int copy_n = new_arr.n;
  copy_ptr_first_node = new_arr.ptr_first_node;
  copy_ptr_last_node = new_arr.ptr_last_node;

  new_arr.ptr_first_node = nullptr;
  new_arr.ptr_last_node = nullptr;
  new_arr.n = 0;

  new_arr.n = this->n;
  new_arr.ptr_first_node = this->ptr_first_node;
  new_arr.ptr_last_node = this->ptr_last_node;

  this->n = copy_n;
  this->ptr_first_node = copy_ptr_first_node;
  this->ptr_last_node = copy_ptr_last_node;
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <typename T>
void list<T>::push_back(const T &val) {
  DataNode<T> *new_node = new DataNode<T>(val);
  if (ptr_first_node == nullptr && ptr_last_node == nullptr) {
    ptr_first_node = new_node;
    ptr_last_node = new_node;

  } else {
    new_node->prev_ptr = ptr_last_node;
    ptr_last_node->next_ptr = new_node;
    ptr_last_node = new_node;
  }
  ++n;
}

template <typename T>
void list<T>::pop_back() {
  if (n == 1) {
    delete ptr_first_node;
    ptr_first_node = nullptr;
    ptr_last_node = nullptr;
    n = 0;
  } else if (n == 2) {
    delete ptr_last_node;
    ptr_last_node = ptr_first_node;
    --n;
  } else {
    DataNode<T> *ptr = ptr_last_node->prev_ptr;
    delete ptr_last_node;
    ptr_last_node = ptr;
    ptr_last_node->next_ptr = nullptr;
    --n;
  }
}

template <typename T>
void list<T>::pop_front() {
  if (n == 1) {
    delete ptr_first_node;
    ptr_first_node = nullptr;
    ptr_last_node = nullptr;
    n = 0;
  } else if (n == 2) {
    delete ptr_first_node;
    ptr_first_node = ptr_last_node;
    ptr_first_node->prev_ptr = nullptr;
    --n;
  } else {
    DataNode<T> *ptr = ptr_first_node->next_ptr;
    delete ptr_first_node;
    ptr_first_node = ptr;
    ptr_first_node->prev_ptr = nullptr;
    --n;
  }
}

template <typename T>
void list<T>::push_front(const T &data) {
  DataNode<T> *ptr = new DataNode<T>();
  ptr->value = data;
  if (ptr_first_node != nullptr) {
    ptr->prev_ptr = nullptr;
    ptr->next_ptr = ptr_first_node;
    ptr_first_node->prev_ptr = ptr;
    ptr_first_node = ptr;
  } else {
    ptr_first_node = ptr;
    ptr_last_node = ptr;
  }
  ++n;
}

template <typename T>
typename list<T>::reference list<T>::front() const {
  return ptr_first_node->value;
}

template <typename T>
typename list<T>::reference list<T>::back() const {
  return ptr_last_node->value;
}

template <typename T>
void list<T>::reverse() {
  DataNode<T> *next = ptr_first_node->next_ptr;
  DataNode<T> *prev = ptr_first_node->prev_ptr;
  ptr_first_node->prev_ptr = next;
  ptr_first_node->next_ptr = prev;
  DataNode<T> *current_node = ptr_first_node->prev_ptr;
  for (size_type i = 0; i < n - 1; ++i) {
    next = current_node->next_ptr;
    prev = current_node->prev_ptr;
    current_node->prev_ptr = next;
    current_node->next_ptr = prev;
    current_node = current_node->prev_ptr;
  }
  DataNode<T> *ptr = ptr_last_node;
  ptr_last_node = ptr_first_node;
  ptr_first_node = ptr;
}

template <typename T>
void list<T>::unique() {
  if (ptr_first_node == nullptr || ptr_first_node->next_ptr == nullptr) {
    return;
  }
  T val = ptr_first_node->value;
  DataNode<T> *current_node = ptr_first_node->next_ptr;
  DataNode<T> *next = current_node->next_ptr;
  DataNode<T> *prev = current_node->prev_ptr;
  int k = 0;

  while (current_node != nullptr && next != nullptr) {
    if (val == current_node->value) {
      delete current_node;
      prev->next_ptr = next;
      next->prev_ptr = prev;
      current_node = next;
      ++k;
    } else {
      if (current_node != nullptr) {
        val = current_node->value;
      }
      current_node = current_node->next_ptr;
    }

    next = current_node->next_ptr;
    prev = current_node->prev_ptr;
  }

  if (current_node != nullptr) {
    if (val == current_node->value) {
      prev->next_ptr = nullptr;
      ptr_last_node = prev;
      delete current_node;
      ++k;
    }
  }

  n -= k;
}

template <typename T>
void list<T>::merge(list<T> &other) noexcept {
  DataNode<T> *it_1 = this->ptr_first_node;
  DataNode<T> *it_2 = other.ptr_first_node;

  list<T> result;
  if (it_1 == nullptr) {
    this->ptr_first_node = other.ptr_first_node;
    this->ptr_last_node = other.ptr_last_node;
    this->n = other.n;
    other.ptr_first_node = nullptr;
    other.ptr_last_node = nullptr;
    other.n = 0;
  } else {
    while (it_1 != nullptr && it_2 != nullptr) {
      if (it_1->value > it_2->value) {
        result.push_back(it_2->value);
        it_2 = it_2->next_ptr;

      } else {
        result.push_back(it_1->value);
        it_1 = it_1->next_ptr;
      }

      if (it_2 == nullptr) {
        while (it_1 != nullptr) {
          result.push_back(it_1->value);
          it_1 = it_1->next_ptr;
        }
      }

      if (it_1 == nullptr) {
        while (it_2 != nullptr) {
          result.push_back(it_2->value);
          it_2 = it_2->next_ptr;
        }
      }
    }
    swap(result);
    other.clear();
  }
}

template <typename T>
void list<T>::sort() {
  if (empty() || ptr_first_node->next_ptr == nullptr) return;

  ptr_first_node = split_and_merge(ptr_first_node);

  DataNode<T> *last = ptr_first_node;
  while (last && last->next_ptr) {
    last = last->next_ptr;
  }
  ptr_last_node = last;
}

template <typename T>
DataNode<T> *list<T>::merge_node(DataNode<T> *first, DataNode<T> *second) {
  if (!first) return second;
  if (!second) return first;

  DataNode<T> *dummy_head = new DataNode<T>;
  DataNode<T> *tail = dummy_head;

  while (first && second) {
    if (first->value <= second->value) {
      tail->next_ptr = first;
      first = first->next_ptr;
    } else {
      tail->next_ptr = second;
      second = second->next_ptr;
    }
    tail = tail->next_ptr;
  }

  if (first) tail->next_ptr = first;
  if (second) tail->next_ptr = second;

  DataNode<T> *result = dummy_head->next_ptr;

  delete dummy_head;
  return result;
}

template <typename T>
std::pair<DataNode<T> *, DataNode<T> *> list<T>::split(DataNode<T> *head) {
  if (!head || !head->next_ptr) return {head, nullptr};

  DataNode<T> *slow = head;
  DataNode<T> *fast = head->next_ptr;

  while (fast && fast->next_ptr) {
    slow = slow->next_ptr;
    fast = fast->next_ptr->next_ptr;
  }

  DataNode<T> *second_half = slow->next_ptr;
  slow->next_ptr = nullptr;
  return {head, second_half};
}

template <typename T>
DataNode<T> *list<T>::split_and_merge(DataNode<T> *head) {
  if (!head || !head->next_ptr) return head;

  auto parts = split(head);
  DataNode<T> *left = split_and_merge(parts.first);
  DataNode<T> *right = split_and_merge(parts.second);

  return merge_node(left, right);
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  DataNode<T> *current = ptr_first_node;
  if (current != nullptr) {
    return iterator(current);
  }
  return iterator(nullptr);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const {
  DataNode<T> *current = ptr_first_node;
  if (current != nullptr) {
    return const_iterator(current);
  }
  return const_iterator(nullptr);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const {
  return const_iterator(nullptr);
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const T &value) {
  DataNode<T> *curr = new DataNode<T>(value);

  if (pos.current == nullptr) {
    if (ptr_last_node == nullptr) {
      ptr_first_node = ptr_last_node = curr;
    } else {
      ptr_last_node->next_ptr = curr;
      curr->prev_ptr = ptr_last_node;
      ptr_last_node = curr;
    }
  } else if (pos.current->prev_ptr == nullptr) {
    curr->next_ptr = pos.current;
    pos.current->prev_ptr = curr;
    ptr_first_node = curr;
  } else {
    curr->prev_ptr = pos.current->prev_ptr;
    curr->next_ptr = pos.current;
    pos.current->prev_ptr->next_ptr = curr;
    pos.current->prev_ptr = curr;
  }

  ++n;
  return iterator(curr);
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (other.empty()) return;

  DataNode<T> *firstOther = other.ptr_first_node;
  DataNode<T> *lastOther = other.ptr_last_node;

  if (pos.current == nullptr) {
    if (this->ptr_last_node) {
      this->ptr_last_node->next_ptr = firstOther;
      firstOther->prev_ptr = this->ptr_last_node;
    } else {
      this->ptr_first_node = firstOther;
      firstOther->prev_ptr = nullptr;
    }
    this->ptr_last_node = lastOther;
    lastOther->next_ptr = nullptr;
  } else {
    if (pos == this->begin()) {
      firstOther->prev_ptr = nullptr;
      this->ptr_first_node = firstOther;
    } else {
      DataNode<T> *prevNode = pos.current->prev_ptr;
      prevNode->next_ptr = firstOther;
      firstOther->prev_ptr = prevNode;
    }
    lastOther->next_ptr = pos.current;
    pos.current->prev_ptr = lastOther;
  }

  this->n += other.n;

  other.ptr_first_node = nullptr;
  other.ptr_last_node = nullptr;
  other.n = 0;
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == this->end()) return;

  DataNode<T> *nodeToDelete = pos.current;

  if (nodeToDelete->prev_ptr) {
    nodeToDelete->prev_ptr->next_ptr = nodeToDelete->next_ptr;
  } else {
    ptr_first_node = nodeToDelete->next_ptr;
  }

  if (nodeToDelete->next_ptr) {
    nodeToDelete->next_ptr->prev_ptr = nodeToDelete->prev_ptr;
  } else {
    ptr_last_node = nodeToDelete->prev_ptr;
  }

  pos.current = nodeToDelete->next_ptr;

  delete nodeToDelete;
  n--;
}

template <typename T>
list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(DataNode<T>);
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  auto it = pos.current;
  iterator result(it);

  (insert(result, std::forward<Args>(args)), ...);

  return result;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  ((this->push_back(std::forward<Args>(args))), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  ((this->push_front(std::forward<Args>(args))), ...);
}

};  // namespace my