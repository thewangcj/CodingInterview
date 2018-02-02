// 在O(1)时间删除链表结点
// 题目：给定单向链表的头指针和一个结点指针，定义一个函数在O(1)时间删除该结点。
#include <iostream>
#include "./utils/List.h"
using namespace std;

void DeleteNodeInList(ListNode** list_head, ListNode* to_be_delete) {
  if( ! list_head || !to_be_delete ) {
    return;
  }

  if( to_be_delete->next != NULL) {
    ListNode* p_next = to_be_delete->next;
    to_be_delete->value = p_next->value;
    to_be_delete->next = p_next->next;
    delete p_next;
    p_next = NULL;
  } else if( *list_head == to_be_delete ) {
    delete to_be_delete;
    to_be_delete = NULL;
    *list_head = NULL;
  } else {
    ListNode* p_node = *list_head;
    while ( p_node->next != to_be_delete) {
      p_node = p_node->next;
    }
    p_node->next = NULL;
    delete to_be_delete;
    to_be_delete = NULL;
  }
}

// ====================测试代码====================
void Test(ListNode* pListHead, ListNode* pNode)
{
  printf("The original list is: ");
  PrintList(pListHead);

  printf("The node to be deleted is: ");
  PrintListNode(pNode);

  DeleteNodeInList(&pListHead, pNode);

  printf("The result list is: ");
  PrintList(pListHead);
}

// 链表中有多个结点，删除中间的结点
void Test1()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  Test(pNode1, pNode3);

  DestroyList(pNode1);
}

// 链表中有多个结点，删除尾结点
void Test2()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  Test(pNode1, pNode5);

  DestroyList(pNode1);
}

// 链表中有多个结点，删除头结点
void Test3()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  Test(pNode1, pNode1);

  DestroyList(pNode1);
}

// 链表中只有一个结点，删除头结点
void Test4()
{
  ListNode* pNode1 = CreateListNode(1);

  Test(pNode1, pNode1);
}

// 链表为空
void Test5()
{
  Test(NULL, NULL);
}

int main(int argc, char const *argv[]) {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  return 0;
}
