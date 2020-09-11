// 重建二叉树
// 题目：输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输
// 入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,
// 2, 4, 7, 3, 5, 6, 8}和中序遍历序列{4, 7, 2, 1, 5, 3, 8, 6}，则重建出
// 图2.6所示的二叉树并输出它的头结点。
#include "./utils/BinaryTree.h"
#include <iostream>
#include <exception>
#include <cstdlib>
using namespace std;

BinaryTreeNode *ConstructBinaryTree(int *start_pre, int *end_pre, int *start_in, int *end_in)
{
  int root_value = start_pre[0];
  BinaryTreeNode *root = CreateBiTreeNode(root_value);

  if (start_pre == end_pre)
  {
    if (start_in == end_in && *start_pre == *start_in)
    {
      return root;
    }
    else
    {
      std::cout << "Invalid input" << '\n';
      exit(0);
    }
  }

  int *root_in = start_in;
  while (root_in <= end_in && *root_in != root_value)
  {
    root_in++;
  }
  if (root_in == end_in && *root_in != root_value)
  {
    std::cout << "Invalid input" << '\n';
    exit(0);
  }

  int left_len = root_in - start_in;
  if (left_len > 0)
  {
    root->left = ConstructBinaryTree(start_pre + 1, start_pre + left_len, start_in, root_in - 1);
  }
  if (left_len < end_pre - start_pre)
  {
    root->right = ConstructBinaryTree(start_pre + left_len + 1, end_pre, root_in + 1, end_in);
  }
  return root;
}

BinaryTreeNode *Construct(int *pre_order, int *in_order, int length)
{
  if (pre_order == nullptr || in_order == nullptr || length < 0)
  {
    return nullptr;
  }
  return ConstructBinaryTree(pre_order, pre_order + length - 1, in_order, in_order + length - 1);
}

// ====================测试代码====================
void Test(const char *testName, int *preorder, int *inorder, int length)
{
  if (testName != nullptr)
    cout << testName << ": ";

  cout << "The preorder sequence is: ";
  for (int i = 0; i < length; ++i)
    cout << preorder[i] << ' ';
  cout << endl;

  cout << "The inorder sequence is: ";
  for (int i = 0; i < length; ++i)
    cout << inorder[i] << ' ';
  cout << endl;

  BinaryTreeNode *root = Construct(preorder, inorder, length);
  PrintBinTree(root);
  cout << endl;
  DestoryBinTree(root);
}

void Test1()
{
  const int length = 8;
  int preorder[length] = {1, 2, 4, 7, 3, 5, 6, 8};
  int inorder[length] = {4, 7, 2, 1, 5, 3, 8, 6};

  Test("Test1", preorder, inorder, length);
}

// 所有结点都没有右子结点
//            1
//           /
//          2
//         /
//        3
//       /
//      4
//     /
//    5
void Test2()
{
  const int length = 5;
  int preorder[length] = {1, 2, 3, 4, 5};
  int inorder[length] = {5, 4, 3, 2, 1};

  Test("Test2", preorder, inorder, length);
}

// 所有结点都没有左子结点
//            1
//             \
//              2
//               \
//                3
//                 \
//                  4
//                   \
//                    5
void Test3()
{
  const int length = 5;
  int preorder[length] = {1, 2, 3, 4, 5};
  int inorder[length] = {1, 2, 3, 4, 5};

  Test("Test3", preorder, inorder, length);
}

// 树中只有一个结点
void Test4()
{
  const int length = 1;
  int preorder[length] = {1};
  int inorder[length] = {1};

  Test("Test4", preorder, inorder, length);
}

// 完全二叉树
//              1
//           /     \
//          2       3
//         / \     / \
//        4   5   6   7
void Test5()
{
  const int length = 7;
  int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
  int inorder[length] = {4, 2, 5, 1, 6, 3, 7};

  Test("Test5", preorder, inorder, length);
}

// 输入空指针
void Test6()
{
  Test("Test6", nullptr, nullptr, 0);
}

// 输入的两个序列不匹配
void Test7()
{
  const int length = 7;
  int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
  int inorder[length] = {4, 2, 8, 1, 6, 3, 7};

  Test("Test7: for unmatched input", preorder, inorder, length);
}

int main(int argc, char const *argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();

  return 0;
}
