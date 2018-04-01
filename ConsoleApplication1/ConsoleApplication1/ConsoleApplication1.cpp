// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "PS.h"
int deqi(int n);
int dequy_duoi(int, int);
int dequy_tuyen_tinh(int n);
void arrange();
void arrange1();
void arrange2();
void InsertionSort();
void xuat_matrix_n(int a[10][10], int row, int col);
void nhan_matrix1(int a[10][10], int b[10][10], int row_a, int col, int col_b)
{

	int c[10][10];
	int temp = 0;
	for(int i = 0; i < row_a*col_b; i++)
	{
		for(int j = 0; j < col; j++)
		{
			temp += a[i/col_b][j] * b[j][i%col_b];
		}
		c[i/col_b][i%col_b] = temp; 
		temp = 0;
	}

	xuat_matrix_n(c, row_a, col_b);
}
void xuat_matrix_n(int a[10][10], int row, int col)
{

	for(int i = 0; i < row*col; i ++)
	{
		cout << a[i/col][i % col] << " ";
		if((i+1)%col == 0) cout << endl;
	}
}

void nhap_matrix_n(int a[10][10], int row, int col)
{

	for(int i = 0; i < row*col; i ++)
	{
		cout << "Nhap a[" << (i/col) << "][" << (i%col) << "]";
		cin >> a[i/col][i%col];
	}
}
class A
{
public:
	A(){};
	~A(){};
	void Show(int a){};
	void Show1(int a) {};
};
class B:public A
{
public:
	B(){};
	~B(){};
	void Show()
	{
		cout << "con";
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	arrange();
	////PS axx;
	//PS ax (1,1), b;
	//int x  = 10;
	//ax.a = &x;
	//b = ax;
	//cout << b;
	//*b.a = 11;
	//cout << ax;
	//cout << b;
	//int a = deqi(3);
	//cout << a << endl;
	//int result1, result;
	//result = dequy_duoi(3, result1=1);
	//cout << result;
	//result = dequy_tuyen_tinh(3);
	//cout << result;
	//InsertionSort();
	int a[10][10];
	int b[10][10];
	int row_a, col_a, row_b, col_b;
	do
	{
		cout << "please input row_a: ";
		cin >> row_a;
	}
	while(row_a < 2);

	do
	{
		cout << "please input col_a: ";
		cin >> col_a;
	}
	while(col_a < 2);

	do
	{
		cout << "please input row_b: ";
		cin >> row_b;
	}
	while(row_b < 2 || row_b!= col_a);

	do
	{
		cout << "please input col_b: ";
		cin >> col_b;
	}
	while(col_b < 2);

	nhap_matrix_n(a, row_a, col_a);
	xuat_matrix_n(a, row_a, col_a);

	nhap_matrix_n(b, row_b, col_b);
	xuat_matrix_n(b, row_b, col_b);

	nhan_matrix1(a, b, row_a, col_a, col_b);
	return 0;
}
int deqi(int n)
{
	int result  =  (n>1) ? n*n+deqi(n-1): 1;
	return result;
}
int dequy_duoi(int n, int result=1)
{
	if(n == 1) return result;
	return dequy_duoi(n-1, result + n);
}

int dequy_tuyen_tinh(int n)
{
	int result = 1;
	if(n == 1) return 1;
	else
		for(int i = 2; i <= n; i++)
		{
			result *= i;
		}
	return dequy_duoi(n-1) + result;
}
#define SWAP(a,b) {int temp; temp = a; a = b; b = temp;}
//bubble sort
void arrange()
{
	int a[10] = {1, 4, 6, 2, 5, 3, 9, 8, 7, 0};
	for(int i = 0; i < 10; i ++)
		for(int j = 9; j > i; j --)
		{
			if(a[j-1] > a[j])
				SWAP(a[j-1], a[j]);
		}
	for(int i = 0; i < 10; i ++)
	{
		cout << a[i] << endl;
	}
}
//insert sort
void arrange1()
{
	int num;
	int a[10] = {1, 4, 6, 2, 5, 3, 9, 8, 7, 0};
	for(int i = 1; i < 10; i ++)
	{
		num = 0;
		for(int j = i; j >= 0; j --)
		{
			if(a[i] < a[j])
				num = j;
		}
		if (num > 0)
			SWAP(a[i], a[num]);
	}
	for(int i = 0; i < 10; i ++)
	{
		cout << a[i] << endl;
	}
}
//Selection sort
void arrange2()
{
	int num, min,imin;
	int a[10] = {1, 4, 6, 2, 5, 3, 9, 8, 7, 0};
	for(int i = 0; i < 10; i ++)
	{
		min = i;
		imin = a[i];
		for(int j = i+1; j < 10; j ++)
		{
			if(imin > a[j])
			{
				imin = a[j];
				min = j;
			}
		}
		if(min != i)
		{
			//SWAP(a[i], a[min]);
			a[min] = a[min]^ a[i];
            a[i] = a[i]^a[min];
            a[min] = a[min]^a[i];
		}
	}
	for(int i = 0; i < 10; i ++)
	{
		cout << a[i] << endl;
	}
}

void InsertionSort()
{
	int a[10] = {1, 4, 6, 2, 5, 3, 9, 8, 7, 0};
	for (int i = 1; i < 10; i++)
	{
		int x = a[i];
		int j = i;
		while (j > 0 && a[j - 1] > x)
		{
			a[j] = a[j - 1];
			j--;
		}
		a[j] = x;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << endl;
	}
}