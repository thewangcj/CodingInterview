// 二叉搜索树与双向链表
// 题目：输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求
// 不能创建任何新的结点，只能调整树中结点指针的指向。

#include <iostream>
#include "./utils/BinaryTree.h"
using namespace std;

void ConvertNode(BinaryTreeNode* node, BinaryTreeNode** last) {
	if(node == NULL)
		return;

	BinaryTreeNode* current = node;
	if(current->left != NULL)
		ConvertNode(current->left, last);

	current->left = *last;

	if(*last != NULL)
		(*last)->right = current;

	*last = current;

	if(current->right != NULL)
		ConvertNode(current->right, last);
}

BinaryTreeNode* Convert(BinaryTreeNode* Tree) {
	BinaryTreeNode* last = NULL;
	ConvertNode(Tree, &last);
	BinaryTreeNode* list = last;
	while(list != NULL && list->left != NULL) {
		list = list->left;
	}
	return list;
}

// ====================测试代码====================
void PrintDoubleLinkedList(BinaryTreeNode* pHeadOfList)
{
  BinaryTreeNode* pNode = pHeadOfList;

  printf("The nodes from left to right are:\n");
  while(pNode != NULL)
  {
    printf("%d\t", pNode->value);

    if(pNode->right == NULL)
      break;
    pNode = pNode->right;
  }

  printf("\nThe nodes from right to left are:\n");
  while(pNode != NULL)
  {
    printf("%d\t", pNode->value);

    if(pNode->left == NULL)
      break;
    pNode = pNode->left;
  }

  printf("\n");
}

void DestroyList(BinaryTreeNode* pHeadOfList)
{
  BinaryTreeNode* pNode = pHeadOfList;
  while(pNode != NULL)
  {
    BinaryTreeNode* pNext = pNode->right;

    delete pNode;
    pNode = pNext;
  }
}

void Test(const char* testName, BinaryTreeNode* pRootOfTree)
{
  if(testName != NULL)
    printf("%s begins:\n", testName);

  PrintBinTree(pRootOfTree);

  BinaryTreeNode* pHeadOfList = Convert(pRootOfTree);

  PrintDoubleLinkedList(pHeadOfList);
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

  DestroyList(pNode4);
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

  DestroyList(pNode1);
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

  DestroyList(pNode1);
}

// 树中只有1个结点
void Test4()
{
  BinaryTreeNode* pNode1 = CreateBiTreeNode(1);
  Test("Test4", pNode1);

  DestroyList(pNode1);
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