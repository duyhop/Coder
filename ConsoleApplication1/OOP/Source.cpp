#include <iostream>
#include "CsubSingleton.h"
using namespace std;

class Animal
{
public:
	Animal():temp(10){
	};
	~Animal(){};
	void say_hello()
	{
		cout << "Animal Say hello" << endl;
	}
	void say_hello(int qa)
	{
		cout << "Animal Say hello" << endl;
	}
	void Step()
	{
		cout << "Animal Step" << endl;
	}
	friend void getTemp(Animal A);
	friend class X;

private:
	int temp;
	void test()
	{
		cout << "Test" << endl;
	}
};

void getTemp(Animal A)
{
	cout << "Gia tri temp = " << A.temp << endl;
}
class Cat: public Animal
{
public:
	Cat(){};
	~Cat(){};

	void Step()
	{
		cout << "Cat Step" << endl;
	}
};

class Dog: public Animal
{
public:
	Dog(){};
	~Dog(){};

	void say_hello()
	{
		cout << "Dog say hello" << endl;
	}

	void Step()
	{
		cout << "Dog Step" << endl;
	}
};
class X
{
public:
	int a;


	void show(Animal *A)
	{
		cout << "Temp: " <<  A->temp << endl;
		A->test();
	}
};
class Xx
{
public:
	int *p;
	Xx()
	{
		p = new int();
	}
	~Xx()
	{
		delete p;
	}
	virtual void show(){cout << "B" <<endl;};
	virtual void show1(){cout << "B1" <<endl;};
};
class Xy:public Xx
{
public:
	void show(){cout << "A" <<endl;};
	void show1(){cout << "A1" <<endl;};
};

int main()
{
	//CSingleton<CsubSingleton>::getInstance()->isKeyDown(10);
	int a = 10;
	int * b = new int;
	cout << "dia chi a: " << &a << endl;
	cout << "dia chi b: " << b << endl;
	cout << "dia chi &b: " << &b << endl;
	//Xx temp;
	//Xy temp1;
	//temp.show();
	//temp.show1();
	//temp1.show();
	//temp1.show1();
	//Xx *Base = &temp1;
	//Base->show();
	//Base->show1();
	//cout << Base->p << endl;
	//cout << temp1.p << endl;
	/*Cat C;
	Dog D;
	A.say_hello();
	A.Step();
	C.say_hello();
	C.Step();
	D.say_hello();
	D.Step();
	Animal *A1 = new Dog();
	A1->Step();
	delete A1;*/
	system("pause");
	return 0;
}