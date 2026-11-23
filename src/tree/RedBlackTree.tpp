#ifndef MY_REDBLACKTREE_TPP
#define MY_REDBLACKTREE_TPP

#include "RedBlackTree.h"

using namespace std;

namespace my_tree {

template <typename TNodeKey, typename TNodeValue>
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTree() {
  t_nil = &sentinel;
  sentinel.isBlack = true;
  sentinel.parent = t_nil;
  sentinel.left = t_nil;
  sentinel.right = t_nil;
  root = t_nil;
  elementsCount = 0;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTree(const RedBlackTree &other) {
  t_nil = &sentinel;
  sentinel.isBlack = true;
  sentinel.parent = t_nil;
  sentinel.left = t_nil;
  sentinel.right = t_nil;
  root = t_nil;

  if (other.elementsCount != 0) {
    root = RedBlackTreeCopySubtree(other.root, other);
    root->parent = t_nil;
  }
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTree<TNodeKey, TNodeValue>::~RedBlackTree() {
  RedBlackTreeClear(root);
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTree<TNodeKey, TNodeValue> &
RedBlackTree<TNodeKey, TNodeValue>::operator=(const RedBlackTree &other) {
  if (this != &other) {
    clear();

    if (other.root != other.t_nil) {
      root = RedBlackTreeCopySubtree(other.root, other);
      root->parent = t_nil;
    } else {
      root = t_nil;
    }
  }
  return *this;
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeRelocateTNil(
    RedBlackTreeNode<TNodeKey, TNodeValue> *currentNode,
    RedBlackTreeNode<TNodeKey, TNodeValue> *oldTNil,
    RedBlackTreeNode<TNodeKey, TNodeValue> *newTNil) {
  if (currentNode != oldTNil) {
    if (currentNode->left == oldTNil) {
      currentNode->left = newTNil;
    } else {
      RedBlackTreeRelocateTNil(currentNode->left, oldTNil, newTNil);
    }

    if (currentNode->right == oldTNil) {
      currentNode->right = newTNil;
    } else {
      RedBlackTreeRelocateTNil(currentNode->right, oldTNil, newTNil);
    }

    if (currentNode->parent == oldTNil) {
      currentNode->parent = newTNil;
    }
  }
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTree(
    RedBlackTree &&other) noexcept {
  t_nil = &sentinel;
  sentinel.isBlack = true;
  sentinel.parent = t_nil;
  sentinel.left = t_nil;
  sentinel.right = t_nil;
  root = t_nil;
  elementsCount = 0;

  if (other.elementsCount > 0) {
    root = other.root;
    elementsCount = other.elementsCount;

    RedBlackTreeRelocateTNil(root, other.t_nil, t_nil);

    if (root != t_nil) {
      root->parent = t_nil;
    }

    other.root = other.t_nil;
    other.elementsCount = 0;
  }
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTree<TNodeKey, TNodeValue> &
RedBlackTree<TNodeKey, TNodeValue>::operator=(RedBlackTree &&other) noexcept {
  if (this != &other) {
    if (elementsCount > 0) {
      RedBlackTreeClear(root);
    }

    root = t_nil;
    elementsCount = 0;

    if (other.elementsCount > 0) {
      root = other.root;
      elementsCount = other.elementsCount;

      RedBlackTreeRelocateTNil(root, other.t_nil, t_nil);

      if (root != t_nil) {
        root->parent = t_nil;
      }

      other.root = other.t_nil;
      other.elementsCount = 0;
    }
  }
  return *this;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeCopySubtree(
    RedBlackTreeNode<TNodeKey, TNodeValue> *sourceNode,
    const RedBlackTree &copyingTree) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *result = t_nil;

  if (sourceNode != copyingTree.t_nil) {
    result = new RedBlackTreeNode<TNodeKey, TNodeValue>{};
    result->nodeKey = sourceNode->nodeKey;
    result->nodeValue = sourceNode->nodeValue;
    result->isBlack = sourceNode->isBlack;

    result->left = RedBlackTreeCopySubtree(sourceNode->left, copyingTree);
    result->right = RedBlackTreeCopySubtree(sourceNode->right, copyingTree);

    if (result->left != copyingTree.t_nil) {
      result->left->parent = result;
    }

    if (result->right != copyingTree.t_nil) {
      result->right->parent = result;
    }

    result->parent = t_nil;
    elementsCount++;
  }

  return result;
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeClear(
    RedBlackTreeNode<TNodeKey, TNodeValue> *startNode) {
  if (startNode != t_nil) {
    RedBlackTreeClear(startNode->left);
    RedBlackTreeClear(startNode->right);
    delete startNode;
  }
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::clear() {
  RedBlackTreeClear(root);
  root = t_nil;
  elementsCount = 0;
}

template <typename TNodeKey, typename TNodeValue>
bool RedBlackTree<TNodeKey, TNodeValue>::empty() const {
  return elementsCount == 0;
}

template <typename TNodeKey, typename TNodeValue>
size_t RedBlackTree<TNodeKey, TNodeValue>::size() const {
  return elementsCount;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeMinimum(
    RedBlackTreeNode<TNodeKey, TNodeValue> *subtreeRoot) const {
  RedBlackTreeNode<TNodeKey, TNodeValue> *result = subtreeRoot;

  while (result->left != t_nil) {
    result = result->left;
  }

  return result;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeMaximum(
    RedBlackTreeNode<TNodeKey, TNodeValue> *subtreeRoot) const {
  RedBlackTreeNode<TNodeKey, TNodeValue> *result = subtreeRoot;

  while (result->right != t_nil) {
    result = result->right;
  }

  return result;
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeLeftRotate(
    RedBlackTreeNode<TNodeKey, TNodeValue> *rotationNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *rightChildNode = nullptr;

  rightChildNode = rotationNode->right;
  rotationNode->right = rightChildNode->left;

  if (rightChildNode->left != t_nil) {
    rightChildNode->left->parent = rotationNode;
  }

  rightChildNode->parent = rotationNode->parent;

  if (rotationNode->parent == t_nil) {
    root = rightChildNode;
  } else if (rotationNode == rotationNode->parent->left) {
    rotationNode->parent->left = rightChildNode;
  } else {
    rotationNode->parent->right = rightChildNode;
  }

  rightChildNode->left = rotationNode;

  rotationNode->parent = rightChildNode;
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeRightRotate(
    RedBlackTreeNode<TNodeKey, TNodeValue> *rotationNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *leftChildNode = nullptr;

  leftChildNode = rotationNode->left;
  rotationNode->left = leftChildNode->right;

  if (leftChildNode->right != t_nil) {
    leftChildNode->right->parent = rotationNode;
  }

  leftChildNode->parent = rotationNode->parent;

  if (rotationNode->parent == t_nil) {
    root = leftChildNode;
  } else if (rotationNode == rotationNode->parent->right) {
    rotationNode->parent->right = leftChildNode;
  } else {
    rotationNode->parent->left = leftChildNode;
  }

  leftChildNode->right = rotationNode;

  rotationNode->parent = leftChildNode;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeFindNodeForInsertion(
    RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *returningNode = t_nil;
  RedBlackTreeNode<TNodeKey, TNodeValue> *currentNode = root;

  while (currentNode != t_nil) {
    returningNode = currentNode;

    if (insertingNode->nodeKey > currentNode->nodeKey) {
      currentNode = currentNode->right;
    } else {
      currentNode = currentNode->left;
    }
  }

  return returningNode;
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::SetNewNodeInFoundedForInsertion(
    RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode,
    RedBlackTreeNode<TNodeKey, TNodeValue> *foundedNode) {
  insertingNode->parent = foundedNode;

  if (foundedNode == t_nil) {
    root = insertingNode;
  } else if (insertingNode->nodeKey > foundedNode->nodeKey) {
    foundedNode->right = insertingNode;
  } else {
    foundedNode->left = insertingNode;
  }
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeInsertNode(
    RedBlackTreeNode<TNodeKey, TNodeValue> *newNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *parentNode = t_nil;

  parentNode = RedBlackTreeFindNodeForInsertion(newNode);
  SetNewNodeInFoundedForInsertion(newNode, parentNode);

  newNode->left = t_nil;
  newNode->right = t_nil;
  newNode->isBlack = false;

  elementsCount++;

  RedBlackTreeInsertFixup(newNode);
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeInsertFixup(
    RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *parentNode = t_nil;
  RedBlackTreeNode<TNodeKey, TNodeValue> *grandpaNode = t_nil;

  parentNode = insertingNode->parent;
  grandpaNode = parentNode->parent;

  while (!parentNode->isBlack) {
    if (parentNode == grandpaNode->left) {
      insertingNode =
          RedBlackTreeGetInsertingLeftGrandpaChildFixup(insertingNode);
    } else {
      insertingNode =
          RedBlackTreeGetInsertingRightGrandpaChildFixup(insertingNode);
    }

    parentNode = insertingNode->parent;
    grandpaNode = parentNode->parent;
  }

  root->isBlack = true;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTree<TNodeKey, TNodeValue>::
    RedBlackTreeGetInsertingLeftGrandpaChildFixup(
        RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *parentNode = t_nil;
  RedBlackTreeNode<TNodeKey, TNodeValue> *grandpaNode = t_nil;
  RedBlackTreeNode<TNodeKey, TNodeValue> *uncleNode = t_nil;

  parentNode = insertingNode->parent;
  grandpaNode = insertingNode->parent->parent;
  uncleNode = grandpaNode->right;

  if (!uncleNode->isBlack) {
    parentNode->isBlack = true;
    uncleNode->isBlack = true;
    grandpaNode->isBlack = false;
    insertingNode = grandpaNode;
  } else {
    if (insertingNode == parentNode->right) {
      insertingNode = parentNode;
      RedBlackTreeLeftRotate(insertingNode);

      parentNode = insertingNode->parent;
      grandpaNode = insertingNode->parent->parent;
      uncleNode = grandpaNode->right;
    }

    parentNode->isBlack = true;
    grandpaNode->isBlack = false;
    RedBlackTreeRightRotate(grandpaNode);
  }

  return insertingNode;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *RedBlackTree<TNodeKey, TNodeValue>::
    RedBlackTreeGetInsertingRightGrandpaChildFixup(
        RedBlackTreeNode<TNodeKey, TNodeValue> *insertingNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *parentNode = t_nil;
  RedBlackTreeNode<TNodeKey, TNodeValue> *grandpaNode = t_nil;
  RedBlackTreeNode<TNodeKey, TNodeValue> *uncleNode = t_nil;

  parentNode = insertingNode->parent;
  grandpaNode = parentNode->parent;
  uncleNode = grandpaNode->left;

  if (!uncleNode->isBlack) {
    parentNode->isBlack = true;
    uncleNode->isBlack = true;
    grandpaNode->isBlack = false;
    insertingNode = grandpaNode;
  } else {
    if (insertingNode == parentNode->left) {
      insertingNode = parentNode;
      RedBlackTreeRightRotate(insertingNode);

      parentNode = insertingNode->parent;
      grandpaNode = parentNode->parent;
      uncleNode = grandpaNode->left;
    }

    parentNode->isBlack = true;
    grandpaNode->isBlack = false;
    RedBlackTreeLeftRotate(grandpaNode);
  }

  return insertingNode;
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeRemoveNode(
    RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *x = t_nil;
  RedBlackTreeNode<TNodeKey, TNodeValue> *y = t_nil;
  bool isYBlack = false;

  y = removingNode;
  isYBlack = y->isBlack;

  if (removingNode->left == t_nil) {
    x = removingNode->right;
    RedBlackTreeTransplant(removingNode, removingNode->right);
  } else if (removingNode->right == t_nil) {
    x = removingNode->left;
    RedBlackTreeTransplant(removingNode, removingNode->left);
  } else {
    y = RedBlackTreeMinimum(removingNode->right);
    isYBlack = y->isBlack;
    x = y->right;

    if (y->parent == removingNode) {
      x->parent = y;
    } else {
      RedBlackTreeTransplant(y, y->right);
      y->right = removingNode->right;
      y->right->parent = y;
    }

    RedBlackTreeTransplant(removingNode, y);
    y->left = removingNode->left;
    y->left->parent = y;
    y->isBlack = removingNode->isBlack;
  }

  if (isYBlack) {
    RedBlackTreeRemoveFixup(x);
  }

  delete removingNode;
  elementsCount--;
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeTransplant(
    RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode,
    RedBlackTreeNode<TNodeKey, TNodeValue> *transplantapleNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *removingParentNode = t_nil;

  removingParentNode = removingNode->parent;

  if (removingParentNode == t_nil) {
    root = transplantapleNode;
  } else {
    if (removingNode == removingParentNode->right) {
      removingParentNode->right = transplantapleNode;
    } else {
      removingParentNode->left = transplantapleNode;
    }
  }

  transplantapleNode->parent = removingParentNode;
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeRemoveFixup(
    RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *parentNode = t_nil;
  while (removingNode != root && removingNode->isBlack) {
    parentNode = removingNode->parent;

    if (removingNode == parentNode->left) {
      removingNode =
          RedBlackTreeGetLeftChildRemoveFixup(removingNode, parentNode);

    } else {
      removingNode =
          RedBlackTreeGetRightChildRemoveFixup(removingNode, parentNode);
    }
  }

  removingNode->isBlack = true;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeGetLeftChildRemoveFixup(
    RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode,
    RedBlackTreeNode<TNodeKey, TNodeValue> *parentNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *brotherNode = t_nil;

  brotherNode = parentNode->right;

  if (!brotherNode->isBlack) {
    brotherNode->isBlack = true;
    parentNode->isBlack = false;

    RedBlackTreeLeftRotate(parentNode);

    brotherNode = parentNode->right;
  }

  if (brotherNode->left->isBlack && brotherNode->right->isBlack) {
    brotherNode->isBlack = false;
    removingNode = parentNode;
  } else {
    if (brotherNode->right->isBlack) {
      brotherNode->left->isBlack = true;
      brotherNode->isBlack = false;

      RedBlackTreeRightRotate(brotherNode);

      brotherNode = parentNode->right;
    }

    brotherNode->isBlack = parentNode->isBlack;
    parentNode->isBlack = true;
    brotherNode->right->isBlack = true;

    RedBlackTreeLeftRotate(parentNode);
    removingNode = root;
  }

  return removingNode;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeGetRightChildRemoveFixup(
    RedBlackTreeNode<TNodeKey, TNodeValue> *removingNode,
    RedBlackTreeNode<TNodeKey, TNodeValue> *parentNode) {
  RedBlackTreeNode<TNodeKey, TNodeValue> *brotherNode = t_nil;

  brotherNode = parentNode->left;

  if (!brotherNode->isBlack) {
    brotherNode->isBlack = true;
    parentNode->isBlack = false;

    RedBlackTreeRightRotate(parentNode);

    brotherNode = parentNode->left;
  }

  if (brotherNode->left->isBlack && brotherNode->right->isBlack) {
    brotherNode->isBlack = false;
    removingNode = parentNode;
  } else {
    if (brotherNode->left->isBlack) {
      brotherNode->right->isBlack = true;
      brotherNode->isBlack = false;

      RedBlackTreeLeftRotate(brotherNode);

      brotherNode = parentNode->left;
    }

    brotherNode->isBlack = parentNode->isBlack;
    parentNode->isBlack = true;
    brotherNode->left->isBlack = true;

    RedBlackTreeRightRotate(parentNode);
    removingNode = root;
  }

  return removingNode;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeSearch(
    TNodeKey key, RedBlackTreeNode<TNodeKey, TNodeValue> *subtreeRoot) const {
  RedBlackTreeNode<TNodeKey, TNodeValue> *resultNode = t_nil;

  resultNode = subtreeRoot;

  while (resultNode != t_nil && key != resultNode->nodeKey) {
    if (key > resultNode->nodeKey) {
      resultNode = resultNode->right;
    } else {
      resultNode = resultNode->left;
    }
  }
  return resultNode;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreePredecessor(
    RedBlackTreeNode<TNodeKey, TNodeValue> *nextNode) const {
  RedBlackTreeNode<TNodeKey, TNodeValue> *result = t_nil;

  if (nextNode->left != t_nil) {
    result = RedBlackTreeMaximum(nextNode->left);
  } else {
    result = nextNode->parent;

    while (result != t_nil && nextNode == result->left) {
      nextNode = result;
      result = nextNode->parent;
    }
  }

  return result;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeSuccessor(
    RedBlackTreeNode<TNodeKey, TNodeValue> *previousNode) const {
  RedBlackTreeNode<TNodeKey, TNodeValue> *result = t_nil;

  if (previousNode->right != t_nil) {
    result = RedBlackTreeMinimum(previousNode->right);
  } else {
    result = previousNode->parent;

    while (result != t_nil && previousNode == result->right) {
      previousNode = result;
      result = previousNode->parent;
    }
  }

  return result;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeRoot() const {
  return root;
}

template <typename TNodeKey, typename TNodeValue>
RedBlackTreeNode<TNodeKey, TNodeValue> *
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeNil() const {
  return t_nil;
}

template <typename TNodeKey, typename TNodeValue>
pair<bool, RedBlackTreeNode<TNodeKey, TNodeValue> *>
RedBlackTree<TNodeKey, TNodeValue>::RedBlackTreeInsert(
    const TNodeKey &key, const TNodeValue &value) {
  auto *newNode = new RedBlackTreeNode<TNodeKey, TNodeValue>;
  newNode->nodeKey = key;
  newNode->nodeValue = value;

  RedBlackTreeInsertNode(newNode);

  return {true, newNode};
}

template <typename TNodeKey, typename TNodeValue>
void RedBlackTree<TNodeKey, TNodeValue>::resetTree() {
  root = t_nil;
  elementsCount = 0;
}
}  // namespace my_tree
#endif  // my_REDBLACKTREE_TPP