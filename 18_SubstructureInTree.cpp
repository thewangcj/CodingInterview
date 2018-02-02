// 树的子结构
// 题目：输入两棵二叉树A和B，判断B是不是A的子结构。
#include <iostream>
#include "./utils/BinaryTree.h"
using namespace std;

bool IsTree1HasTree2(BinaryTreeNode* tree1, BinaryTreeNode* tree2) {
  // 考虑到当 tree1 tree2 同时为空时，要先判断 tree2，否则返回 false
  if(tree2 == NULL)
    return true;
  if(tree1 == NULL)
    return false;

  if(tree1->value != tree2->value)
    return false;

  return IsTree1HasTree2(tree1->left, tree2->left) && IsTree1HasTree2(tree1->right, tree2->right);
}

bool HasSubTree(BinaryTreeNode* tree1, BinaryTreeNode* tree2) {
  bool result = false;

  if(tree1 != NULL && tree2 != NULL){
    if(tree1->value == tree2->value) {
      result = IsTree1HasTree2(tree1, tree2);
    }
    if(!result){
      result = HasSubTree(tree1->left, tree2);
    }
    if(!result){
      result = HasSubTree(tree1->right, tree2);
    }
  }

  return result;
}


// ====================测试代码====================
void Test(const char* testName, BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2, bool expected)
{
  if(HasSubTree(pRoot1, pRoot2) == expected)
    printf(" %s passed.\n", testName);
  else
    printf(" %s failed.\n", testName);
}

// 树中结点含有分叉，树B是树A的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     2
//               / \
//              4   7
void Test1()
{
  BinaryTreeNode* pNodeA1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA2 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA3 = CreateBiTreeNode(7);
  BinaryTreeNode* pNodeA4 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeA5 = CreateBiTreeNode(2);
  BinaryTreeNode* pNodeA6 = CreateBiTreeNode(4);
  BinaryTreeNode* pNodeA7 = CreateBiTreeNode(7);

  ConnectBinTreeNodes(pNodeA1, pNodeA2, pNodeA3);
  ConnectBinTreeNodes(pNodeA2, pNodeA4, pNodeA5);
  ConnectBinTreeNodes(pNodeA5, pNodeA6, pNodeA7);

  BinaryTreeNode* pNodeB1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeB2 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeB3 = CreateBiTreeNode(2);

  ConnectBinTreeNodes(pNodeB1, pNodeB2, pNodeB3);

  Test("Test1", pNodeA1, pNodeB1, true);
  //PrintBinTree(pNodeA1);
  DestoryBinTree(pNodeA1);
  DestoryBinTree(pNodeB1);
}

// 树中结点含有分叉，树B不是树A的子结构
//                  8                8
//              /       \           / \
//             8         7         9   2
//           /   \
//          9     3
//               / \
//              4   7
void Test2()
{
  BinaryTreeNode* pNodeA1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA2 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA3 = CreateBiTreeNode(7);
  BinaryTreeNode* pNodeA4 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeA5 = CreateBiTreeNode(3);
  BinaryTreeNode* pNodeA6 = CreateBiTreeNode(4);
  BinaryTreeNode* pNodeA7 = CreateBiTreeNode(7);

  ConnectBinTreeNodes(pNodeA1, pNodeA2, pNodeA3);
  ConnectBinTreeNodes(pNodeA2, pNodeA4, pNodeA5);
  ConnectBinTreeNodes(pNodeA5, pNodeA6, pNodeA7);

  BinaryTreeNode* pNodeB1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeB2 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeB3 = CreateBiTreeNode(2);

  ConnectBinTreeNodes(pNodeB1, pNodeB2, pNodeB3);

  Test("Test2", pNodeA1, pNodeB1, false);
  //PrintBinTree(pNodeB1);
  DestoryBinTree(pNodeA1);
  DestoryBinTree(pNodeB1);
}

// 树中结点只有左子结点，树B是树A的子结构
//                8                  8
//              /                   /
//             8                   9
//           /                    /
//          9                    2
//         /
//        2
//       /
//      5
void Test3()
{
  BinaryTreeNode* pNodeA1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA2 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA3 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeA4 = CreateBiTreeNode(2);
  BinaryTreeNode* pNodeA5 = CreateBiTreeNode(5);

  ConnectBinTreeNodes(pNodeA1, pNodeA2, NULL);
  ConnectBinTreeNodes(pNodeA2, pNodeA3, NULL);
  ConnectBinTreeNodes(pNodeA3, pNodeA4, NULL);
  ConnectBinTreeNodes(pNodeA4, pNodeA5, NULL);

  BinaryTreeNode* pNodeB1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeB2 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeB3 = CreateBiTreeNode(2);

  ConnectBinTreeNodes(pNodeB1, pNodeB2, NULL);
  ConnectBinTreeNodes(pNodeB2, pNodeB3, NULL);

  Test("Test3", pNodeA1, pNodeB1, true);

  DestoryBinTree(pNodeA1);
  DestoryBinTree(pNodeB1);
}

// 树中结点只有左子结点，树B不是树A的子结构
//                8                  8
//              /                   /
//             8                   9
//           /                    /
//          9                    3
//         /
//        2
//       /
//      5
void Test4()
{
  BinaryTreeNode* pNodeA1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA2 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA3 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeA4 = CreateBiTreeNode(2);
  BinaryTreeNode* pNodeA5 = CreateBiTreeNode(5);

  ConnectBinTreeNodes(pNodeA1, pNodeA2, NULL);
  ConnectBinTreeNodes(pNodeA2, pNodeA3, NULL);
  ConnectBinTreeNodes(pNodeA3, pNodeA4, NULL);
  ConnectBinTreeNodes(pNodeA4, pNodeA5, NULL);

  BinaryTreeNode* pNodeB1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeB2 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeB3 = CreateBiTreeNode(3);

  ConnectBinTreeNodes(pNodeB1, pNodeB2, NULL);
  ConnectBinTreeNodes(pNodeB2, pNodeB3, NULL);

  Test("Test4", pNodeA1, pNodeB1, false);

  DestoryBinTree(pNodeA1);
  DestoryBinTree(pNodeB1);
}

// 树中结点只有右子结点，树B是树A的子结构
//       8                   8
//        \                   \
//         8                   9
//          \                   \
//           9                   2
//            \
//             2
//              \
//               5
void Test5()
{
  BinaryTreeNode* pNodeA1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA2 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA3 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeA4 = CreateBiTreeNode(2);
  BinaryTreeNode* pNodeA5 = CreateBiTreeNode(5);

  ConnectBinTreeNodes(pNodeA1, NULL, pNodeA2);
  ConnectBinTreeNodes(pNodeA2, NULL, pNodeA3);
  ConnectBinTreeNodes(pNodeA3, NULL, pNodeA4);
  ConnectBinTreeNodes(pNodeA4, NULL, pNodeA5);

  BinaryTreeNode* pNodeB1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeB2 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeB3 = CreateBiTreeNode(2);

  ConnectBinTreeNodes(pNodeB1, NULL, pNodeB2);
  ConnectBinTreeNodes(pNodeB2, NULL, pNodeB3);

  Test("Test5", pNodeA1, pNodeB1, true);

  DestoryBinTree(pNodeA1);
  DestoryBinTree(pNodeB1);
}

// 树A中结点只有右子结点，树B不是树A的子结构
//       8                   8
//        \                   \
//         8                   9
//          \                 / \
//           9               3   2
//            \
//             2
//              \
//               5
void Test6()
{
  BinaryTreeNode* pNodeA1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA2 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA3 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeA4 = CreateBiTreeNode(2);
  BinaryTreeNode* pNodeA5 = CreateBiTreeNode(5);

  ConnectBinTreeNodes(pNodeA1, NULL, pNodeA2);
  ConnectBinTreeNodes(pNodeA2, NULL, pNodeA3);
  ConnectBinTreeNodes(pNodeA3, NULL, pNodeA4);
  ConnectBinTreeNodes(pNodeA4, NULL, pNodeA5);

  BinaryTreeNode* pNodeB1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeB2 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeB3 = CreateBiTreeNode(3);
  BinaryTreeNode* pNodeB4 = CreateBiTreeNode(2);

  ConnectBinTreeNodes(pNodeB1, NULL, pNodeB2);
  ConnectBinTreeNodes(pNodeB2, pNodeB3, pNodeB4);

  Test("Test6", pNodeA1, pNodeB1, false);

  DestoryBinTree(pNodeA1);
  DestoryBinTree(pNodeB1);
}

// 树A为空树
void Test7()
{
  BinaryTreeNode* pNodeB1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeB2 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeB3 = CreateBiTreeNode(3);
  BinaryTreeNode* pNodeB4 = CreateBiTreeNode(2);

  ConnectBinTreeNodes(pNodeB1, NULL, pNodeB2);
  ConnectBinTreeNodes(pNodeB2, pNodeB3, pNodeB4);

  Test("Test7", NULL, pNodeB1, false);

  DestoryBinTree(pNodeB1);
}

// 树B为空树
void Test8()
{
  BinaryTreeNode* pNodeA1 = CreateBiTreeNode(8);
  BinaryTreeNode* pNodeA2 = CreateBiTreeNode(9);
  BinaryTreeNode* pNodeA3 = CreateBiTreeNode(3);
  BinaryTreeNode* pNodeA4 = CreateBiTreeNode(2);

  ConnectBinTreeNodes(pNodeA1, NULL, pNodeA2);
  ConnectBinTreeNodes(pNodeA2, pNodeA3, pNodeA4);

  Test("Test8", pNodeA1, NULL, false);

  DestoryBinTree(pNodeA1);
}

// 树A和树B都为空
void Test9()
{
  Test("Test9", NULL, NULL, false);
}

int main(int argc, char const *argv[]) {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();
  Test8();
  Test9();
  return 0;
}
