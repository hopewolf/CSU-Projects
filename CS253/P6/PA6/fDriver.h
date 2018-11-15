/* Name: Luke Burford
 * Date Created: 09/14/17
 * Updated to fDriver: 10/23/17
 * Email: lburford@rams.colostate.edu
 */

#ifndef FDRIVER_H_INCLUDE
#define FDRIVER_H_INCLUDE

#include <lexo.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h> 
using namespace std;

class fDriver {
public:
    // constructor for fDriver, takes the argc passed in by main and assigns it to N
    fDriver(int fCount) {
        N = fCount-2;
    };
    /* read will return -1 if error, 0 if success
     * creates StemException object
     * creates lexo objects for every file that is needed to read
     */
    int read(char* list[]);
    /* calculates the matrix to print using several methods:
     * calcSim, calcTFIDF, calcTF, calcIDF
     * pushes results to the results map
     */
    void calcMatrix();
    /* calculates the Sim score between two documents
     * takes the two lexo objects to compare each word repition between the two
     * TODO currently going to itererate through each string, maybe find a way to be more efficent
     */
    long double calcSim(lexo &A, lexo &B);
    /* calculates the TFIDF score for a word in a given file
     * takes a word string and a doc lexo object to find that word in it
     * calls calcTF & calcIDF to function
     * NOTE taking lexo in as a reference to save efficency 
     */
    double calcTFIDF(const string &sIn, lexo &doc);
    /* calculates TF portion of the TFIDF equation
     * takes a word string and a doc lexo object to find that word in it
     */
    double calcTF(const string &sIn, lexo &doc);
    /* calculates the IDF pertion of the IDF equation
     * takes a word string to check between N files and n occurencses of sIn in each file
     * NOTE taking lexo in as a reference to save efficency
     */
    double calcIDF(const string &sIn);
    // prints the calculated frequencies from the results map
    void printDocMatrix();
    /* helper method to calcMatrix
     * checks to see if an equation was already calculated between two files
     * if the string matches a string in the map, return false (dont recalculate)
     * if the string does not exist in the map, return true (needs a calculation)
     */
    bool checkResultsMap(string &name);
    
private:
    int N = 0; // total number of documents passed in TO COMPARE (not including exceptions)
    vector<lexo> docs; // vector that contains all of the lexo objects, 1 lexo object processes 1 file
    map<string,long double> results; // map that will contain the SIM calculation for a given set of docs
};

#endif //FDRIVER_H_INCLUDE
