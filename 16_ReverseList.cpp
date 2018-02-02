// 反转链表
// 题目：定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点。
#include <iostream>
#include "./utils/List.h"
using namespace std;

ListNode* ReverseList(ListNode* list) {
  ListNode* return_list = NULL;
  ListNode* p_node = list;
  ListNode* p_pre = NULL;
  ListNode* p_next = NULL;
  while(p_node != NULL) {
    p_next = p_node->next;
    if(p_next == NULL)
      return_list = p_node;
    p_node->next = p_pre;
    p_pre = p_node;
    p_node = p_next;
  }
  return return_list;
}

// ====================测试代码====================
ListNode* Test(ListNode* pHead)
{
  printf("The original list is: \n");
  PrintList(pHead);

  ListNode* pReversedHead = ReverseList(pHead);

  printf("The reversed list is: \n");
  PrintList(pReversedHead);

  return pReversedHead;
}

// 输入的链表有多个结点
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

  ListNode* pReversedHead = Test(pNode1);

  DestroyList(pReversedHead);
}

// 输入的链表只有一个结点
void Test2()
{
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pReversedHead = Test(pNode1);

  DestroyList(pReversedHead);
}

// 输入空链表
void Test3()
{
  Test(NULL);
}

int main(int argc, char const *argv[]) {
  Test1();
  Test2();
  Test3();
  return 0;
}
