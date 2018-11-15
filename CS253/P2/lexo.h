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
    void addVector(string sIn);
    // use the sort algorithm: sort(vec.begin(), vec.end()); to sort lexographicaly 
    void lexSort();
    // prints the sorted vector and displays the count of each string as well
    void lexPrint();
private:
    vector<string> lVect;
};

#endif //LEXO_H_INCLUDE
