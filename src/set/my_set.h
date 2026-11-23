#ifndef MY_SET_H_INCLUDED
#define MY_SET_H_INCLUDED

#include <initializer_list>
#include <utility>

#include "../tree/RedBlackTree.h"
#include "../tree/RedBlackTree.tpp"
#include "vector/my_vector.h"
#include "vector/my_vector.tpp"

namespace my {

template <typename TValue>
class my_set {
 private:
  my_tree::RedBlackTree<TValue, char> tree;
  void collect_nodes(
      my_tree::RedBlackTreeNode<TValue, char>* node,
      my_tree::RedBlackTreeNode<TValue, char>* t_nil,
      my::vector<my_tree::RedBlackTreeNode<TValue, char>*>& nodes);

 public:
  using key_type = TValue;
  using value_type = TValue;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  class SetIterator {
   private:
    using node_type = my_tree::RedBlackTreeNode<TValue, char>;
    using tree_type = my_tree::RedBlackTree<TValue, char>;

    node_type* node;
    const tree_type* tree;

    friend class my_set<TValue>;

    explicit SetIterator(node_type* n, const tree_type* t) : node(n), tree(t) {}

    mutable TValue proxy_value;

   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = TValue;
    using difference_type = std::ptrdiff_t;
    using pointer = const TValue*;
    using reference = const TValue&;

    reference operator*() const {
      proxy_value = node->nodeKey;
      return proxy_value;
    }

    pointer operator->() const {
      proxy_value = node->nodeKey;
      return &proxy_value;
    }

    SetIterator& operator++() {
      if (node != tree->RedBlackTreeNil()) {
        node = tree->RedBlackTreeSuccessor(node);
      }
      return *this;
    }

    SetIterator operator++(int) {
      SetIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    SetIterator& operator--() {
      if (node == tree->RedBlackTreeNil()) {
        node = tree->RedBlackTreeRoot();
        while (node != tree->RedBlackTreeNil() &&
               node->right != tree->RedBlackTreeNil()) {
          node = node->right;
        }
      } else {
        node = tree->RedBlackTreePredecessor(node);
      }
      return *this;
    }

    SetIterator operator--(int) {
      SetIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const SetIterator& other) const {
      return node == other.node;
    }

    bool operator!=(const SetIterator& other) const {
      return !(*this == other);
    }
  };
  using iterator = SetIterator;
  using const_iterator = SetIterator;

  my_set() = default;
  my_set(std::initializer_list<value_type> init);
  my_set(const my_set& other);
  my_set(my_set&& other) noexcept;
  ~my_set() = default;

  my_set& operator=(my_set&& other) noexcept;
  my_set& operator=(const my_set& other);

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  std::pair<iterator, bool> insert(const value_type& value);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void erase(iterator pos);
  void clear();
  void swap(my_set& other);
  void merge(my_set& other);

  iterator find(const key_type& key);
  bool contains(const key_type& key);
};

}  // namespace my

#endif  // my_SET_H_INCLUDED
