// 复杂链表的复制
// 题目：请实现函数ComplexListNode* Clone(ComplexListNode* pHead)，复
// 制一个复杂链表。在复杂链表中，每个结点除了有一个m_pNext指针指向下一个
// 结点外，还有一个m_pSibling 指向链表中的任意结点或者nullptr。
#include <iostream>

using namespace std;

struct ComplexListNode
{
	int m_value;
	ComplexListNode* m_next;
	ComplexListNode* m_sibling;
};

ComplexListNode* CreateNode(int value)
{
    ComplexListNode* pNode = new ComplexListNode();
    
    pNode->m_value = value;
    pNode->m_next = NULL;
    pNode->m_sibling = NULL;

    return pNode;
}

void BuildNodes(ComplexListNode* pNode, ComplexListNode* pNext, ComplexListNode* pSibling)
{
    if(pNode != NULL)
    {
        pNode->m_next = pNext;
        pNode->m_sibling = pSibling;
    }
}

void PrintList(ComplexListNode* pHead)
{
    ComplexListNode* pNode = pHead;
    while(pNode != NULL)
    {
        printf("The value of this node is: %d.\n", pNode->m_value);

        if(pNode->m_sibling != NULL)
            printf("The value of its sibling is: %d.\n", pNode->m_sibling->m_value);
        else
            printf("This node does not have a sibling.\n");

        printf("\n");

        pNode = pNode->m_next;
    }
}

void CloneNodes(ComplexListNode* list) {
	ComplexListNode* p = list;
	while(p != NULL) {
		ComplexListNode* cloned = new ComplexListNode();
		cloned->m_value = p->m_value;
		cloned->m_next = p->m_next;
		p->m_next = cloned;
		p = cloned->m_next;
	}
}

void ConnectSiblingsNodes(ComplexListNode* list) {
	ComplexListNode* p = list;
	while(p != NULL) {
		ComplexListNode* cloned = p->m_next;
		if(p->m_sibling != NULL) {
			cloned->m_sibling = p->m_sibling->m_next;
		}
		p = cloned->m_next;
	}
}

ComplexListNode* ReconnectNodes(ComplexListNode* list) {
	ComplexListNode* node = list;
	ComplexListNode* cloned_list = NULL;
	ComplexListNode* cloned = NULL;
	if(node != NULL) {
		cloned = cloned_list = node->m_next;
		node->m_next = cloned->m_next;
		node = node->m_next;
	}
	while(node != NULL) {
		cloned->m_next = node->m_next;
		cloned = cloned->m_next;
		node->m_next = cloned->m_next;
		node = node->m_next;
	}
	return cloned_list;
}

ComplexListNode* CopyComplexList(ComplexListNode* list) {
	CloneNodes(list);
	ConnectSiblingsNodes(list);
	return ReconnectNodes(list);
}

// ====================测试代码====================
void Test(const char* testName, ComplexListNode* pHead)
{
  if(testName != NULL)
  	printf("%s begins:\n", testName);

  printf("The original list is:\n");
  PrintList(pHead);

  ComplexListNode* pClonedHead = CopyComplexList(pHead);

  printf("The cloned list is:\n");
  PrintList(pClonedHead);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void Test1()
{
  ComplexListNode* pNode1 = CreateNode(1);
  ComplexListNode* pNode2 = CreateNode(2);
  ComplexListNode* pNode3 = CreateNode(3);
  ComplexListNode* pNode4 = CreateNode(4);
  ComplexListNode* pNode5 = CreateNode(5);

  BuildNodes(pNode1, pNode2, pNode3);
  BuildNodes(pNode2, pNode3, pNode5);
  BuildNodes(pNode3, pNode4, NULL);
  BuildNodes(pNode4, pNode5, pNode2);

  Test("Test1", pNode1);
}

// m_pSibling指向结点自身
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
void Test2()
{
  ComplexListNode* pNode1 = CreateNode(1);
  ComplexListNode* pNode2 = CreateNode(2);
  ComplexListNode* pNode3 = CreateNode(3);
  ComplexListNode* pNode4 = CreateNode(4);
  ComplexListNode* pNode5 = CreateNode(5);

  BuildNodes(pNode1, pNode2, NULL);
  BuildNodes(pNode2, pNode3, pNode5);
  BuildNodes(pNode3, pNode4, pNode3);
  BuildNodes(pNode4, pNode5, pNode2);

  Test("Test2", pNode1);	
}

// m_pSibling形成环
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
void Test3()
{
  ComplexListNode* pNode1 = CreateNode(1);
  ComplexListNode* pNode2 = CreateNode(2);
  ComplexListNode* pNode3 = CreateNode(3);
  ComplexListNode* pNode4 = CreateNode(4);
  ComplexListNode* pNode5 = CreateNode(5);

  BuildNodes(pNode1, pNode2, NULL);
  BuildNodes(pNode2, pNode3, pNode4);
  BuildNodes(pNode3, pNode4, NULL);
  BuildNodes(pNode4, pNode5, pNode2);

  Test("Test3", pNode1);
}

// 只有一个结点
void Test4()
{
  ComplexListNode* pNode1 = CreateNode(1);
  BuildNodes(pNode1, NULL, pNode1);

  Test("Test4", pNode1);
}

// 鲁棒性测试
void Test5()
{
  Test("Test5", NULL);
}

int main(int argc, char* argv[])
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();

  return 0;
}
