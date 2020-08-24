// 从尾到头打印链表
// 题目：输入一个链表的头结点，从尾到头反过来打印出每个结点的值。
#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include "./utils/List.h"
using namespace std;

void ReversingPrintListIteratively(ListNode *const list)
{
  // 这里应该存 ListNode *，假如 ListNode 里的 value 是个很大的量，存指针可以减少内存占用
  stack<ListNode *> nodes;
  ListNode *p = list;
  while (p != NULL)
  {
    nodes.push(p);
    p = p->next;
  }
  while (!nodes.empty())
  {
    cout << nodes.top()->value << '\n';
    nodes.pop();
  }
}

void ReversingPrintListRecursively(ListNode *const list)
{
  if (list != NULL)
  {
    if (list->next != NULL)
    {
      ReversingPrintListRecursively(list->next);
    }
    cout << list->value << '\n';
  }
}

int main(int argc, char const *argv[])
{
  ListNode *p1 = CreateListNode(1);
  ListNode *p2 = CreateListNode(2);
  ListNode *p3 = CreateListNode(3);
  ConnectListNodes(p1, p2);
  ConnectListNodes(p2, p3);
  PrintList(p1);
  ReversingPrintListIteratively(p1);

  ListNode *p4 = CreateListNode(1);
  ReversingPrintListIteratively(p4);

  ReversingPrintListIteratively(nullptr);
  return 0;
}
