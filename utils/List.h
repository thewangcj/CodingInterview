#ifndef __LIST_H__
#define  __LIST_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

struct ListNode{
  int value;
  ListNode * next;
};

ListNode* CreateListNode(int value);
void ConnectListNodes (ListNode* p_current, ListNode* p_next);
void PrintList(ListNode* const list);
void DestroyList(ListNode* list);
void PrintListNode(ListNode* list_node);

#endif
