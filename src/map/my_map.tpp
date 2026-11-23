using namespace std;
using namespace my;
using namespace my_tree;

namespace my {
template <typename Key, typename T>
my_map<Key, T>::my_map(std::initializer_list<value_type> const &items) {
  for (const auto &val : items) {
    insert(val);
  }
}

template <typename Key, typename T>
my_map<Key, T>::my_map(const my_map &m) {
  tree = m.tree;
}

template <typename Key, typename T>
my_map<Key, T>::my_map(my_map &&m) noexcept {
  tree = std::move(m.tree);
}

template <typename Key, typename T>
my_map<Key, T> &my_map<Key, T>::operator=(const my_map &m) {
  if (this != &m) {
    tree = m.tree;
  }
  return *this;
}

template <typename Key, typename T>
my_map<Key, T> &my_map<Key, T>::operator=(my_map &&m) noexcept {
  if (this != &m) {
    tree = std::move(m.tree);
  }

  return *this;
}

template <typename Key, typename T>
T &my_map<Key, T>::at(const key_type &key) {
  auto node = tree.RedBlackTreeSearch(key, tree.RedBlackTreeRoot());

  if (node == tree.RedBlackTreeNil()) {
    throw std::out_of_range("key not exist");
  }

  return node->nodeValue;
}

template <typename Key, typename T>
T &my_map<Key, T>::operator[](const key_type &key) {
  auto node = tree.RedBlackTreeSearch(key, tree.RedBlackTreeRoot());
  if (node != tree.RedBlackTreeNil()) {
    return node->nodeValue;
  }

  auto result = tree.RedBlackTreeInsert(key, T{});
  return result.second->nodeValue;
}

template <typename Key, typename T>
typename my_map<Key, T>::iterator my_map<Key, T>::begin() {
  iterator result = end();

  if (size() > 0) {
    result = iterator(tree.RedBlackTreeMinimum(tree.RedBlackTreeRoot()), &tree);
  }

  return result;
}

template <typename Key, typename T>
typename my_map<Key, T>::iterator my_map<Key, T>::end() {
  return iterator(tree.RedBlackTreeNil(), &tree);
}

template <typename Key, typename T>
typename my_map<Key, T>::const_iterator my_map<Key, T>::begin() const {
  const_iterator result = end();

  if (size() > 0) {
    result = iterator(tree.RedBlackTreeMinimum(tree.RedBlackTreeRoot()), &tree);
  }

  return result;
}

template <typename Key, typename T>
typename my_map<Key, T>::const_iterator my_map<Key, T>::end() const {
  return const_iterator(tree.RedBlackTreeNil(), &tree);
}

template <typename Key, typename T>
bool my_map<Key, T>::empty() {
  return tree.empty();
}

template <typename Key, typename T>
typename my_map<Key, T>::size_type my_map<Key, T>::size() const {
  return tree.size();
}

template <typename Key, typename T>
typename my_map<Key, T>::size_type my_map<Key, T>::max_size() {
  return std::numeric_limits<typename my_map<Key, T>::size_type>::max() / 2;
}

template <typename Key, typename T>
void my_map<Key, T>::clear() {
  tree.clear();
}

template <typename Key, typename T>
std::pair<typename my_map<Key, T>::iterator, bool> my_map<Key, T>::insert(
    const value_type &value) {
  auto node = tree.RedBlackTreeSearch(value.first, tree.RedBlackTreeRoot());
  if (node == tree.RedBlackTreeNil()) {
    auto result = tree.RedBlackTreeInsert(value.first, value.second);
    return std::make_pair(iterator(result.second, &tree), result.first);
  } else {
    return std::make_pair(iterator(node, &tree), false);
  }
}

template <typename Key, typename T>
std::pair<typename my_map<Key, T>::iterator, bool> my_map<Key, T>::insert(
    const key_type &key, const T &obj) {
  return insert(value_type(key, obj));
}

template <typename Key, typename T>
std::pair<typename my_map<Key, T>::iterator, bool>
my_map<Key, T>::insert_or_assign(const key_type &key, const T &obj) {
  auto node = tree.RedBlackTreeSearch(key, tree.RedBlackTreeRoot());
  if (node == tree.RedBlackTreeNil()) {
    return insert(value_type(key, obj));
  } else {
    node->nodeValue = obj;
    return std::make_pair(iterator(node, &tree), false);
  }
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename my_map<Key, T>::iterator, bool>>
my_map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;

  (result.push_back(insert(std::forward<Args>(args))), ...);
  return result;
}

template <typename Key, typename T>
void my_map<Key, T>::erase(iterator pos) {
  if (pos.node != tree.RedBlackTreeNil()) {
    tree.RedBlackTreeRemoveNode(pos.node);
  }
}

template <typename Key, typename T>
void my_map<Key, T>::swap(my_map &other) {
  if (this != &other) {
    RedBlackTree<Key, T> tmp;
    tmp = std::move(tree);
    tree = std::move(other.tree);
    other.tree = std::move(tmp);
  }
}

template <typename Key, typename T>
void my_map<Key, T>::merge(my_map &other) {
  my::vector<RedBlackTreeNode<Key, T> *> nodes_to_move;
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

template <typename Key, typename T>
void my_map<Key, T>::collect_nodes(
    RedBlackTreeNode<Key, T> *node, RedBlackTreeNode<Key, T> *t_nil,
    my::vector<RedBlackTreeNode<Key, T> *> &nodes) {
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

template <typename Key, typename T>
bool my_map<Key, T>::contains(const key_type &key) {
  bool result = false;
  auto node = tree.RedBlackTreeSearch(key, tree.RedBlackTreeRoot());

  if (node != tree.RedBlackTreeNil()) {
    result = true;
  }

  return result;
}

}  // namespace my