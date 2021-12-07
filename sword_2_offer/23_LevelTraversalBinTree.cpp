// 不分行从上往下打印二叉树
// 题目：从上往下打印出二叉树的每个结点，同一层的结点按照从左到右的顺序打印。
#include "./utils/BinaryTree.h"
#include <iostream>
#include <deque>

void LevelTraversalBInTree(BinaryTreeNode* tree) {
	if(!tree)
		return;
	deque<BinaryTreeNode*> bin_tree_deque;
	bin_tree_deque.push_back(tree);
	while(bin_tree_deque.size()) {
		BinaryTreeNode* p = bin_tree_deque.front();
		bin_tree_deque.pop_front();
		cout<<p->value<<' ';
		if(p->left)
			bin_tree_deque.push_back(p->left);
		if(p->right)
			bin_tree_deque.push_back(p->right);
	}
}

// ====================测试代码====================
void Test(const char* testName, BinaryTreeNode* pRoot)
{
  if(testName != NULL)
      printf("%s begins: \n", testName);

  PrintBinTree(pRoot);

  printf("The nodes from top to bottom, from left to right are: \n");
  LevelTraversalBInTree(pRoot);

  printf("\n\n");
}

//            10
//         /      \
//        6        14
//       /\        /\
//      4  8     12  16
void Test1()
{
  BinaryTreeNode* pNode10 = CreateBiTreeNode(10);
  BinaryTreeNode* pNode6 = CreateBiTreeNode(6);
  BinaryTreeNode* pNode14 = CreateBiTreeNode(14);
  BinaryTreeNode* pNode4 = CreateBiTreeNode(4);
  BinaryTreeNode* pNode8 = CreateBiTreeNode(8);
  BinaryTreeNode* pNode12 = CreateBiTreeNode(12);
  BinaryTreeNode* pNode16 = CreateBiTreeNode(16);

  ConnectBinTreeNodes(pNode10, pNode6, pNode14);
  ConnectBinTreeNodes(pNode6, pNode4, pNode8);
  ConnectBinTreeNodes(pNode14, pNode12, pNode16);

  Test("Test1", pNode10);

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
void Test2()
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

  Test("Test2", pNode5);

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
void Test3()
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

  Test("Test3", pNode1);

  DestoryBinTree(pNode1);
}

// 树中只有1个结点
void Test4()
{
  BinaryTreeNode* pNode1 = CreateBiTreeNode(1);
  Test("Test4", pNode1);

  DestoryBinTree(pNode1);
}

// 树中没有结点
void Test5()
{
  Test("Test5", NULL);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

 	return 0;	
}