/* Name: Luke Burford
 * Date: 09/08/17
 * Email: lburford@rams.colostate.edu
 */

#ifndef LEXO_H_INCLUDE
#define LEXO_H_INCLUDE

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class lexo{
public:
    // takes string from fRead and prints them in lexographical order
    void addVector(string &sIn);
    // takes a string and checks it to make sure that its grammatically correct
    void checkEng(string &sIn);
    
    void checkPunct(string &sIn, int pos);
    
    void checkDig(string &sIn, int pos);
    
    void checkAlpha(string &sIn, int pos);
    // takes in a string, and a size to substring out the portion to push into
    string subString(string &sIn, int size);
    // use the sort algorithm: sort(vec.begin(), vec.end()); to sort lexographicaly 
    void lexSort();
    // prints the sorted vector and displays the count of each string as well
    void lexPrint();
private:
    vector<string> lVect;
    int SoS = 1; // value for tracking if at the start of sentence, 0 if false, 1 if true
};

#endif //LEXO_H_INCLUDE
