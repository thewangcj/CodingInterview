#include <iostream>
#include <stack>
#include "./utils/BinaryTree.h"
using namespace std;

void MirrorOfBinTree(BinaryTreeNode* bin_tree) {
  if(bin_tree == NULL)
    return;
  if(bin_tree->left == NULL && bin_tree == NULL)
    return;

  BinaryTreeNode* tmp = bin_tree->left;
  bin_tree->left = bin_tree->right;
  bin_tree->right = tmp;

  if(bin_tree->left)
    MirrorOfBinTree(bin_tree->left);
  if(bin_tree->right)
    MirrorOfBinTree(bin_tree->right);
}

void MirrorOfBinTreeItera(BinaryTreeNode* bin_tree) {
  if(bin_tree == NULL)
    return;
    stack<BinaryTreeNode*> tree_stack;
    tree_stack.push(bin_tree);

    while (tree_stack.size() > 0) {
      BinaryTreeNode* p = tree_stack.top();
      tree_stack.pop();

      BinaryTreeNode* tmp = p->left;
      p->left = p->right;
      p->right = tmp;
      if(p->left)
        tree_stack.push(p->left);
      if(p->right)
        tree_stack.push(p->right);
    }
}

// 测试完全二叉树：除了叶子节点，其他节点都有两个子节点
//            8
//        6      10
//       5 7    9  11
void Test1()
{
  printf("\n=====Test1 starts:=====\n");
  BinaryTreeNode* pNode8 = CreateBiTreeNode(8);
  BinaryTreeNode* pNode6 = CreateBiTreeNode(6);
  BinaryTreeNode* pNode10 = CreateBiTreeNode(10);
  BinaryTreeNode* pNode5 = CreateBiTreeNode(5);
  BinaryTreeNode* pNode7 = CreateBiTreeNode(7);
  BinaryTreeNode* pNode9 = CreateBiTreeNode(9);
  BinaryTreeNode* pNode11 = CreateBiTreeNode(11);

  ConnectBinTreeNodes(pNode8, pNode6, pNode10);
  ConnectBinTreeNodes(pNode6, pNode5, pNode7);
  ConnectBinTreeNodes(pNode10, pNode9, pNode11);

  PrintBinTree(pNode8);

  printf("\n=====Test1: MirrorOfBinTree=====\n");
  MirrorOfBinTree(pNode8);
  PrintBinTree(pNode8);

  printf("\n=====Test1: MirrorOfBinTreeItera=====\n");
  MirrorOfBinTreeItera(pNode8);
  PrintBinTree(pNode8);

  DestoryBinTree(pNode8);
}

// 测试二叉树：出叶子结点之外，左右的结点都有且只有一个左子结点
//            8
//          7
//        6
//      5
//    4
void Test2()
{
  printf("\n=====Test2 starts:=====\n");
  BinaryTreeNode* pNode8 = CreateBiTreeNode(8);
  BinaryTreeNode* pNode7 = CreateBiTreeNode(7);
  BinaryTreeNode* pNode6 = CreateBiTreeNode(6);
  BinaryTreeNode* pNode5 = CreateBiTreeNode(5);
  BinaryTreeNode* pNode4 = CreateBiTreeNode(4);

  ConnectBinTreeNodes(pNode8, pNode7, NULL);
  ConnectBinTreeNodes(pNode7, pNode6, NULL);
  ConnectBinTreeNodes(pNode6, pNode5, NULL);
  ConnectBinTreeNodes(pNode5, pNode4, NULL);

  PrintBinTree(pNode8);

  printf("\n=====Test2: MirrorOfBinTree=====\n");
  MirrorOfBinTree(pNode8);
  PrintBinTree(pNode8);

  printf("\n=====Test2: MirrorOfBinTreeItera=====\n");
  MirrorOfBinTreeItera(pNode8);
  PrintBinTree(pNode8);

  DestoryBinTree(pNode8);
}

// 测试二叉树：出叶子结点之外，左右的结点都有且只有一个右子结点
//            8
//             7
//              6
//               5
//                4
void Test3()
{
  printf("\n=====Test3 starts:=====\n");
  BinaryTreeNode* pNode8 = CreateBiTreeNode(8);
  BinaryTreeNode* pNode7 = CreateBiTreeNode(7);
  BinaryTreeNode* pNode6 = CreateBiTreeNode(6);
  BinaryTreeNode* pNode5 = CreateBiTreeNode(5);
  BinaryTreeNode* pNode4 = CreateBiTreeNode(4);

  ConnectBinTreeNodes(pNode8, NULL, pNode7);
  ConnectBinTreeNodes(pNode7, NULL, pNode6);
  ConnectBinTreeNodes(pNode6, NULL, pNode5);
  ConnectBinTreeNodes(pNode5, NULL, pNode4);

  PrintBinTree(pNode8);

  printf("\n=====Test3: MirrorOfBinTree=====\n");
  MirrorOfBinTree(pNode8);
  PrintBinTree(pNode8);

  printf("\n=====Test3: MirrorOfBinTreeItera=====\n");
  MirrorOfBinTreeItera(pNode8);
  PrintBinTree(pNode8);

  DestoryBinTree(pNode8);
}

// 测试空二叉树：根结点为空指针
void Test4()
{
  printf("\n=====Test4 starts:=====\n");
  BinaryTreeNode* pNode = NULL;

  PrintBinTree(pNode);

  printf("\n=====Test4: MirrorOfBinTree=====\n");
  MirrorOfBinTree(pNode);
  PrintBinTree(pNode);

  printf("\n=====Test4: MirrorOfBinTreeItera=====\n");
  MirrorOfBinTreeItera(pNode);
  PrintBinTree(pNode);
}

// 测试只有一个结点的二叉树
void Test5()
{
  printf("\n=====Test5 starts:=====\n");
  BinaryTreeNode* pNode8 = CreateBiTreeNode(8);

  PrintBinTree(pNode8);

  printf("\n=====Test4: MirrorOfBinTree=====\n");
  MirrorOfBinTree(pNode8);
  PrintBinTree(pNode8);

  printf("\n=====Test4: MirrorOfBinTreeItera=====\n");
  MirrorOfBinTreeItera(pNode8);
  PrintBinTree(pNode8);
}


int main(int argc, char const *argv[]) {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  return 0;
}
