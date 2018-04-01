#include <iostream>
using namespace std;
#include<stack>
// khoi tao cau truc

struct Node
{
	int data;
	struct Node *pNext;
};
typedef struct Node NODE;

struct Stack
{
	NODE *top;
};
typedef struct Stack STACK;

// init
void init_stack(STACK &stack)
{
	stack.top = NULL;
}

bool isEmpty(STACK stack)
{
	if(stack.top == NULL)
	{
		return true;
	}
	return false;
}
NODE * getItem(int data)
{
	NODE *p = new NODE;
	p->data = data;
	p->pNext = NULL;
	return p;
}
void push_Item(STACK &stack, NODE *node)
{
	bool bcheck = isEmpty(stack);
	if(bcheck == true)
	{
		stack.top = node;
	}
	else
	{
		node->pNext = stack.top;
		stack.top = node;
	}
	//delete p;
}
int pop_Item(STACK &stack)
{
	int result = 0;
	bool bcheck = isEmpty(stack);
	if(bcheck == true)
		return NULL;

	NODE *p = new NODE;
	
	p = stack.top;
	result = p->data;
	stack.top = stack.top->pNext;
	
	delete p;
	return result;
}

int main()
{
	STACK myStack;
	
	init_stack(myStack);
	
	bool bcheck = isEmpty(myStack);
	if(bcheck == true)
		cout << "Empty" << endl;
	else
		cout << "Not Empty" << endl;
	NODE *item1 = new NODE;
	NODE *item2 = new NODE;
	NODE *item3 = new NODE;
	item1 = getItem(10);
	item2 = getItem(11);
	item3 = getItem(12);

	push_Item(myStack, item1);
	push_Item(myStack, item2);
	push_Item(myStack, item3);
	bool check = false;

	int length= 0;
     NODE *node = myStack.top;
     while (node != NULL) {
         length = length + 1;
         node = node->pNext;
		 cout << pop_Item(myStack) << endl;
     }
     
	 cout << length << endl;
	system("pause");
	return 0;
}
