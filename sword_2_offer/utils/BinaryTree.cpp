#include "BinaryTree.h"

BinaryTreeNode *CreateBiTreeNode(const int value)
{
  BinaryTreeNode *node = new BinaryTreeNode();
  node->value = value;
  node->left = nullptr;
  node->right = nullptr;
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
  }
}
