/* Name: Luke Burford
 * Date Created: 09/14/17
 * Updated to fDriver: 10/23/17
 * Email: lburford@rams.colostate.edu
 */

#include <fDriver.h>
#include <lexo.h>
#include <StemExcep.h>
#include <string>
using std::to_string;
using namespace std;
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;
#include <fstream>
using std::ifstream;
using std::ws;
#include <vector>
using std::vector;
#include <map>
using std::map;
using std::pair;
#include <math.h>

int fDriver::read(char* list[]) {
    // stem exception to check stemming special cases
    StemExcep se = StemExcep();
    // creates the exception and replacement list (stem exception isnt used until lexo from here)
    if(se.initExcep(list[1]))
        return -1; // StemExcep returned an error while init the file and vectors
        
    // create N number of lexo objects for each file and add them to the lexo vector
    for(int i = 0; i < N; ++i) {
        // initiate a new file stream using the char pointer in
        ifstream fIn(list[i+2]);
        // lexographical sort class, takes a StemExcep object to keep the init list
        lexo lex = lexo(se);
        // check if the input stream has thrown any errors, if so, then throw an error
        if (fIn.fail()){ 
            cerr << "Failed to open file" << endl;
            return -1;
        }
        // check to see if the start of the file is also the end of the file
        if((fIn >> ws).peek() == EOF){
            cerr << "Empty file" << endl;
            return -1;
        }
        // read the file until its at the end
        while (!((fIn >> ws).peek() == EOF)){
            string current;
            fIn >> current;
            //pass current to lexo to check the grammer, and then add to the vector
            lex.checkEng(current);
        }
        // check and remove ambigouty, sort lexographicaly, and calculate the frequencies by adding to a map
        lex.lexCalcFreq();
        lex.printMap(); // NOTE THIS IS TO SHOW OBJECT MAP CONTENTS
        docs.push_back(lex);
    }
    return 0; //at the end if it was able to fully execute then return 0 (complete)
}

void fDriver::calcMatrix() {
    long double result = 0; // result local variable to be added to the results map
    // integers to serve as a "name" for a result calculation
    int currA, currB;
    currA = 1, currB = 1;
    string name = ""; // name for a result to be added to the results vector
    // 2 iterators for lexo object (document) vectors
    for(vector<lexo>::iterator itA = docs.begin(); itA < docs.end(); ++itA) {
        for(vector<lexo>::iterator itB = docs.begin(); itB < docs.end(); ++itB) {
            // get the name for this current calculation
            name = to_string(currA) + to_string(currB);
//             if(!checkResultsMap(name)) // check to make sure this calculation hasnt already been done
//                 break; // if it has then break (dont need to recalculate)
            // need to calculate:
            result = calcSim(*itA, *itB); // pass in the two objects to calcSim
            results.insert(pair<string,long double>(name,result));
            ++currB;
        }
        ++currA;
    }
}

long double fDriver::calcSim(lexo &A, lexo &B) {
    long double sum = 0;
    // current string while iterating through the maps
    string currA = "";
    string currB = "";
    // iterators for object A & B maps
    map<string,int>::iterator itA = A.freqMap.begin();
    map<string,int>::iterator itB = B.freqMap.begin();
    // iterate through doc A & B maps
    for(itA = A.freqMap.begin(); itA != A.freqMap.end(); ++itA) {
        string currA = itA->first; // get the string protion of the current map index
        for(itB = B.freqMap.begin(); itB != B.freqMap.end(); ++itB) {
            string currB = itB->first; // get the string protion of the current map index NOTE was itA???????
            if(currA.front() < currB.front())
                break; // check the first letter of both strings, both maps are sorted lexographicaly, if you have passed your current first char then its not going to be after that.
            if(currA == currB) {
                sum += calcTFIDF(currA, A) * calcTFIDF(currB, B); // get the TFIDF for both words in the docs
                break; // found the word, thus can search for the next one
            }
        }
    }
    return sum;
}

double fDriver::calcTFIDF(const string &sIn, lexo &doc) {
    return calcTF(sIn, doc) * calcIDF(sIn); // perform the TFIDF calculation by calling TF & IDF
}

double fDriver::calcTF(const string &sIn, lexo &doc) {
    return doc.getMapWordCount(sIn); // simply the amount of times a word accours in the given document
}

double fDriver::calcIDF(const string &sIn) {
    int n = 0; // number of documents that have occurences of sIn
    // Find n (number of occurences in all docs)
    // iterator for vector of lexo objects
    for(vector<lexo>::iterator itV = docs.begin(); itV < docs.end(); ++itV) {
        // using maps check fucntion, check if sIn occurs in the current index document
        if((*itV).freqMap.count(sIn) != 0)
            ++n;
    }
    // log base 10 of total files over number of files with at least one instance of sIn
    double temp = 0;
    temp = (double) N/n;
    return log10(temp);
}

//TODO Check what percision need to print at
void fDriver::printDocMatrix() {
    int newline = 0; // for keeping track of when to add a newline
    map<string,long double>::iterator it = results.begin(); // create the results iterator
    for(it = results.begin(); it != results.end(); ++it) { // print everything in the map
        cout << it->second << " "; // print format: "result " until results.end()
        newline++;
        if(newline == N) { // we print N number of files per line
            cout << endl;
            newline = 0;
        }
    }
}
//NOTE CURRENTLY COMMENTED OUT CAUSE IT ONLY PRINTS ONE LINE
//TODO Prints one line only due to it not copying already calculated values to the map again
bool fDriver::checkResultsMap(string &name) {
    string currName = ""; // current string "name" in the map
    // need to iterate through the results map
    map<string,long double>::iterator itR = results.begin();
    for(itR = results.begin(); itR != results.end(); ++itR) {
        currName = itR->first;
        // check to make sure your testing the same files (regardless of order)
        if((name.at(0) == currName.at(0) || name.at(0) == currName.at(1))
            &&(name.at(1) == currName.at(0) || name.at(1) == currName.at(1))) {
            results.insert(pair<string,long double>(name,itR->second));
            return false; // dont recalculate
        }
    }
    return true; // could not find a match, need to calculate
}
