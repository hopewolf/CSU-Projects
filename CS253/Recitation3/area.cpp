#include<iostream>

using namespace std;

double area(int r)
{
	int i = 500;
	return 3.14159 * r * r;	
}

double square(int* x)
{
	x = 0;
	return x[0] * x[1];
}

void handle()
{
	int r;
	cout << "Please input the radius: ";
	cin >> r;
	for(int i = 0; i != 5; ++i)
		cout << "the area is: " << area(r + i) << endl;

	int* a = new int[2];
	cout << square(a) << endl;
}

int main(int argc, char* argv[])
{
	if(!(argc == 2))
		return -1;
	handle();
	return 0;
}

