/* Name: Luke Burford
 * Date: 09/08/17
 * Email: lburford@rams.colostate.edu
 */

#include <lexo.h>
#include <iostream>
#include <vector>
using std::vector;
#include <algorithm>
#include <string>
using namespace std;

void lexo::addVector(string sIn) {
    // push_back puts the string in the back of the vector
    lVect.push_back(sIn);
}

void lexo::lexSort() {
    // uses the algorithm sort function to sort lexographicaly
    sort(lVect.begin(), lVect.end());
    // once sorted
    lexPrint();
}

void lexo::lexPrint() {
    //uses the vector iterator
  for (vector<string>::iterator it = lVect.begin() ; it != lVect.end(); ++it) {
    int sCount = 1;
    while((it != lVect.end()) && (*it == *(it+1))) {
        sCount++;
        it++;
    }
    cout << *it << " " << sCount << endl;
  }
}
