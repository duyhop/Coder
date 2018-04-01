// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
struct Node{
	int data;
	struct Node *pNext;
};

struct ListNode
{
	Node *pHead;
	Node *pTail;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Node *node1, *node2, *node3, *node4;
	node1 = new Node;
	node2 = new Node;
	node3 = new Node;
	node4 = new Node;
	node1->data = 10;
	node2->data = 11;
	node3->data = 12;
	node4->data = 13;

	node1->pNext = node2;
	node2->pNext = NULL;
	ListNode List;
	List.pHead = List.pTail = NULL;
	//List.pHead->pNext = node1;
	List.pHead = node1;
	node1->pNext = node2;
	node2->pNext = node3;
	node3->pNext = node4;
	List.pTail = node4;
	List.pTail->pNext = NULL;

	Node* p;
 
	p = List.pHead;
	while (p != NULL)
	{
		// Process Node
		std::cout << p->data << std::endl;
		p = p->pNext;
	}
	return 0;
}

