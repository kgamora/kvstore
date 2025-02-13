#ifndef TEST_BUILD
#define TEST_BUILD
#endif // !TEST_BUILD

#include "avl_tree.hpp"

#include <cstddef>
#include <gtest/gtest.h>

namespace {
struct empty {};
} // namespace

namespace keyvaluestorage::core::tests {

class AVLTreeTest : public ::testing::Test {
protected:
  struct empty {};
  using TTree = keyvaluestorage::core::AVLTree<size_t, empty>;
  using TTreeIter = typename TTree::iterator;
};

TEST_F(AVLTreeTest, RotateLeftTest) {
  auto rNode = TTree::makeNode('r', {}, {}, {}, 0);
  auto qNode = TTree::makeNode('q', {}, {}, {}, 0);
  auto bNode = TTree::makeNode('b', {}, qNode, rNode, 1);
  auto pNode = TTree::makeNode('p', {}, {}, {}, 0);
  auto aNode = TTree::makeNode('a', {}, pNode, bNode, 2);
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
  auto rNode = TTree::makeNode('r', {}, {}, {}, 1);
  auto qNode = TTree::makeNode('q', {}, {}, {}, 1);
  auto bNode = TTree::makeNode('b', {}, qNode, rNode, 2);
  auto pNode = TTree::makeNode('p', {}, {}, {}, 0);
  auto aNode = TTree::makeNode('a', {}, pNode, bNode, 3);
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
  auto pNode = TTree::makeNode('p', {}, {}, {}, 0);
  auto qNode = TTree::makeNode('q', {}, {}, {}, 0);
  auto aNode = TTree::makeNode('a', {}, pNode, qNode, 1);
  auto rNode = TTree::makeNode('r', {}, {}, {}, 0);
  auto bNode = TTree::makeNode('b', {}, aNode, rNode, 2);
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
  auto pNode = TTree::makeNode('p', {}, {}, {}, 1);
  auto qNode = TTree::makeNode('q', {}, {}, {}, 1);
  auto aNode = TTree::makeNode('a', {}, pNode, qNode, 2);
  auto rNode = TTree::makeNode('r', {}, {}, {}, 0);
  auto bNode = TTree::makeNode('b', {}, aNode, rNode, 3);
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
  auto qNode = TTree::makeNode('q', {}, {}, {}, 0);
  auto rNode = TTree::makeNode('r', {}, {}, {}, 0);
  auto cNode = TTree::makeNode('c', {}, qNode, rNode, 1);
  auto sNode = TTree::makeNode('s', {}, {}, {}, 0);
  auto bNode = TTree::makeNode('b', {}, cNode, sNode, 2);
  auto pNode = TTree::makeNode('p', {}, {}, {}, 0);
  auto aNode = TTree::makeNode('a', {}, pNode, bNode, 3);
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
  auto qNode = TTree::makeNode('q', {}, {}, {}, 0);
  auto rNode = TTree::makeNode('r', {}, {}, {}, 0);
  auto cNode = TTree::makeNode('c', {}, qNode, rNode, 1);
  auto sNode = TTree::makeNode('s', {}, {}, {}, 0);
  auto bNode = TTree::makeNode('b', {}, cNode, sNode, 2);
  auto pNode = TTree::makeNode('p', {}, {}, {}, 0);
  auto aNode = TTree::makeNode('a', {}, pNode, bNode, 3);
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
  auto qNode = TTree::makeNode('q', {}, {}, {}, 0);
  auto rNode = TTree::makeNode('r', {}, {}, {}, 0);
  auto cNode = TTree::makeNode('c', {}, rNode, qNode, 1);
  auto sNode = TTree::makeNode('s', {}, {}, {}, 0);
  auto bNode = TTree::makeNode('b', {}, sNode, cNode, 2);
  auto pNode = TTree::makeNode('p', {}, {}, {}, 0);
  auto aNode = TTree::makeNode('a', {}, bNode, pNode, 3);
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
  auto qNode = TTree::makeNode('q', {}, {}, {}, 0);
  auto rNode = TTree::makeNode('r', {}, {}, {}, 0);
  auto cNode = TTree::makeNode('c', {}, rNode, qNode, 1);
  auto sNode = TTree::makeNode('s', {}, {}, {}, 0);
  auto bNode = TTree::makeNode('b', {}, sNode, cNode, 2);
  auto pNode = TTree::makeNode('p', {}, {}, {}, 0);
  auto aNode = TTree::makeNode('a', {}, bNode, pNode, 3);
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

TEST_F(AVLTreeTest, TestIteratorFollowsInputIteratorConcept) {
  EXPECT_TRUE(std::input_iterator<TTreeIter>);
}

TEST_F(AVLTreeTest, TestIteratorTraverse) {
  auto aNode = TTree::makeNode('a', {}, {}, {}, 0);
  auto cNode = TTree::makeNode('c', {}, {}, {}, 0);
  auto bNode = TTree::makeNode('b', {}, aNode, cNode, 1);
  auto eNode = TTree::makeNode('e', {}, {}, {}, 0);
  auto gNode = TTree::makeNode('g', {}, {}, {}, 0);
  auto fNode = TTree::makeNode('f', {}, eNode, gNode, 1);
  auto dNode = TTree::makeNode('d', {}, bNode, fNode, 2);
  TTree tree{dNode};
  TTreeIter it = tree.begin();
  EXPECT_NE(it, tree.end());
  EXPECT_EQ(*(*it++).key, 'a');
  EXPECT_EQ(*(*it++).key, 'b');
  EXPECT_EQ(*(*it++).key, 'c');
  EXPECT_EQ(*(*it++).key, 'd');
  EXPECT_EQ(*(*it++).key, 'e');
  EXPECT_EQ(*(*it++).key, 'f');
  EXPECT_EQ(*(*it++).key, 'g');
  EXPECT_EQ(it, tree.end());
}

TEST_F(AVLTreeTest, TestInsert) {
  TTree tree(3);
  tree.insert('b', {});
  tree.insert('d', {});
  tree.insert('a', {});
  tree.insert('e', {});
  tree.insert('c', {});
  tree.insert('f', {});
  tree.insert('g', {});
  std::vector<char> keys {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
  auto keyIt = keys.begin();
  for (auto it = tree.begin(); it != tree.end(); it++) {
    EXPECT_NE(keyIt, keys.end());
    const auto& [keyPtr, valPtr] = *it;
    EXPECT_EQ(*keyIt, *keyPtr);
    keyIt++;
  }
  EXPECT_TRUE(tree.root->height <= 3);
}
} // namespace keyvaluestorage::core::tests

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
