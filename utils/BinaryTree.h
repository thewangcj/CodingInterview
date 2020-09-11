#ifndef __BINART__TREE__
#define __BINART__TREE__

#include <iostream>
using namespace std;

struct BinaryTreeNode
{
  int value;
  BinaryTreeNode *left;
  BinaryTreeNode *right;
};

BinaryTreeNode *CreateBiTreeNode(const int value);
void PrintBinTree(const BinaryTreeNode *tree);
void PrintBinTreeNode(const BinaryTreeNode *node);
void DestoryBinTree(BinaryTreeNode *tree);
void ConnectBinTreeNodes(BinaryTreeNode *parent, BinaryTreeNode *left_child, BinaryTreeNode *right_child);

#endif
