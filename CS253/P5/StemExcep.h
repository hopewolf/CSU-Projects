/* Name: Luke Burford
 * Date: 10/17/17
 * Email: lburford@rams.colostate.edu
 */

#ifndef STEMEXCEP_H_INCLUDE
#define STEMEXCEP_H_INCLUDE

#include <Stem.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class StemExcep {
public:
    /* initalizes the exceptions file to iterate to check for exceptions before stemming
     * adds all strings to the 2 vectors: eVect & rVect
     * takes in a char pointer (to the start of a file)
     * returns true if it encountered an error, false if it went smoothly
     */
    bool initExcep(char* list);
    /* with the input string check to see if it exsists in the exception vector
     * if so, modify it with its appropriate replacement from the replacement vector
     * if not just return the original string
     */
    string checkExcep(string &sIn);
    
private:
    vector<string> eVect; // vector to store all of the possible exceptions
    vector<string> rVect; // vector to store all of the replacements to the exceptions
    Stem stem = Stem();
};

#endif //FREAD_H_INCLUDE
