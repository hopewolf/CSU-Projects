#include <vector>
#include <iostream>
using namespace std;

class Test {
public:
	Test (int x) {p = new int(x);}
	/*other option for fixing test4:
    Test (const Test& t) {p = new int(t.getValue());}
	*/
	~Test() {
		delete p;
	}
	int getValue () const {return *p;}
	int *p;
};

void test1 () {
	int *val = new int[1];
	val[0] = 1;
    delete[] val; // to fix the leak delete the int array
}

char test2 () // fix by returning by value so it does not fall out of scope
{
	char c = 'a';
	return c;
}

void test3 ()
{
	char *char_array = new char[3];
	char_array[0] = 'a';
	char_array[1] = 'b';
	char_array[2] = 'c';
	delete[] char_array;
}

void test4(Test &t)
{
	cout << "test5: " << t.getValue() << endl;
}

int main (int argc, char* argv[]) 
{
	int i = 0;
	cout << "i in main: " << i << endl;

	test1();
	
	char c = test2();
	c = 'd';

	test3();

	Test x(5);
	test4(x);
}
