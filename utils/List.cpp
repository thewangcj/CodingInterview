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
