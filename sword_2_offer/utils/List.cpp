#include "List.h"
using namespace std;

ListNode *CreateListNode(int value)
{
  ListNode *p = new ListNode();
  p->value = value;
  p->next = 0;
  return p;
}

void ConnectListNodes(ListNode *p_current, ListNode *p_next)
{
  if (p_current == NULL)
  {
    cout << "list is null" << endl;
    exit(1);
  }
  p_current->next = p_next;
}

void PrintList(ListNode *const list)
{
  ListNode *p = list;
  while (p != NULL)
  {
    cout << p->value << ',';
    p = p->next;
  }
  cout << endl;
}

void DestroyList(ListNode *list)
{
  ListNode *p = list;
  while (p != NULL)
  {
    list = list->next;
    delete p;
    p = list;
  }
}

void PrintListNode(ListNode *list_node)
{
  if (list_node == NULL)
  {
    cout << "The node is null" << endl;
  }
  else
  {
    cout << "The key in node is " << list_node->value << endl;
  }
}
void AddToTail(ListNode **list, int value)
{
  ListNode *pNew = new ListNode();
  pNew->value = value;
  pNew->next = nullptr;
  if (*list == nullptr)
  {
    *list = pNew;
  }
  else
  {
    ListNode *node = *list;
    while (node->next != nullptr)
    {
      node = node->next;
    }
    node->next = pNew;
  }
}
void RemoveNode(ListNode **list, int value)
{
  if (list == nullptr || *list == nullptr)
    return;

  ListNode *pToBeDelete = nullptr;

  if ((*list)->value = value)
  {
    pToBeDelete = *list;
    *list = (*list)->next;
  }
  else
  {
    ListNode *node = *list;
    while (node->next != nullptr && node->next->value != value)
    {
      node = node->next;
    }
    if (node->next != nullptr && node->next->value == value)
    {
      pToBeDelete = node->next;
      node->next = node->next->next;
    }
  }

  if (pToBeDelete != nullptr)
  {
    delete pToBeDelete;
    pToBeDelete = nullptr;
  }
}