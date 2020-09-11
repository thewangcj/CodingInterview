// 题目：给定一棵二叉树和其中的一个结点，如何找出中序遍历顺序的下一个结点？
// 树中的结点除了有两个分别指向左右子结点的指针以外，还有一个指向父结点的指针。

#include <iostream>
struct BinaryTreeNode
{
  int value;
  BinaryTreeNode *left;
  BinaryTreeNode *right;
  BinaryTreeNode *parent;
};

BinaryTreeNode *CreateBiTreeNode(const int value)
{
  BinaryTreeNode *node = new BinaryTreeNode();
  node->value = value;
  node->left = nullptr;
  node->right = nullptr;
  node->parent = nullptr;
  return node;
}

void PrintBinTreeNode(const BinaryTreeNode *node)
{
  if (node != nullptr)
  {
    std::cout << node->value << ' ';
  }
  else
  {
    std::cout << " node is null ";
  }
}

void PrintBinTree(const BinaryTreeNode *tree)
{
  PrintBinTreeNode(tree);
  if (tree != nullptr)
  {
    if (tree->left != nullptr)
    {
      PrintBinTree(tree->left);
    }
    if (tree->right != nullptr)
    {
      PrintBinTree(tree->right);
    }
  }
}

void DestoryBinTree(BinaryTreeNode *tree)
{
  if (tree != nullptr)
  {
    BinaryTreeNode *left = tree->left;
    BinaryTreeNode *right = tree->right;
    delete tree;
    tree = nullptr;
    DestoryBinTree(left);
    DestoryBinTree(right);
  }
}

void ConnectBinTreeNodes(BinaryTreeNode *parent, BinaryTreeNode *left_child, BinaryTreeNode *right_child)
{
  if (parent != nullptr)
  {
    parent->left = left_child;
    parent->right = right_child;
    if (left_child != nullptr)
      left_child->parent = parent;
    if (right_child != nullptr)
      right_child->parent = parent;
  }
}

BinaryTreeNode *GetNext(BinaryTreeNode *node)
{
  if (node == nullptr)
    return nullptr;

  BinaryTreeNode *p_next = nullptr;

  if (node->right != nullptr)
  {
    BinaryTreeNode *p_right = node->right;
    while (p_right->left != nullptr)
    {
      p_right = p_right->left;
    }
    p_next = p_right;
  }
  else if (node->parent != nullptr)
  {
    BinaryTreeNode *p_current = node;
    BinaryTreeNode *p_parent = node->parent;
    while (p_parent != nullptr && p_current == p_parent->right)
    {
      p_current = p_parent;
      p_parent = p_parent->parent;
    }
    p_next = p_parent;
  }
  return p_next;
}

// ====================测试代码====================
void Test(const char *testName, BinaryTreeNode *pNode, BinaryTreeNode *expected)
{
  if (testName != nullptr)
    printf("%s begins: ", testName);

  BinaryTreeNode *pNext = GetNext(pNode);
  if (pNext == expected)
    printf("Passed.\n");
  else
    printf("FAILED.\n");
}

//            8
//        6      10
//       5 7    9  11
void Test1_7()
{
  BinaryTreeNode *pNode8 = CreateBiTreeNode(8);
  BinaryTreeNode *pNode6 = CreateBiTreeNode(6);
  BinaryTreeNode *pNode10 = CreateBiTreeNode(10);
  BinaryTreeNode *pNode5 = CreateBiTreeNode(5);
  BinaryTreeNode *pNode7 = CreateBiTreeNode(7);
  BinaryTreeNode *pNode9 = CreateBiTreeNode(9);
  BinaryTreeNode *pNode11 = CreateBiTreeNode(11);

  ConnectBinTreeNodes(pNode8, pNode6, pNode10);
  ConnectBinTreeNodes(pNode6, pNode5, pNode7);
  ConnectBinTreeNodes(pNode10, pNode9, pNode11);

  Test("Test1", pNode8, pNode9);
  Test("Test2", pNode6, pNode7);
  Test("Test3", pNode10, pNode11);
  Test("Test4", pNode5, pNode6);
  Test("Test5", pNode7, pNode8);
  Test("Test6", pNode9, pNode10);
  Test("Test7", pNode11, nullptr);

  DestoryBinTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test8_11()
{
  BinaryTreeNode *pNode5 = CreateBiTreeNode(5);
  BinaryTreeNode *pNode4 = CreateBiTreeNode(4);
  BinaryTreeNode *pNode3 = CreateBiTreeNode(3);
  BinaryTreeNode *pNode2 = CreateBiTreeNode(2);

  ConnectBinTreeNodes(pNode5, pNode4, nullptr);
  ConnectBinTreeNodes(pNode4, pNode3, nullptr);
  ConnectBinTreeNodes(pNode3, pNode2, nullptr);

  Test("Test8", pNode5, nullptr);
  Test("Test9", pNode4, pNode5);
  Test("Test10", pNode3, pNode4);
  Test("Test11", pNode2, pNode3);

  DestoryBinTree(pNode5);
}

//        2
//         3
//          4
//           5
void Test12_15()
{
  BinaryTreeNode *pNode2 = CreateBiTreeNode(2);
  BinaryTreeNode *pNode3 = CreateBiTreeNode(3);
  BinaryTreeNode *pNode4 = CreateBiTreeNode(4);
  BinaryTreeNode *pNode5 = CreateBiTreeNode(5);

  ConnectBinTreeNodes(pNode2, nullptr, pNode3);
  ConnectBinTreeNodes(pNode3, nullptr, pNode4);
  ConnectBinTreeNodes(pNode4, nullptr, pNode5);

  Test("Test12", pNode5, nullptr);
  Test("Test13", pNode4, pNode5);
  Test("Test14", pNode3, pNode4);
  Test("Test15", pNode2, pNode3);

  DestoryBinTree(pNode2);
}

void Test16()
{
  BinaryTreeNode *pNode5 = CreateBiTreeNode(5);

  Test("Test16", pNode5, nullptr);

  DestoryBinTree(pNode5);
}
int main(int argc, char const *argv[])
{
  Test1_7();
  Test8_11();
  Test12_15();
  return 0;
}
