/* Name: Luke Burford
 * Date: 09/14/17
 * Email: lburford@rams.colostate.edu
 */

#include <fRead.h>
#include <Stem.h>
#include <string>
using namespace std;
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;
#include <fstream>
using std::ifstream;
using std::ws;

int main(int argc, char* argv[]) {
    /* TEMP TESTING STEM FUNCTIONS ONLY */
/*     Stem s = Stem();
    string s1 = "sudedly"*/;
//     string s2 = "definition";
//     string s3 = "abcdeG";
//     string s4 = "ff";
//     string s5 = "tricked";
//     string s6 = "bed";
//     string s7 = "browthreezus";
//     string empty = "";
//     string suffix = "ed";
//    cout << s.isVowel(s1, 5) << endl;
//    cout << s.isDouble(s4, 0) << endl;
//    cout << s.isLiEnding(s3) << endl;
//    cout << "region1: " << s.Region1(s2) << endl;
//    cout << "region2: " << s.Region2(s2) << endl;
//    cout << s.Preceder(s5, suffix) << endl;
//    cout << s.isShortSyllable(s6) << endl;
//    cout << s.isShort(s6) << endl;
//     cout << "Final out: " << s.Step1(s7) << endl;
//     cout << "Find method: " << s.Find(s1, "ed") << endl;;
//     return 0;
     
/* BELLOW IS THE REAL MAIN, EVERYTHING ABOVE IS FOR TEMP TESTING ONLY!!! */    

    if(argc != 2) {
        cerr << "Missing file as argument" << endl;
        return -1;
    }
    fRead fr = fRead();
    return fr.fRead::read(argv[1]);
 }
