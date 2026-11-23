#include "my_set.h"
// using namespace std;
using namespace my_tree;

namespace my {

template <typename TValue>
bool my_set<TValue>::empty() const {
  return tree.empty();
}

template <typename TValue>
typename my_set<TValue>::size_type my_set<TValue>::size() const {
  return tree.size();
}

template <typename TValue>
typename my_set<TValue>::size_type my_set<TValue>::max_size() const {
  return numeric_limits<typename my_set<TValue>::size_type>::max() /
         sizeof(RedBlackTreeNode<TValue, char>);
}

template <typename TValue>
my_set<TValue>::my_set(initializer_list<value_type> init) {
  for (const auto& val : init) {
    insert(val);
  }
}

template <typename TValue>
my_set<TValue>::my_set(const my_set& other) {
  tree = other.tree;
}

template <typename TValue>
my_set<TValue>::my_set(my_set&& other) noexcept {
  tree = std::move(other.tree);
}

template <typename TValue>
my_set<TValue>& my_set<TValue>::operator=(my_set&& other) noexcept {
  if (this != &other) {
    tree = std::move(other.tree);
  }

  return *this;
}

template <typename TValue>
my_set<TValue>& my_set<TValue>::operator=(const my_set& other) {
  if (this != &other) {
    tree = other.tree;
  }
  return *this;
}

template <typename TValue>
typename my_set<TValue>::iterator my_set<TValue>::begin() {
  iterator result = end();

  if (size() > 0) {
    result = iterator(tree.RedBlackTreeMinimum(tree.RedBlackTreeRoot()), &tree);
  }

  return result;
}

template <typename TValue>
typename my_set<TValue>::iterator my_set<TValue>::end() {
  return iterator(tree.RedBlackTreeNil(), &tree);
}

template <typename TValue>
typename my_set<TValue>::const_iterator my_set<TValue>::begin() const {
  const_iterator result = end();

  if (size() > 0) {
    result = const_iterator(tree.RedBlackTreeMinimum(tree.RedBlackTreeRoot()),
                            &tree);
  }

  return result;
}

template <typename TValue>
typename my_set<TValue>::const_iterator my_set<TValue>::end() const {
  return const_iterator(tree.RedBlackTreeNil(), &tree);
}

template <typename TValue>
pair<typename my_set<TValue>::iterator, bool> my_set<TValue>::insert(
    const value_type& value) {
  auto it = find(value);
  if (it != end()) {
    return {it, false};
  }

  auto result = tree.RedBlackTreeInsert(value, ' ');
  iterator new_it(result.second, &tree);

  return {new_it, true};
}

template <typename TValue>
void my_set<TValue>::erase(iterator pos) {
  if (pos.node != tree.RedBlackTreeNil()) {
    tree.RedBlackTreeRemoveNode(pos.node);
  }
}

template <typename TValue>
void my_set<TValue>::swap(my_set& other) {
  if (this != &other) {
    RedBlackTree<TValue, char> tmp;
    tmp = std::move(tree);
    tree = std::move(other.tree);
    other.tree = std::move(tmp);
  }
}

template <typename TValue>
void my_set<TValue>::merge(my_set& other) {
  my::vector<RedBlackTreeNode<TValue, char>*> nodes_to_move;
  auto* nil = tree.RedBlackTreeNil();

  collect_nodes(other.tree.RedBlackTreeRoot(), other.tree.RedBlackTreeNil(),
                nodes_to_move);

  other.tree.resetTree();

  for (auto* node : nodes_to_move) {
    node->left = nil;
    node->right = nil;
    node->parent = nil;
    node->isBlack = false;

    tree.RedBlackTreeInsertNode(node);
  }
}

template <typename TValue>
void my_set<TValue>::collect_nodes(
    RedBlackTreeNode<TValue, char>* node, RedBlackTreeNode<TValue, char>* t_nil,
    vector<RedBlackTreeNode<TValue, char>*>& nodes) {
  if (node != t_nil) {
    collect_nodes(node->left, t_nil, nodes);
    collect_nodes(node->right, t_nil, nodes);

    if (tree.RedBlackTreeSearch(node->nodeKey, tree.RedBlackTreeRoot()) ==
        tree.RedBlackTreeNil()) {
      nodes.push_back(node);
    } else {
      delete node;
    }
  }
}

template <typename TValue>
void my_set<TValue>::clear() {
  tree.clear();
}

template <typename TValue>
typename my_set<TValue>::iterator my_set<TValue>::find(const key_type& key) {
  iterator result = end();

  auto* node = tree.RedBlackTreeSearch(key, tree.RedBlackTreeRoot());

  if (node != tree.RedBlackTreeNil()) {
    result = iterator(node, &tree);
  }

  return result;
}

template <typename TValue>
bool my_set<TValue>::contains(const key_type& key) {
  bool result = false;
  auto node = tree.RedBlackTreeSearch(key, tree.RedBlackTreeRoot());

  if (node != tree.RedBlackTreeNil()) {
    result = true;
  }

  return result;
}

template <typename TValue>
template <typename... Args>
std::vector<std::pair<typename my_set<TValue>::iterator, bool>>
my_set<TValue>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  result.reserve(sizeof...(args));

  (result.push_back(insert(std::forward<Args>(args))), ...);

  return result;
}
}  // namespace my