#ifndef MY_REDBLACKTREE_HPP
#define MY_REDBLACKTREE_HPP

#include <iostream>
#include <memory>

namespace my_tree {

template <typename TNodeKey, typename TNodeValue>
struct RedBlackTreeNode {
  TNodeKey nodeKey;
  TNodeValue nodeValue;
  bool isBlack;
  RedBlackTreeNode<TNodeKey, TNodeValue> *parent;
  RedBlackTreeNode<TNodeKey, TNodeValue> *left;
  RedBlackTreeNode<TNodeKey, TNodeValue> *right;
};

template <typename TNodeKey, typename TNodeValue>
class RedBlackTree {
 private:
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeFindNodeForInsertion(
      RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode);
  void SetNewNodeInFoundedForInsertion(
      RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode,
      RedBlackTreeNode<TNodeKey, TNodeValue> *foundedNode);
  void RedBlackTreeInsertFixup(
      RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode);
  RedBlackTreeNode<TNodeKey, TNodeValue> *
  RedBlackTreeGetInsertingLeftGrandpaChildFixup(
      RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode);
  RedBlackTreeNode<TNodeKey, TNodeValue> *
  RedBlackTreeGetInsertingRightGrandpaChildFixup(
      RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode);
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeGetLeftChildRemoveFixup(
      RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode,
      RedBlackTreeNode<TNodeKey, TNodeValue> *parentNode);
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeGetRightChildRemoveFixup(
      RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode,
      RedBlackTreeNode<TNodeKey, TNodeValue> *parentNode);
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeCopySubtree(
      RedBlackTreeNode<TNodeKey, TNodeValue> *sourceNode,
      const RedBlackTree &copyingTree);
  void RedBlackTreeRelocateTNil(
      RedBlackTreeNode<TNodeKey, TNodeValue> *currentNode,
      RedBlackTreeNode<TNodeKey, TNodeValue> *oldTNil,
      RedBlackTreeNode<TNodeKey, TNodeValue> *newTNil);

 protected:
  size_t elementsCount = 0;
  RedBlackTreeNode<TNodeKey, TNodeValue> sentinel;
  RedBlackTreeNode<TNodeKey, TNodeValue> *t_nil;
  RedBlackTreeNode<TNodeKey, TNodeValue> *root;

  void RedBlackTreeLeftRotate(
      RedBlackTreeNode<TNodeKey, TNodeValue> *rotationNode);
  void RedBlackTreeRightRotate(
      RedBlackTreeNode<TNodeKey, TNodeValue> *rotationNode);
  void RedBlackTreeTransplant(
      RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode,
      RedBlackTreeNode<TNodeKey, TNodeValue> *transplantapleNode);
  void RedBlackTreeRemoveFixup(
      RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode);

 public:
  RedBlackTree();

  RedBlackTree(const RedBlackTree &other);
  RedBlackTree(RedBlackTree &&other) noexcept;

  ~RedBlackTree();

  RedBlackTree &operator=(const RedBlackTree &other);
  RedBlackTree &operator=(RedBlackTree &&other) noexcept;

  bool empty() const;
  size_t size() const;
  void clear();

  void resetTree();
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeRoot() const;
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeNil() const;
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreePredecessor(
      RedBlackTreeNode<TNodeKey, TNodeValue> *nextNode) const;
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeSuccessor(
      RedBlackTreeNode<TNodeKey, TNodeValue> *previousNode) const;
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeSearch(
      TNodeKey key, RedBlackTreeNode<TNodeKey, TNodeValue> *subtreeRoot) const;

  void RedBlackTreeClear(RedBlackTreeNode<TNodeKey, TNodeValue> *startNode);
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeMinimum(
      RedBlackTreeNode<TNodeKey, TNodeValue> *subtreeRoot) const;
  RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTreeMaximum(
      RedBlackTreeNode<TNodeKey, TNodeValue> *subtreeRoot) const;
  void RedBlackTreeRemoveNode(
      RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode);

  std::pair<bool, RedBlackTreeNode<TNodeKey, TNodeValue> *> RedBlackTreeInsert(
      const TNodeKey &key, const TNodeValue &value);

  void RedBlackTreeInsertNode(RedBlackTreeNode<TNodeKey, TNodeValue> *newNode);
  //
};

}  // namespace my_tree

#endif  // my_REDBLACKTREE_HPP