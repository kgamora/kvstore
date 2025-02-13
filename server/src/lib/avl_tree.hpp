#pragma once

#include <algorithm>
#include <cstdint>
#include <exception>
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
    struct TData {
      TKeyPtr key;
      TValuePtr value;
    };
    TData data;
    TNodePtr left;
    TNodePtr right;
    THeight height;
  };

  static inline TNodePtr makeNode(const TKey &key, const TValue &value,
                                  TNodePtr left = {}, TNodePtr right = {},
                                  THeight height = {}) {
    using TNodeData = typename AVLNode::TData;
    return std::make_unique<AVLNode>(
        TNodeData(std::make_unique<TKey>(key), std::make_unique<TValue>(value)),
        left, right, height);
  }

  THeight height;
  TNodePtr root;
  Cmp cmp_;

public:
  // TODO: I want an stl type iterator
  class iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = typename AVLNode::TData;

  public:
    iterator() = default;
    iterator(const std::stack<TNodePtr *> &stack) : stack_(stack) {}

    value_type &operator*() const { return (*stack_.top())->data; }

    bool operator==(const iterator &) const = default;

    iterator &operator++() {
      if (stack_.empty()) {
        throw std::exception();
      }

      auto currentNodePtr = &(*stack_.top())->right;
      stack_.pop();
      if (!*currentNodePtr) {
        return *this;
      }
      stack_.push(currentNodePtr);

      while ((*currentNodePtr)->left) {
        currentNodePtr = &(*currentNodePtr)->left;
        stack_.push(currentNodePtr);
      }

      return *this;
    }

    iterator operator++(int) {
      iterator old = *this;
      operator++();
      return old;
    }

  private:
    std::stack<TNodePtr *> stack_;
    friend AVLTree;
  };

  explicit AVLTree(THeight height) : height(height) {}
  ~AVLTree() = default;

#ifdef TEST_BUILD
  explicit AVLTree(TNodePtr root) : root(root) {
    if (root) {
      height = root->height;
    }
  }
#endif // TEST_BUILD

  // Modification
  std::pair<iterator, bool> insert(TKey &key, const TValue &value) {
    TNodePtr newNode = makeNode(key, value);

    std::stack<TNodePtr *> stack;

    if (!root) {
      root = newNode;
      stack.push(&root);
      return {{stack}, true};
    }

    auto currentNodePtr = &root;
    while (*currentNodePtr) {
      auto &currentNode = *currentNodePtr;
      auto &currentKey = *currentNode->data.key;
      if (equal_(currentKey, key)) {
        return {end(), false};
      }
      stack.push(currentNodePtr);
      currentNodePtr =
          less_(key, currentKey) ? &currentNode->left : &currentNode->right;
    }
    *currentNodePtr = newNode;

    stack.push(currentNodePtr);
    std::pair<iterator, bool> result{{stack}, true};
    stack.pop();

    while (!stack.empty()) {
      currentNodePtr = stack.top();
      stack.pop();
      auto &currentNode = *currentNodePtr;
      adjustHeight_(currentNode);
      currentNode = rebalanceAt_(currentNode);
    }

    return result;
  }

  //// Iterators
  // iterator find(const K &key);
  iterator begin() {
    if (!root) {
      return {};
    }
    std::stack<TNodePtr *> stack;

    TNodePtr *currentNodePtr = &root;
    while (*currentNodePtr) {
      stack.push(currentNodePtr);
      currentNodePtr = &(*currentNodePtr)->left;
    }
    return {stack};
  }

  iterator end() const { return {}; }

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
