#include <iostream>
#include <conio.h>
using namespace std;
//template <class T> void f(T &i) {cout << 1; }

//template <class Type = int> void f(const int &i) {cout << 2; }

class A {
public:
	int a;
	
	class B{
	public:
		int c;
		void show()
			{
				cout << "test" << endl;
			}
		class C{
		public:
			int d;
			
		};
	};
	void A::B::show() {}
};

int main()
{
	cout << " Tetst My Branch" << endl;
	return 0;
}