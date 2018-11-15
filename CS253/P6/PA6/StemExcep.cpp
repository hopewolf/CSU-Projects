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
#include <unordered_map>
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
    // strings to store the temp values in
    string line = "";
    string currEx = "";
    string currRe = "";
    // read the file until its at the end
    while (!((fList >> ws).peek() == EOF)){
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
        eMap.insert(pair<string,string>(currEx,currRe)); // insert the exception and then its replacement
    }
    return false;   // there was NO error
}

string StemExcep::checkExcep(string &sIn) {
    if(eMap.count(sIn) == 1) // if not found eMap.find will equal eMap.end
        sIn = eMap.at(sIn); // get the second element of the index in the map (string)
    else    // not found, thus stem as usual
        sIn = stem.Step1(sIn);
    return sIn;
}
