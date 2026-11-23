#ifndef MY_MAP_H_INCLUDED
#define MY_MAP_H_INCLUDED

#include <initializer_list>
#include <utility>
#include <vector>

#include "../tree/RedBlackTree.h"
#include "../tree/RedBlackTree.tpp"
namespace my {
template <typename Key, typename T>
class my_map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  class MapConstIterator {
   private:
    using node_type = my_tree::RedBlackTreeNode<Key, T>;
    using tree_type = my_tree::RedBlackTree<Key, T>;

    my_map *map;
    node_type *node;
    const tree_type *tree;

    friend class my_map;
    mutable typename my_map<Key, T>::value_type *proxy_ptr = nullptr;

    explicit MapConstIterator(node_type *n, const tree_type *t)
        : node(n), tree(t) {}

    mutable typename my_map<Key, T>::value_type proxy_value;

   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = typename my_map<Key, T>::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = const value_type *;
    using reference = const value_type &;

    ~MapConstIterator() { delete proxy_ptr; }

    MapConstIterator(const MapConstIterator &other) = default;

    MapConstIterator &operator=(const MapConstIterator &other) {
      if (this != &other) {
        node = other.node;
        map = other.map;
        delete proxy_ptr;
        proxy_ptr = nullptr;
      }
      return *this;
    }

    reference operator*() const {
      delete proxy_ptr;
      proxy_ptr = new value_type(node->nodeKey, node->nodeValue);
      return *proxy_ptr;
    }

    pointer operator->() const {
      if (!proxy_ptr) {
        proxy_ptr = new value_type(node->nodeKey, node->nodeValue);
      }
      return proxy_ptr;
    }

    MapConstIterator &operator++() {
      if (node != tree->RedBlackTreeNil()) {
        node = tree->RedBlackTreeSuccessor(node);
      }
      return *this;
    }

    MapConstIterator operator++(int) {
      MapConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    MapConstIterator &operator--() {
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

    MapConstIterator operator--(int) {
      MapConstIterator tmp = *this;
      --(*this);
      return tmp;
    }

    bool operator==(const MapConstIterator &other) const {
      return node == other.node;
    }

    bool operator!=(const MapConstIterator &other) const {
      return !(*this == other);
    }
  };

  using iterator = MapConstIterator;
  using const_iterator = MapConstIterator;

  my_map() = default;
  my_map(std::initializer_list<value_type> const &items);
  my_map(const my_map &m);
  my_map(my_map &&m) noexcept;
  ~my_map() = default;

  my_map &operator=(const my_map &m);
  my_map &operator=(my_map &&m) noexcept;

  T &at(const key_type &key);
  T &operator[](const key_type &key);

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  bool empty();
  size_type size() const;
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key, const T &obj);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  void erase(iterator pos);
  void swap(my_map &other);
  void merge(my_map &other);

  bool contains(const key_type &key);

 private:
  my_tree::RedBlackTree<Key, T> tree;
  void collect_nodes(my_tree::RedBlackTreeNode<Key, T> *node,
                     my_tree::RedBlackTreeNode<Key, T> *t_nil,
                     my::vector<my_tree::RedBlackTreeNode<Key, T> *> &nodes);
};

}  // namespace my

#endif  // my_MAP_H_INCLUDED