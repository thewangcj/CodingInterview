#include "BinaryTree.h"

BinaryTreeNode* CreateBiTreeNode(const int value) {
  BinaryTreeNode* node = new BinaryTreeNode();
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void PrintBinTreeNode(const BinaryTreeNode* node) {
  if (node != NULL) {
    std::cout << node->value << ' ';
  } else {
    std::cout << " node is null ";
  }
}

void PrintBinTree(const BinaryTreeNode* tree) {
  PrintBinTreeNode(tree);
  if(tree != NULL){
    if(tree->left != NULL){
      PrintBinTree(tree->left);
    }
    if(tree->right != NULL){
      PrintBinTree(tree->right);
    }
  }
}

void DestoryBinTree(BinaryTreeNode* tree) {
  if(tree != NULL){
    BinaryTreeNode* left = tree->left;
    BinaryTreeNode* right = tree->right;
    delete tree;
    tree = NULL;
    DestoryBinTree(left);
    DestoryBinTree(right);
  }
}

void ConnectBinTreeNodes(BinaryTreeNode* parent, BinaryTreeNode* left_child, BinaryTreeNode* right_child){
  if( parent != NULL){
    parent->left = left_child;
    parent->right = right_child;
  }
}
