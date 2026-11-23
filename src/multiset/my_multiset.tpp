#include "my_multiset.h"

using namespace std;
using namespace my_tree;

namespace my {
template <typename Key>
my_multiset<Key>::my_multiset(initializer_list<value_type> const &items) {
  for (const auto &val : items) {
    insert(val);
  }
}

template <typename Key>
my_multiset<Key>::my_multiset(const my_multiset &ms) {
  tree = ms.tree;
}

template <typename Key>
my_multiset<Key>::my_multiset(my_multiset &&ms) noexcept {
  tree = std::move(ms.tree);
}

template <typename Key>
my_multiset<Key> &my_multiset<Key>::operator=(const my_multiset &ms) {
  if (this != &ms) {
    tree = ms.tree;
  }
  return *this;
}

template <typename Key>
my_multiset<Key> &my_multiset<Key>::operator=(my_multiset &&ms) noexcept {
  if (this != &ms) {
    tree = std::move(ms.tree);
  }

  return *this;
}

template <typename Key>
typename my_multiset<Key>::iterator my_multiset<Key>::begin() {
  iterator result = end();

  if (size() > 0) {
    result = iterator(tree.RedBlackTreeMinimum(tree.RedBlackTreeRoot()), &tree);
  }

  return result;
}

template <typename Key>
typename my_multiset<Key>::iterator my_multiset<Key>::end() {
  return iterator(tree.RedBlackTreeNil(), &tree);
}

template <typename Key>
typename my_multiset<Key>::const_iterator my_multiset<Key>::begin() const {
  const_iterator result = end();

  if (size() > 0) {
    result = const_iterator(tree.RedBlackTreeMinimum(tree.RedBlackTreeRoot()),
                            &tree);
  }
}

template <typename Key>
typename my_multiset<Key>::const_iterator my_multiset<Key>::end() const {
  return const_iterator(tree.RedBlackTreeNil(), &tree);
}

template <typename Key>
bool my_multiset<Key>::empty() {
  return tree.empty();
}

template <typename Key>
typename my_multiset<Key>::size_type my_multiset<Key>::size() {
  return tree.size();
}

template <typename Key>
typename my_multiset<Key>::size_type my_multiset<Key>::max_size() {
  return numeric_limits<typename my_multiset<Key>::size_type>::max() /
         sizeof(RedBlackTreeNode<Key, char>);
}

template <typename Key>
void my_multiset<Key>::clear() {
  tree.clear();
}

template <typename Key>
void my_multiset<Key>::erase(iterator pos) {
  if (pos.node != tree.RedBlackTreeNil()) {
    tree.RedBlackTreeRemoveNode(pos.node);
  }
}

template <typename Key>
void my_multiset<Key>::swap(my_multiset &other) {
  if (this != &other) {
    RedBlackTree<Key, char> tmp;
    tmp = std::move(tree);
    tree = std::move(other.tree);
    other.tree = std::move(tmp);
  }
}

template <typename Key>
void my_multiset<Key>::merge(my_multiset &other) {
  std::vector<RedBlackTreeNode<Key, char> *> nodes_to_move;
  auto *nil = tree.RedBlackTreeNil();

  collect_nodes(other.tree.RedBlackTreeRoot(), other.tree.RedBlackTreeNil(),
                nodes_to_move);

  other.tree.resetTree();

  for (auto *node : nodes_to_move) {
    node->left = nil;
    node->right = nil;
    node->parent = nil;
    node->isBlack = false;

    tree.RedBlackTreeInsertNode(node);
  }
}

template <typename Key>
void my_multiset<Key>::collect_nodes(
    RedBlackTreeNode<Key, char> *node, RedBlackTreeNode<Key, char> *t_nil,
    vector<RedBlackTreeNode<Key, char> *> &nodes) {
  if (node != t_nil) {
    collect_nodes(node->left, t_nil, nodes);
    collect_nodes(node->right, t_nil, nodes);

    nodes.push_back(node);
  }
}

template <typename Key>
typename my_multiset<Key>::iterator my_multiset<Key>::insert(
    const value_type &value) {
  auto result = tree.RedBlackTreeInsert(value, ' ');
  iterator new_it(result.second, &tree);

  return new_it;
}

template <typename Key>
std::pair<typename my_multiset<Key>::iterator, bool>
my_multiset<Key>::internalInsert(const value_type &value) {
  auto result = tree.RedBlackTreeInsert(value, ' ');
  return std::make_pair(iterator(result.second, &tree), result.first);
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename my_multiset<Key>::iterator, bool>>
my_multiset<Key>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  (result.push_back(internalInsert(std::forward<Args>(args))), ...);
  return result;
}

template <typename Key>
typename my_multiset<Key>::size_type my_multiset<Key>::count(const Key &key) {
  my_multiset<Key>::size_type result = 0;

  for (auto it = begin(); it != end(); it++) {
    if (*it == key) {
      result++;
    }
  }
  return result;
}

template <typename Key>
typename my_multiset<Key>::iterator my_multiset<Key>::find(const Key &key) {
  iterator result = end();

  auto *node = tree.RedBlackTreeSearch(key, tree.RedBlackTreeRoot());

  if (node != tree.RedBlackTreeNil()) {
    result = iterator(node, &tree);
  }

  return result;
}

template <typename Key>
bool my_multiset<Key>::contains(const Key &key) {
  bool result = false;
  auto node = tree.RedBlackTreeSearch(key, tree.RedBlackTreeRoot());

  if (node != tree.RedBlackTreeNil()) {
    result = true;
  }

  return result;
}

template <typename Key>
std::pair<typename my_multiset<Key>::iterator,
          typename my_multiset<Key>::iterator>
my_multiset<Key>::equal_range(const Key &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key>
typename my_multiset<Key>::iterator my_multiset<Key>::lower_bound(
    const Key &key) {
  auto node = tree.RedBlackTreeRoot();
  auto nil = tree.RedBlackTreeNil();
  RedBlackTreeNode<Key, char> *result = nil;

  while (node != nil) {
    if (key <= node->nodeKey) {
      result = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }

  return iterator(result, &tree);
}

template <typename Key>
typename my_multiset<Key>::iterator my_multiset<Key>::upper_bound(
    const Key &key) {
  auto node = tree.RedBlackTreeRoot();
  auto nil = tree.RedBlackTreeNil();
  RedBlackTreeNode<Key, char> *result = nil;

  while (node != nil) {
    if (key < node->nodeKey) {
      result = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }

  return iterator(result, &tree);
}
}  // namespace my