#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <stack>


namespace keyvaluestorage::core {

// TODO: we want K to be of fixed size
// TODO: we want to have some method to get a binary representation of V
template <class K, class V, class Cmp = std::less<>> class AVLTree {
#ifdef TEST_BUILD
public:
#endif // TEST_BUILD
  struct AVLNode;

  using THeight = uint16_t;
  using THeightDiff = int8_t;
  using TNodePtr = std::shared_ptr<AVLNode>;

public:
  using TKey = const K;
  using TValue = V;
  using TKeyPtr = std::unique_ptr<const K>;
  using TValuePtr = std::unique_ptr<V>;

private:
#ifdef TEST_BUILD
public:
#endif // TEST_BUILD
  struct AVLNode {
    TKeyPtr key;
    TValuePtr value;
    TNodePtr left;
    TNodePtr right;
    THeight height;
  };

  static inline TNodePtr makeNode(const TKey &key, const TValue &value,
                                  TNodePtr left = {}, TNodePtr right = {},
                                  THeight height = {}) {
    return std::make_unique<AVLNode>(std::make_unique<TKey>(key),
                                     std::make_unique<TValue>(value), left,
                                     right, height);
  }

  THeight height;
  TNodePtr root;

public:
  // TODO: I want an stl type iterator
  class iterator {
    friend AVLTree;
  };

  explicit AVLTree(THeight height) : height(height) {}
  ~AVLTree() = default;

  // Modification
  std::pair<iterator, bool> insert(TKey &key, const TValue &value) {
    TNodePtr newNode = makeNode(key, value);

    if (!root) {
      root = newNode;
      return {{root}, true};
    }

    std::stack<TNodePtr *> stack;
    stack.reserve(root.height);

    auto currentNodePtr = &root;
    while (*currentNodePtr) {
      auto &currentNode = *currentNodePtr;
      auto &currentKey = *currentNode->key;
      if (equal_(currentKey, key)) { // TODO: use cmp
        return {end(), false};
      }
      stack.push(currentNodePtr);
      currentNodePtr =
          less_(key, currentKey) ? &currentNode->left : &currentNode->right;
    }
    *currentNodePtr = newNode;
    std::pair<iterator, bool> result{{newNode}, true};

    while (!stack.empty()) {
      currentNodePtr = stack.pop();
      auto &currentNode = *currentNodePtr;
      recalculateHeight_(currentNode);
      currentNode = rebalanceAt_(currentNode);
    }

    return result;
  }

  //// Iterators
  // iterator find(const K &key);
  // iterator begin();
  iterator end();

#ifndef TEST_BUILD
private:
#endif // !TEST_BUILD

  // Misc
  // Rebalance and return local 'root'
  static TNodePtr rebalanceAt_(TNodePtr node) {
    auto heightDiff = heightDiff_(node);
    if (std::abs(heightDiff) < 2) {
      return node;
    }

    bool rightRotate = signum(heightDiff);
    if (rightRotate) {
      auto &lNode = node->left;
      if (heightDiff_(lNode) == -1) {
        return bigRotateRight_(node);
      }
      return rotateRight_(node);
    }

    auto &rNode = node->right;
    if (heightDiff_(rNode) == 1) {
      return bigRotateLeft_(node);
    }
    return rotateLeft_(node);
  }
  // Rotations: rotate and return local 'root'
  static TNodePtr rotateRight_(TNodePtr node) noexcept {
    TNodePtr l = node->left;
    TNodePtr lr = l->right;

    // Rotate right
    node->left = lr;
    l->right = node;

    // Recalculate heights
    THeight zero{};
    adjustHeight_(node);
    adjustHeight_(l);

    return l;
  }

  static TNodePtr rotateLeft_(TNodePtr node) noexcept {
    THeight nodeHeight = node->height;

    TNodePtr r = node->right;
    TNodePtr rl = r->left;

    // Rotate left
    node->right = rl;
    r->left = node;

    // Recalculate heights
    THeight zero{};
    adjustHeight_(node);
    adjustHeight_(r);

    return r;
  }

  static TNodePtr bigRotateLeft_(TNodePtr node) noexcept {
    node->right = rotateRight_(node->right);
    return rotateLeft_(node);
  }

  static TNodePtr bigRotateRight_(TNodePtr node) noexcept {
    node->left = rotateLeft_(node->left);
    return rotateRight_(node);
  }

  // Comparisons
  inline bool equal_(TKey &lhs, TKey &rhs) const {
    return !cmp_(lhs, rhs) && !cmp_(rhs, lhs);
  }

  inline bool less_(TKey &lhs, TKey &rhs) const { return cmp_(lhs, rhs); }

  // Node utils

  inline static std::pair<THeight, THeight>
  childHeights_(const TNodePtr &node) {
    auto &left = node->left;
    auto &right = node->right;

    THeight zero{};
    return {left ? left->height : zero, right ? right->height : zero};
  }

  inline static void adjustHeight_(TNodePtr &node) {
    auto [lHeight, rHeight] = childHeights_(node);
    node->height = std::max(lHeight, rHeight) + 1;
  }

  inline static THeightDiff heightDiff_(const TNodePtr &node) {
    auto [lHeight, rHeight] = childHeights_(node);
    return lHeight - rHeight;
  }

  inline static bool signum(THeightDiff diff) { return diff > 0; }
};

} // namespace keyvaluestorage::core
