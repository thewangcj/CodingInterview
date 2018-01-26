#include "List.h"
using namespace std;

ListNode* CreateListNode(int value) {
  ListNode* p = new ListNode();
  p->value = value;
  p->next = 0;
  return p;
}

void ConnectListNodes (ListNode* p_current, ListNode* p_next) {
  if(p_current == NULL) {
    cout<< "list is null" <<endl;
    exit(1);
  }
  p_current->next = p_next;
}

void PrintList(ListNode* const list) {
  ListNode* p = list;
  while(p != NULL) {
    cout<< p->value << ',';
    p = p->next;
  }
  cout<<endl;
}

void DestroyList(ListNode* list) {
  ListNode* p = list;
  while (p != NULL) {
    list = list->next;
    delete p;
    p = list;
  }
}

void PrintListNode(ListNode* list_node) {
  if(list_node == NULL) {
    cout<< "The node is null" << endl;
  } else {
    cout<< "The key in node is " << list_node->value << endl;
  }
}
