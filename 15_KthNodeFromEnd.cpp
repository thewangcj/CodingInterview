#include <iostream>
#include "./utils/List.h"
using namespace std;

ListNode* FindKthToTail(ListNode* list, unsigned int k) {
  if(list == NULL || k == 0)
    return NULL;

  ListNode* p_first = list;
  ListNode* p_second = list;
  for(size_t i = 0; i < k-1; i++) {
    if(p_first->next != NULL) {
      p_first = p_first->next;
    } else {
      return NULL;
    }
  }

  while(p_first->next !=NULL) {
    p_first = p_first->next;
    p_second = p_second->next;
  }
  return p_second;
}
// ====================测试代码====================
// 测试要找的结点在链表中间
void Test1()
{
  cout<< "=====Test1 starts:=====" << endl;
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  cout<< "expected result: 4." << endl;
  ListNode* pNode = FindKthToTail(pNode1, 2);
  PrintListNode(pNode);

  DestroyList(pNode1);
}

// 测试要找的结点是链表的尾结点
void Test2()
{
  cout<< "=====Test2 starts:=====" << endl;
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  cout<< "expected result: 5." << endl;
  ListNode* pNode = FindKthToTail(pNode1, 1);
  PrintListNode(pNode);

  DestroyList(pNode1);
}

// 测试要找的结点是链表的头结点
void Test3()
{
  cout<< "=====Test3 starts:=====" << endl;
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  cout<< "expected result: 1" << endl;
  ListNode* pNode = FindKthToTail(pNode1, 5);
  PrintListNode(pNode);

  DestroyList(pNode1);
}

// 测试空链表
void Test4()
{
  cout<< "=====Test4 starts:=====" << endl;
  cout<< "expected result: nullptr." << endl;
  ListNode* pNode = FindKthToTail(nullptr, 100);
  PrintListNode(pNode);
}

// 测试输入的第二个参数大于链表的结点总数
void Test5()
{
  cout<< "=====Test5 starts:=====" << endl;
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  cout<< "expected result: nullptr." << endl;
  ListNode* pNode = FindKthToTail(pNode1, 6);
  PrintListNode(pNode);

  DestroyList(pNode1);
}

// 测试输入的第二个参数为0
void Test6()
{
  cout<< "=====Test6 starts:=====" << endl;
  ListNode* pNode1 = CreateListNode(1);
  ListNode* pNode2 = CreateListNode(2);
  ListNode* pNode3 = CreateListNode(3);
  ListNode* pNode4 = CreateListNode(4);
  ListNode* pNode5 = CreateListNode(5);

  ConnectListNodes(pNode1, pNode2);
  ConnectListNodes(pNode2, pNode3);
  ConnectListNodes(pNode3, pNode4);
  ConnectListNodes(pNode4, pNode5);

  cout<< "expected result: nullptr." << endl;
  ListNode* pNode = FindKthToTail(pNode1, 0);
  PrintListNode(pNode);

  DestroyList(pNode1);
}

int main(int argc, char const *argv[]) {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  return 0;
}
