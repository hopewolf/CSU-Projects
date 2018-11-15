#include <iostream>
#include <string>
 
using namespace std;
 
long factorial(int n);
 
int main(int argc, char* argv[])
{
// Usage: factorial <input_num>
    if (argc != 2)
        return -1;
    int n = std::stoi(argv[1]); //converts string to int
    long val=factorial(n);
    cout << val << endl;
    return 0;
}
 
long factorial(int n)
{
    long result = 1;
    while(--n)
    {
        result*=n;
    }
    return result;
}
