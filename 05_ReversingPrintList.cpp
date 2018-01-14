#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include "./utils/List.h"
using namespace std;

void ReversingPrintListIteratively(ListNode * const list) {
  stack<ListNode*> nodes;
  ListNode* p = list;
  while (p != NULL) {
    nodes.push(p);
    p = p->next;
  }
  while (!nodes.empty()) {
    cout << nodes.top()->value << '\n';
    nodes.pop();
  }
}

void ReversingPrintListRecursively(ListNode * const list) {
  if(list != NULL){
    if(list->next != NULL){
      ReversingPrintListRecursively(list->next);
    }
    cout << list->value << '\n';
  }
}

int main(int argc, char const *argv[]) {
  ListNode* p1 = CreateListNode(1);
  ListNode* p2 = CreateListNode(2);
  ListNode* p3 = CreateListNode(3);
  ConnectListNodes(p1, p2);
  ConnectListNodes(p2, p3);
  PrintList(p1);
  ReversingPrintListIteratively(p1);
  return 0;
}
