#pragma once
#include <iostream>
#include <istream>
using namespace std;
class PS
{
public:
	int *a;
	PS();
	PS(int a, int b);
	~PS(void);
	//PS operator + (PS);
	void show();
	friend PS operator + (PS, PS);
	friend ostream& operator << (ostream &, PS);
	PS& operator =(const PS &);
private:
	int Tu;
	int Mau;

};


