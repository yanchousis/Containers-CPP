#ifndef MY_MULTISET_H_INCLUDED
#define MY_MULTISET_H_INCLUDED

#include <initializer_list>
#include <utility>

#include "../tree/RedBlackTree.h"
#include "../tree/RedBlackTree.tpp"

namespace my {
template <typename Key>
class my_multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  class MultisetIterator {
   private:
    using node_type = my_tree::RedBlackTreeNode<Key, char>;
    using tree_type = my_tree::RedBlackTree<Key, char>;

    node_type *node;
    const tree_type *tree;

    friend class my_multiset;

    explicit MultisetIterator(node_type *n, const tree_type *t)
        : node(n), tree(t) {}

    mutable Key proxy_value;

   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using pointer = const Key *;
    using reference = const Key &;

    reference operator*() const {
      proxy_value = node->nodeKey;
      return proxy_value;
    }

    pointer operator->() const {
      proxy_value = node->nodeKey;
      return &proxy_value;
    }

    MultisetIterator &operator++() {
      if (node != tree->RedBlackTreeNil()) {
        node = tree->RedBlackTreeSuccessor(node);
      }
      return *this;
    }

    MultisetIterator operator++(int) {
      MultisetIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    MultisetIterator &operator--() {
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

    MultisetIterator operator--(int) {
      MultisetIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const MultisetIterator &other) const {
      return node == other.node;
    }

    bool operator!=(const MultisetIterator &other) const {
      return !(*this == other);
    }
  };

  using iterator = MultisetIterator;
  using const_iterator = MultisetIterator;

  my_multiset() = default;
  my_multiset(std::initializer_list<value_type> const &items);
  my_multiset(const my_multiset &ms);
  my_multiset(my_multiset &&ms) noexcept;
  ~my_multiset() = default;

  my_multiset &operator=(const my_multiset &ms);
  my_multiset &operator=(my_multiset &&ms) noexcept;

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  void erase(iterator pos);
  void swap(my_multiset &other);
  void merge(my_multiset &other);
  iterator insert(const value_type &value);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  size_type count(const Key &key);
  iterator find(const Key &key);
  bool contains(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

 private:
  my_tree::RedBlackTree<Key, char> tree;
  void collect_nodes(
      my_tree::RedBlackTreeNode<Key, char> *node,
      my_tree::RedBlackTreeNode<Key, char> *t_nil,
      std::vector<my_tree::RedBlackTreeNode<Key, char> *> &nodes);
  std::pair<iterator, bool> internalInsert(const value_type &value);
};
}  // namespace my

#endif  // my_MULTISET_H_INCLUDED