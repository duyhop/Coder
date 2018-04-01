#include "stdafx.h"
#include "PS.h"


PS::PS(int a, int b)
{
	Tu = a;
	Mau = b;
}
PS::PS(void):Tu(1), Mau(1), a(new int)
{
}

PS::~PS(void)
{
}
//PS PS::operator+(PS arg)
//{
//	PS tong;
//	tong.Tu = Tu*arg.Tu + Mau *arg.Mau; 
//	tong.Mau = Tu*arg.Tu + Mau *arg.Mau;
//	return tong;
//}
void PS::show()
{
	std::cout << Tu << Mau;
}
PS operator + (PS a, PS b)
{
	PS tong;
	tong.Tu = a.Tu * b.Mau + a.Mau *b.Mau; 
	tong.Mau =a.Tu * b.Mau + a.Mau *b.Mau; 
	return tong;
}
ostream& operator << (ostream &os, PS a)
{
	os << a.Tu << "/" << a.Mau << *a.a << endl;
	return os;
}
PS& PS::operator =(const PS &ps)
{
	this->Tu = ps.Tu;
	this->Mau = ps.Mau;
	*this->a = *ps.a;
	return *this;
}