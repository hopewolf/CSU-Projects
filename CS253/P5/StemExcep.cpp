/* Name: Luke Burford
 * Date: 10/17/17
 * Email: lburford@rams.colostate.edu
 */

#include <StemExcep.h>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;
#include <fstream>
using std::ifstream;
using std::ws;
#include <sstream>
#include <vector>
using std::vector;
#include <string>
using namespace std;


bool StemExcep::initExcep(char* list) {
    ifstream fList(list);
    // check if the input stream has thrown any errors, if so, then throw an error
    if (fList.fail()){ 
        cerr << "Failed to open file" << endl;
        return true; // there WAS an error
    }
    // check to see if the start of the file is also the end of the file
    if((fList >> ws).peek() == EOF){
        cerr << "Empty file" << endl;
        return true;
    }

    // read the file until its at the end
    while (!((fList >> ws).peek() == EOF)){
        // strings to store the temp values in
        string line = "";
        string currEx = "";
        string currRe = "";
        getline(fList, line);
        stringstream str(line);
        str >> currEx; // get the lines exception
        str >> currRe; // get the lines correction
        if(fList.fail()){
            cerr << "Failed to input string" << endl;
            return true;
        }
        // check to make sure that exception file is in the format: "string_sring\n" ONLY
        if(str.fail()){
            cerr << "Exception file error" << endl;
            return true;
        }
        // add the strings to their appropriate vector for later reference
        eVect.push_back(currEx);
        rVect.push_back(currRe);
    }
    return false;   // there was NO error
}

string StemExcep::checkExcep(string &sIn) {
    bool Stem = true;
    unsigned int index = 0; // index that will match the exception vector to the replacement vector
    string currEx;
    // make a vector iterator to iterate through the exception vector
    for (vector<string>::iterator eIt = eVect.begin(); eIt != eVect.end(); ++eIt) {
        currEx = *eIt;
        // check the first char of the vector index and sIn (no need to iterate
        if(sIn.length() == currEx.length()) {
            if(sIn == currEx) {
                index = (unsigned int) (eIt - eVect.begin());
                sIn = rVect.at(index);
                Stem = false;
                break;
            }
        }
    }
    // if we could not find an exception then we stem
    if(Stem)
        sIn = stem.Step1(sIn);
    return sIn;
}
