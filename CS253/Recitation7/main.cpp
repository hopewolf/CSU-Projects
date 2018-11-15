#include <vector>
#include <iostream>
#include <stdlib.h> 
using namespace std;

class Test {
public:
	static void testMethod(long l)
    {
        long xx;
        for(long i = 0; i != l; ++i)
        {
            xx = i;
        }
    }
};

void test1 (long l) {
    long xx;
    for(long i = 0; i != l; ++i)
    {
        xx = i;
    }
}

void test2 (long l)
{
    long xx;
    for(long i = 0; i != l; ++i)
    {
        xx = i;
    }
}

void test3 (long l)
{
    long xx;
    for(long i = 0; i != l; ++i)
    {
        xx = i;
    }
    test1(l);
}

void test4(long l)
{
	test1(l);
    test2(l);
}


int main (int argc, char* argv[]) 
{
    long l = atol(argv[1]);
    test1(l);
    test2(l);
    test3(l);
    test4(l);
	Test::testMethod(l);
    cout << "Finally Done!" << endl;

}
