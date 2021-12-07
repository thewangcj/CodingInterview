// 二叉树中和为某一值的路径
// 题目：输入一棵二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所
// 有路径。从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
#include <iostream>
#include "./utils/BinaryTree.h"
#include <vector>
#include <iterator>
using namespace std;

void FindPath(BinaryTreeNode* tree, int expected_sum, vector<int>& path, int current_cum) {
  current_cum += tree->value;
  path.push_back(tree->value);

  bool is_leaf = (tree->left == NULL) && (tree->right == NULL);
  if(current_cum == expected_sum && is_leaf) {
    vector<int>::iterator iter = path.begin();
    for(; iter != path.end(); ++iter) {
      cout<< *iter << " ";
    }
    cout<<endl;
  }

  if(tree->left)
    FindPath(tree->left, expected_sum, path, current_cum);
  if(tree->right)
    FindPath(tree->right, expected_sum, path, current_cum);

  path.pop_back();
}

void FindPathInTree(BinaryTreeNode* tree, int expected_sum) {
  if(tree == NULL)
    return;
  vector<int> path;
  int current_cum = 0;
  FindPath(tree, expected_sum, path, current_cum);
}

// ====================测试代码====================
void Test(const char* testName, BinaryTreeNode* pRoot, int expectedSum)
{
  if(testName != NULL)
    printf("%s begins:\n", testName);

  FindPathInTree(pRoot, expectedSum);

  printf("\n");
}

//            10
//         /      \
//        5        12
//       /\        
//      4  7     
// 有两条路径上的结点和为22
void Test1()
{
  BinaryTreeNode* pNode10 = CreateBiTreeNode(10);
  BinaryTreeNode* pNode5 = CreateBiTreeNode(5);
  BinaryTreeNode* pNode12 = CreateBiTreeNode(12);
  BinaryTreeNode* pNode4 = CreateBiTreeNode(4);
  BinaryTreeNode* pNode7 = CreateBiTreeNode(7);

  ConnectBinTreeNodes(pNode10, pNode5, pNode12);
  ConnectBinTreeNodes(pNode5, pNode4, pNode7);

  printf("Two paths should be found in Test1.\n");
  Test("Test1", pNode10, 22);

  DestoryBinTree(pNode10);
}

//            10
//         /      \
//        5        12
//       /\        
//      4  7     
// 没有路径上的结点和为15
void Test2()
{
  BinaryTreeNode* pNode10 = CreateBiTreeNode(10);
  BinaryTreeNode* pNode5 = CreateBiTreeNode(5);
  BinaryTreeNode* pNode12 = CreateBiTreeNode(12);
  BinaryTreeNode* pNode4 = CreateBiTreeNode(4);
  BinaryTreeNode* pNode7 = CreateBiTreeNode(7);

  ConnectBinTreeNodes(pNode10, pNode5, pNode12);
  ConnectBinTreeNodes(pNode5, pNode4, pNode7);

  printf("No paths should be found in Test2.\n");
  Test("Test2", pNode10, 15);

  DestoryBinTree(pNode10);
}

//               5
//              /
//             4
//            /
//           3
//          /
//         2
//        /
//       1
// 有一条路径上面的结点和为15
void Test3()
{
  BinaryTreeNode* pNode5 = CreateBiTreeNode(5);
  BinaryTreeNode* pNode4 = CreateBiTreeNode(4);
  BinaryTreeNode* pNode3 = CreateBiTreeNode(3);
  BinaryTreeNode* pNode2 = CreateBiTreeNode(2);
  BinaryTreeNode* pNode1 = CreateBiTreeNode(1);

  ConnectBinTreeNodes(pNode5, pNode4, NULL);
  ConnectBinTreeNodes(pNode4, pNode3, NULL);
  ConnectBinTreeNodes(pNode3, pNode2, NULL);
  ConnectBinTreeNodes(pNode2, pNode1, NULL);

  printf("One path should be found in Test3.\n");
  Test("Test3", pNode5, 15);

  DestoryBinTree(pNode5);
}

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
// 没有路径上面的结点和为16
void Test4()
{
  BinaryTreeNode* pNode1 = CreateBiTreeNode(1);
  BinaryTreeNode* pNode2 = CreateBiTreeNode(2);
  BinaryTreeNode* pNode3 = CreateBiTreeNode(3);
  BinaryTreeNode* pNode4 = CreateBiTreeNode(4);
  BinaryTreeNode* pNode5 = CreateBiTreeNode(5);

  ConnectBinTreeNodes(pNode1, NULL, pNode2);
  ConnectBinTreeNodes(pNode2, NULL, pNode3);
  ConnectBinTreeNodes(pNode3, NULL, pNode4);
  ConnectBinTreeNodes(pNode4, NULL, pNode5);

  printf("No paths should be found in Test4.\n");
  Test("Test4", pNode1, 16);

  DestoryBinTree(pNode1);
}

// 树中只有1个结点
void Test5()
{
  BinaryTreeNode* pNode1 = CreateBiTreeNode(1);

  printf("One path should be found in Test5.\n");
  Test("Test5", pNode1, 1);

  DestoryBinTree(pNode1);
}

// 树中没有结点
void Test6()
{
  printf("No paths should be found in Test6.\n");
  Test("Test6", NULL, 0);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();

  return 0;
}