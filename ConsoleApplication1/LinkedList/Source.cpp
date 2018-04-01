#include <iostream>
#include <vector>
// khoi tao cau truc NODE cac so nguyen
#define SWAP(a,b) {int temp; temp = a; a = b; b = temp;};
struct Node
{
	int data;
	struct Node *pNext;
};
typedef struct Node NODE;

struct List
{
	NODE *pHead;
	NODE *PTail;
};
typedef struct List LIST;

void Init(LIST &);
NODE * getNode(int);
void addHead(LIST &, NODE *);
void addTail(LIST &, NODE *);
void nhapDuLieu(LIST &);
void xuat(LIST);
int Max(LIST);
void sort(LIST&);
void Release(LIST &);
void Release1(LIST &);
void addNode(LIST &, NODE *, NODE *);
void xoadau(LIST &);
void xoacuoi(LIST &);
void xoabatky(LIST &, int);
void xoasauNODE(LIST &, NODE *);
void swap(int a , int b)
{
	int temp = a;
	a = b;
	b = temp;
}
int main()
{
	int iMax = 0;
	LIST l;
	// START - tao list bi loop && check xem no loop o dau
	nhapDuLieu(l);
	//xuat(l);
	std::vector<NODE*> V;
	for(NODE *p = l.pHead; p; p = p->pNext)
	{
		V.push_back(p);
		for(int i = 0; i < V.size() - 1; i++)
		{
			if( p == V[i])
			{
				std::cout << "Node thu: " << V.size() << "loop den Node thu: " << i << std::endl;
				goto EXIT;
			}
		}
	}
	// END - tao list bi loop && check xem no loop o dau
	//iMax = Max(l);
	//std::cout << "MAX: " << iMax << std::endl;
	//sort(l);
	//Release(l);
	//NODE *p = getNode(100);
	//NODE *q = getNode(1);
	//addNode(l, p, q);
	//xoadau(l);
	//xoacuoi(l);
	//NODE *P = getNode(1);
	//xoasauNODE(l, P);
	xoabatky(l, 1);
	EXIT:
	system("pause");
	return 0;
}
// init
void Init(LIST &l)
{
	l.pHead = l.PTail = NULL;
}

// tao NODE
NODE * getNode(int idata)
{
	// cap phat 1 NODE
	NODE *node = new NODE;
	if (node == NULL)
		return NULL;
	node->data = idata;
	node->pNext = NULL;// khoi tao moi lien ket
	return node;
}
// them dau
void addHead(LIST &l, NODE *node)
{
	if (l.pHead == NULL) // danh sach rong
	{
		l.pHead = l.PTail = node;
	}
	else
	{
		node->pNext = l.pHead; // node quang day de lien ket voi pHead
		l.pHead = node; // sau khi quang day roi thi node tro thanh pHead, nen cap nhat lai pHead
	}
}
// them cuoi
void addTail(LIST &l, NODE *node)
{
	if (l.pHead == NULL) // danh sach rong
	{
		l.pHead = l.PTail = node;
	}
	else
	{
		l.PTail->pNext = node;// ptail quang day lien ket voi node
		l.PTail = node;//sau khi quang day roi thi node tro thanh ptail, nen cap nhat lai ptail
	}
}
void nhapDuLieu(LIST &l)
{
	int n, x;
	Init(l);
	//std::cout << "Nhap so luong Node: ";
	//std::cin >> n;
	int a  = 10;
	int *ptr = &a;
	std::cout << "Size: " << sizeof(ptr) << std::endl;
	NODE *P;
	NODE *Q = getNode(6);
	for(int i = 1; i <= 5; i++)
	{
		//std::cout << "Nhap data cho NODE: ";
		//std::cin >> x;
		NODE *node = getNode(i);
		addTail(l, node);
		if(i==2) P = node;
	}
	l.PTail->pNext = Q;
	Q->pNext = P;
}

void xuat(LIST l)
{
	NODE *p = l.pHead;
	while(p!=NULL)
	{
		std::cout << p->data << " ";
		p = p->pNext;
	}
	std::cout << std::endl;
}

int Max(LIST l)
{
	int iMax = l.pHead->data;
	for(NODE *p = l.pHead->pNext; p; p = p->pNext)
	{
		if(iMax < p->data)
			iMax = p->data;
	}
	return iMax;
}
void sort(LIST &l)
{
	for (NODE *p = l.pHead; p!= l.PTail; p = p->pNext)
	{
		for (NODE *q = p->pNext; q; q = q->pNext)
		{
			if(p->data > q->data)
				SWAP(p->data, q->data);
		}
	}
	xuat(l);
}
void Release(LIST &l)
{
	NODE *p;
	while(l.pHead != NULL)
	{
		p = l.pHead;
		l.pHead = l.pHead->pNext;
		delete p;
	}
}
void addNode(LIST &l, NODE *nodeNew, NODE *nodeOld)
{
	for(NODE *p = l.pHead; p; p = p->pNext)
		if(p->data == nodeOld->data)
		{
			NODE *q = p->pNext;
			p->pNext = nodeNew;
			nodeNew->pNext = q;
			break;
		}
		xuat(l);
}
void xoadau(LIST &l)
{
	NODE *p = l.pHead;
	l.pHead = l.pHead->pNext;
	delete p;
	xuat(l);
}
void xoacuoi(LIST &l)
{
	NODE *x;
	for(NODE *p = l.pHead; p; p = p->pNext)
	{
		if(p == l.PTail)
		{
			l.PTail = x;
			l.PTail->pNext = NULL;
			delete p;
			break;
		}
		x = p;
	}
	xuat(l);
}
// xoa NODE dung sau NODE p
void xoasauNODE(LIST &l, NODE *p)
{
	NODE *q;
	for(NODE* k = l.pHead; k; k = k->pNext)
	{
		if(k->data == p->data)
		{
			q = k->pNext;
			k->pNext = q->pNext;
			delete q;
			break;
		}
	}
	xuat(l);
}

void xoabatky(LIST &l, int data)
{
	NODE *x;

	if(l.pHead->data == data)
	{
		xoadau(l);
		return;
	}
	
	if(l.PTail->data == data)
	{
		xoacuoi(l);
		return;
	}

	// neu data k fai dau, cuoi
	for(NODE *k = l.pHead; k; k = k->pNext)
	{
		if(k->data == data)
		{
			xoasauNODE(l, x);
			break;
		}
		x = k;
	}
}