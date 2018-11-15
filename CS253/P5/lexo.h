/* Name: Luke Burford
 * Date: 09/08/17
 * Email: lburford@rams.colostate.edu
 */

#ifndef LEXO_H_INCLUDE
#define LEXO_H_INCLUDE

#include <iostream>
#include <StemExcep.h>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class lexo{
public:
    // constructor for lexo, takes the current object of StemExcep to keep the needed exception vectors
    lexo(StemExcep se) {StemE = se;};
    // takes a string and checks it to make sure that its grammatically correct
    void checkEng(string &sIn);
    
    void checkPunct(string &sIn, int pos);
    
    void checkDig(string &sIn, int pos);
    
    void checkAlpha(string &sIn, int pos);
    // check words to later be sent to subString, calls StemExcep and Stem
    string checkWord(string &sIn);
    // takes in a string, and a size to substring out the portion to push into
    string subString(string &sIn, int size);
    // adds given string to the special vector
    void addsVector(string &sIn);
    // adds given string to the list vector
    void addlVector(string &sIn);
    // use the sort algorithm: sort(vec.begin(), vec.end()); to sort lexographicaly 
    void lexSort();
    // prints the sorted vector and displays the count of each string as well
    void lexPrint();
    // check through the special vect to remove ambigous words
    void checkAmbigous(string sIn);
    // removes everything out of the special vector, lowecases, and stems all of them before pushing to lVect
    void clearAmb();
private:
    StemExcep StemE = StemExcep();
    vector<string> lVect;
    vector<string> sVect; // special vector for taking ambigous capitalized strings
    bool SoS = true; // value for tracking if at the start of sentence, 0 if false, 1 if true
    bool stemTest = true;
};

#endif //LEXO_H_INCLUDE
