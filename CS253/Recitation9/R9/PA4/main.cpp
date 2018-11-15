#include <iostream>
#include <string>
#include "stem.h"
using namespace std;


int main(int argc, char* argv[])
{
    Stem ss;
    cout << ss.step1("abc") << endl;
    cout << ss.step1("\'def") << endl;
    string t = "abcsses";
    ss.step2(t);
    cout << t << endl;
    t = "sses";
    ss.step2(t);
    cout << t << endl;
    t = "ses";
    ss.step2(t);
    cout << t << endl;
    cout << ss.isVowel('a')  << endl;
    cout << ss.isVowel('e')  << endl;
    cout << ss.isVowel('b')  << endl;
    cout << ss.isVowel('f')  << endl;
    t = "conditioning";
    ss.step3(t);
    cout << t << endl;
    return 0;
}

