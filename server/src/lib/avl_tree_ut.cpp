#include "avl_tree.hpp"

#include <cstddef>
#include <gtest/gtest.h>
#include <memory>

namespace {
struct empty {};
} // namespace

namespace keyvaluestorage::core::tests {

class AVLTreeTest : public ::testing::Test {
protected:
  struct empty {};
  using TTree = keyvaluestorage::core::AVLTree<size_t, empty>;

public:
  static TTree::TNodePtr makeNode(TTree::TKey key, TTree::TValue value,
                                  TTree::TNodePtr left, TTree::TNodePtr right,
                                  TTree::THeight height) {
    return std::make_shared<TTree::AVLNode>(
        std::make_unique<TTree::TKey>(key),
        std::make_unique<TTree::TValue>(value), left, right, height);
  };
};

TEST_F(AVLTreeTest, RotateLeftTest) {
  auto rNode = makeNode('r', {}, {}, {}, 0);
  auto qNode = makeNode('q', {}, {}, {}, 0);
  auto bNode = makeNode('b', {}, qNode, rNode, 1);
  auto pNode = makeNode('p', {}, {}, {}, 0);
  auto aNode = makeNode('a', {}, pNode, bNode, 2);
  EXPECT_EQ(TTree::rotateLeft_(aNode), bNode);
  EXPECT_EQ(bNode->height, 2);
  EXPECT_EQ(bNode->left, aNode);
  EXPECT_EQ(aNode->height, 1);
  EXPECT_EQ(bNode->right, rNode);
  EXPECT_EQ(rNode->height, 0);
  EXPECT_EQ(aNode->left, pNode);
  EXPECT_EQ(pNode->height, 0);
  EXPECT_EQ(aNode->right, qNode);
  EXPECT_EQ(qNode->height, 0);
}

TEST_F(AVLTreeTest, RebalanceRotateLeftTest) {
  auto rNode = makeNode('r', {}, {}, {}, 1);
  auto qNode = makeNode('q', {}, {}, {}, 1);
  auto bNode = makeNode('b', {}, qNode, rNode, 2);
  auto pNode = makeNode('p', {}, {}, {}, 0);
  auto aNode = makeNode('a', {}, pNode, bNode, 3);
  EXPECT_EQ(TTree::rebalanceAt_(aNode), bNode);
  EXPECT_EQ(bNode->height, 3);
  EXPECT_EQ(bNode->left, aNode);
  EXPECT_EQ(aNode->height, 2);
  EXPECT_EQ(bNode->right, rNode);
  EXPECT_EQ(rNode->height, 1);
  EXPECT_EQ(aNode->left, pNode);
  EXPECT_EQ(pNode->height, 0);
  EXPECT_EQ(aNode->right, qNode);
  EXPECT_EQ(qNode->height, 1);
}

TEST_F(AVLTreeTest, RotateRightTest) {
  auto pNode = makeNode('p', {}, {}, {}, 0);
  auto qNode = makeNode('q', {}, {}, {}, 0);
  auto aNode = makeNode('a', {}, pNode, qNode, 1);
  auto rNode = makeNode('r', {}, {}, {}, 0);
  auto bNode = makeNode('b', {}, aNode, rNode, 2);
  EXPECT_EQ(TTree::rotateRight_(bNode), aNode);
  EXPECT_EQ(aNode->height, 2);
  EXPECT_EQ(aNode->right, bNode);
  EXPECT_EQ(bNode->height, 1);
  EXPECT_EQ(aNode->left, pNode);
  EXPECT_EQ(pNode->height, 0);
  EXPECT_EQ(bNode->left, qNode);
  EXPECT_EQ(qNode->height, 0);
  EXPECT_EQ(bNode->right, rNode);
  EXPECT_EQ(rNode->height, 0);
}

TEST_F(AVLTreeTest, RebalanceRotateRightTest) {
  auto pNode = makeNode('p', {}, {}, {}, 1);
  auto qNode = makeNode('q', {}, {}, {}, 1);
  auto aNode = makeNode('a', {}, pNode, qNode, 2);
  auto rNode = makeNode('r', {}, {}, {}, 0);
  auto bNode = makeNode('b', {}, aNode, rNode, 3);
  EXPECT_EQ(TTree::rebalanceAt_(bNode), aNode);
  EXPECT_EQ(aNode->height, 3);
  EXPECT_EQ(aNode->right, bNode);
  EXPECT_EQ(bNode->height, 2);
  EXPECT_EQ(aNode->left, pNode);
  EXPECT_EQ(pNode->height, 1);
  EXPECT_EQ(bNode->left, qNode);
  EXPECT_EQ(qNode->height, 1);
  EXPECT_EQ(bNode->right, rNode);
  EXPECT_EQ(rNode->height, 0);
}

TEST_F(AVLTreeTest, BigRotateLeftTest) {
  auto qNode = makeNode('q', {}, {}, {}, 0);
  auto rNode = makeNode('r', {}, {}, {}, 0);
  auto cNode = makeNode('c', {}, qNode, rNode, 1);
  auto sNode = makeNode('s', {}, {}, {}, 0);
  auto bNode = makeNode('b', {}, cNode, sNode, 2);
  auto pNode = makeNode('p', {}, {}, {}, 0);
  auto aNode = makeNode('a', {}, pNode, bNode, 3);
  EXPECT_EQ(TTree::bigRotateLeft_(aNode), cNode);
  EXPECT_EQ(cNode->height, 2);
  EXPECT_EQ(cNode->left, aNode);
  EXPECT_EQ(aNode->height, 1);
  EXPECT_EQ(cNode->right, bNode);
  EXPECT_EQ(bNode->height, 1);
  EXPECT_EQ(aNode->left, pNode);
  EXPECT_EQ(pNode->height, 0);
  EXPECT_EQ(aNode->right, qNode);
  EXPECT_EQ(qNode->height, 0);
  EXPECT_EQ(bNode->left, rNode);
  EXPECT_EQ(rNode->height, 0);
  EXPECT_EQ(bNode->right, sNode);
  EXPECT_EQ(sNode->height, 0);
}

TEST_F(AVLTreeTest, RebalanceBigRotateLeftTest) {
  auto qNode = makeNode('q', {}, {}, {}, 0);
  auto rNode = makeNode('r', {}, {}, {}, 0);
  auto cNode = makeNode('c', {}, qNode, rNode, 1);
  auto sNode = makeNode('s', {}, {}, {}, 0);
  auto bNode = makeNode('b', {}, cNode, sNode, 2);
  auto pNode = makeNode('p', {}, {}, {}, 0);
  auto aNode = makeNode('a', {}, pNode, bNode, 3);
  EXPECT_EQ(TTree::rebalanceAt_(aNode), cNode);
  EXPECT_EQ(cNode->height, 2);
  EXPECT_EQ(cNode->left, aNode);
  EXPECT_EQ(aNode->height, 1);
  EXPECT_EQ(cNode->right, bNode);
  EXPECT_EQ(bNode->height, 1);
  EXPECT_EQ(aNode->left, pNode);
  EXPECT_EQ(pNode->height, 0);
  EXPECT_EQ(aNode->right, qNode);
  EXPECT_EQ(qNode->height, 0);
  EXPECT_EQ(bNode->left, rNode);
  EXPECT_EQ(rNode->height, 0);
  EXPECT_EQ(bNode->right, sNode);
  EXPECT_EQ(sNode->height, 0);
}

TEST_F(AVLTreeTest, BigRotateRightTest) {
  auto qNode = makeNode('q', {}, {}, {}, 0);
  auto rNode = makeNode('r', {}, {}, {}, 0);
  auto cNode = makeNode('c', {}, rNode, qNode, 1);
  auto sNode = makeNode('s', {}, {}, {}, 0);
  auto bNode = makeNode('b', {}, sNode, cNode, 2);
  auto pNode = makeNode('p', {}, {}, {}, 0);
  auto aNode = makeNode('a', {}, bNode, pNode, 3);
  EXPECT_EQ(TTree::bigRotateRight_(aNode), cNode);
  EXPECT_EQ(cNode->height, 2);
  EXPECT_EQ(cNode->left, bNode);
  EXPECT_EQ(aNode->height, 1);
  EXPECT_EQ(cNode->right, aNode);
  EXPECT_EQ(bNode->height, 1);
  EXPECT_EQ(aNode->left, qNode);
  EXPECT_EQ(pNode->height, 0);
  EXPECT_EQ(aNode->right, pNode);
  EXPECT_EQ(qNode->height, 0);
  EXPECT_EQ(bNode->left, sNode);
  EXPECT_EQ(rNode->height, 0);
  EXPECT_EQ(bNode->right, rNode);
  EXPECT_EQ(sNode->height, 0);
}

TEST_F(AVLTreeTest, RebalanceBigRotateRightTest) {
  auto qNode = makeNode('q', {}, {}, {}, 0);
  auto rNode = makeNode('r', {}, {}, {}, 0);
  auto cNode = makeNode('c', {}, rNode, qNode, 1);
  auto sNode = makeNode('s', {}, {}, {}, 0);
  auto bNode = makeNode('b', {}, sNode, cNode, 2);
  auto pNode = makeNode('p', {}, {}, {}, 0);
  auto aNode = makeNode('a', {}, bNode, pNode, 3);
  EXPECT_EQ(TTree::rebalanceAt_(aNode), cNode);
  EXPECT_EQ(cNode->height, 2);
  EXPECT_EQ(cNode->left, bNode);
  EXPECT_EQ(aNode->height, 1);
  EXPECT_EQ(cNode->right, aNode);
  EXPECT_EQ(bNode->height, 1);
  EXPECT_EQ(aNode->left, qNode);
  EXPECT_EQ(pNode->height, 0);
  EXPECT_EQ(aNode->right, pNode);
  EXPECT_EQ(qNode->height, 0);
  EXPECT_EQ(bNode->left, sNode);
  EXPECT_EQ(rNode->height, 0);
  EXPECT_EQ(bNode->right, rNode);
  EXPECT_EQ(sNode->height, 0);
}
} // namespace keyvaluestorage::core::tests

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
