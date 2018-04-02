#include <iostream>
#include <conio.h>
using namespace std;
//template <class T> void f(T &i) {cout << 1; }

//template <class Type = int> void f(const int &i) {cout << 2; }

class A {
public:
	int a;
	cout << "test" << COnflic << endl;
	class B{
	public:
		int c;
		void show()
			{
				cout << "test" << COnflic << endl;
			}
		class C{
		public:
			int d;
			cout << "test" << COnflic << endl;
		};
	};
	void A::B::show() {}
};

int main()
{

	return 0;
}
