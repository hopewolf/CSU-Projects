/* Name: Luke Burford
* Date: 09/14/17
* Email: lburford@rams.colostate.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <lexo.h>
#include <iostream>
#include <vector>
using std::vector;
#include <map>
using std::map;
using std::pair;
#include <algorithm>
#include <string>
using namespace std;

void lexo::checkEng(string &sIn) {
    while(!sIn.empty()) {
        if(isspace(sIn.front()))
            sIn.erase(0,1);
        // check to see if a char is punctuation, apostrophe does not count as punctuation
        if(ispunct(sIn.front()) && sIn.front() != '\'')
            checkPunct(sIn, 0);
        // check to see if a char is digit
        else if(isdigit(sIn.front()))
            checkDig(sIn, 0);
        // check to see if a char is alpha
        else
            checkAlpha(sIn, 0);
    }
}

void lexo::checkPunct(string &sIn, int pos) {
    stemTest = false;
    SoS = false; //default SoS is 0, but if it contains and end of sentence char then it will be set back to 1
    //keep looking to find the length of the punctuation string
    for(unsigned int i=pos; i != sIn.length(); ++i) {
        //if the string contains a non punctuation then we found the full punc string
        if(!ispunct(sIn.at(i)) || sIn.at(i) == '\'')
            break;
        // check if the punc is an end of sentence char to set the startOfSentence bit
        if((sIn.at(i) == '.' || sIn.at(i) == '!' || sIn.at(i) == '?'))
            SoS = true;
        if(sIn.at(i) == '.' && i+1 != sIn.length())
            if(isdigit(sIn.at(i+1))) {
                checkDig(sIn, pos);
                return;
            }
        pos++;
    }
    // send to subString to seperate and add to vector
    sIn = subString(sIn, pos); //TEMP TESTING
}

void lexo::checkDig(string &sIn, int pos) {
    stemTest = false;
    SoS = false; // digits count as a valid SoS char
    //keep looking to find the length of the digit string
    for(unsigned int i=pos; i != sIn.length(); ++i) {
        char nextCheck = 'a';
        //get the next char for checking periods and commas
        if(i+1 < sIn.size())
            nextCheck = sIn.at(i+1);
        //check the conditions of ".01" or "20,000"
        if((sIn.at(i) == '.' || sIn.at(i) == ',') && !isdigit(nextCheck))
            break;
        //if the string contains a non digit then we found the full digit string, excluding periods or commas
        if(ispunct(sIn.at(i)) && 
            !(sIn.at(i) == '.' || sIn.at(i) == ',')) {
            break;
        }
        pos++;
    }
    // send to subString to seperate and add to vector
    sIn = subString(sIn, pos);
}

void lexo::checkAlpha(string &sIn, int pos) {
bool addPlus = false; // track wether to add a plus to the start of the string or not
    // check if the startOfSentence bit is true
    if(SoS && isupper(sIn.front())) {
        // if the first letter is upper then we need to concat a '+' char in front of the string
        addPlus = true;
        SoS = false;
    }
    else
        SoS = false; // if it is not valid addPlus then it is a valid letter for SoS thus SoS = 0
    //keep looking to find the length of the alpha string
    for(unsigned int i=pos; i != sIn.length(); ++i) {
        char nextCheck = 'a';
        char nextCheck2 = 'a';
        //get the next char for checking periods
        if(i+1 < sIn.size())
            nextCheck = sIn.at(i+1);
        //get the next next char for checking digits
        if(i+2 < sIn.size())
            nextCheck2 = sIn.at(i+2);
        // check to make sure that is digit is called to not seperate . and ,
        if(isdigit(sIn.at(i)) && (nextCheck == '.' || nextCheck == ',')) {
            checkDig(sIn, i);
            return;
        }
        if(isdigit(sIn.at(i)) || (isupper(sIn.at(i)) && i != 0)) {
            stemTest = false;
            addPlus = false;
        }
        // any capital char wont stem
        if(isupper(sIn.at(i)))
            stemTest = false;
        //check for the super corner case of p.123, which needs to be broken up into 3 strings
        if(nextCheck == '.' && isdigit(nextCheck2))
            sIn.insert(i+2," ");
        //if the string contains a non alpha then we found the full alpha string
        if(ispunct(sIn.at(i)) && sIn.at(i) != '\'') // unless its an apostrophe
            break;
        //check to make sure that the word is not an acronym
        if(addPlus && (isdigit(sIn.at(i)) || isupper(sIn.at(i))) && i != 0) {
            stemTest = false;
            addPlus = false;
        }
        pos++;
    }
    // if the addPlus bit is still true then concat a + char in front of the string, and incriment pos to accomidate
    if(addPlus) {
        sIn = "+" + sIn;
        pos++;
    }
    // send to subString to seperate and add to vector
    sIn = subString(sIn, pos);
}

string lexo::checkWord(string &sIn) {
    // if the string has an ambigous capital
    if(sIn.at(0) == '+') {
        addambVector(sIn); // call addambVector
        return sIn;
    }
    // word contains a capital, then check ambigouty
    else if(!stemTest && sIn.at(0) != '+' && isalpha(sIn.front())) {
        addunambVector(sIn);
        return sIn;
    }

    // if it isnt a ambigous capital, longer than 2, and stemTest
    if(sIn.at(0) != '+' && sIn.length() > 2 && stemTest) {
        sIn = StemE.checkExcep(sIn);
        addlVector(sIn); //after stemming add to the vector
    }
    // doesn't stem, but still needs to be added to the vector
    else
        addlVector(sIn); // call addlVector
    return sIn; // return the remaining string (could be empty) to continue to sort through
}

string lexo::subString(string &sIn, int size) {
    string out = ""; //string that we will send to addlVector
    //substr takes a index and a length of string to substring
    out = sIn.substr(0,size); //substring the current part of the string that we want to add to the Vector
    out = checkWord(out);
    stemTest = true;
    //erase takes a index and a length of string to delete
    sIn = sIn.erase(0,size); // erase the sub-string that we added to the vector
    return sIn; // return the remaining string (could be empty) to continue to sort through
}
//TODO Change the vector to be completly and only a map
void lexo::addlVector(const string &sIn) {
    if(sIn == "") {
        cout << "right her pushing empty string!" <<endl;
        cout << "last thing pushed: " << lVect.back() << endl;
        cout << "before that: " << lVect[lVect.size()-2] << endl;
        
    }
    // push_back puts the string in the back of the list vector
    lVect.push_back(sIn);
}

void lexo::addambVector(const string &sIn) {
    // remove the plus before we push_back, we dont need it anymore
    // push_back puts the string in the back of the ambigous vector
    ambVect.push_back(sIn.substr(1, sIn.length()));
}

void lexo::addunambVector(const string &sIn) {
    // push_back puts the string in the back of the unambigous vector
    unambVect.push_back(sIn);
}

void lexo::lexSort() {
    // uses the algorithm sort function to sort lexographicaly
    sort(lVect.begin(), lVect.end());
}

void lexo::lexCalcFreq() {
    //before we can calc the frequncies we need to check ambigouty and sort it
    clearAmb(); // remove any remaining ambigous string and add them to the vector to be sorted
    lexSort();
    //uses the vector iterator
    for (vector<string>::iterator it = lVect.begin(); it != lVect.end(); ++it) {
        // calculate frequncies by converting the vector to a map that contains strings(the word) and ints (count for words)
        addFreqMap(*it);
    }
    //NOTE as of PA6 may want to deconstruct the StemException object before lexo object is copied to vector
}

void lexo::addFreqMap(const string &sIn) {
    //NOTE: for now our freq map will not include punc as of PA6, this may change later, if this changes, just remove the next 2 lines: TEMP COMMENT FOR TEST
//     if(ispunct(sIn.front()))
//         return;
    // if the map does not yet contain the string to be added
    if(freqMap.count(sIn) == 0)
        freqMap.insert(pair<string,int>(sIn,1)); // insert the string with its count as 0
    else
        freqMap.at(sIn) = freqMap.at(sIn)+1; // add 1 to the count NOTE: I think this is kind of a sketch way to do it
}

bool lexo::checkAmbigous(string sIn) {
    //NOTE just iterating through entire vector every check, not having to check it that often, thus not worried about it ATM
    string current = "";
    // iterate through the special vector
    for(vector<string>::iterator itU = unambVect.begin(); itU < unambVect.end(); ++itU) {
        current = *itU;
        if(sIn == current)
            return true;
        if(sIn.front() < current.front()) // unambVect is sorted lexo so you already passed any possible match
            return false;
    }
    return false; // if you iterate through the entire vector and didnt find it then return false
}

void lexo::clearAmb() {
    string current = "";
    sort(unambVect.begin(), unambVect.end()); // sort the unambigous vector for faster lookup
    // iterate through the special vector
    for(vector<string>::iterator itA = ambVect.begin(); itA < ambVect.end(); ++itA) {
        current = *itA; // copy the current index to local string
        if(checkAmbigous(current)) {
            addlVector(current); // word is no longer ambigous thus add to lVect
            ambVect.erase(itA);
            --itA;
            continue;
        }
        current.front() = tolower(current.front()); // set the first char to lower
        if(current.length() > 2)
            current = StemE.checkExcep(current); // find exception or stem
        addlVector(current); // add to the main lexo vector
    }
    // now add the items from unambVect to lVect
    for(vector<string>::iterator itU = unambVect.begin(); itU < unambVect.end(); ++itU) {
        addlVector(*itU);
    }
}

const void lexo::printMap() {
    map<string,int>::iterator it = freqMap.begin(); // create the freqMap iterator
    for (it = freqMap.begin(); it != freqMap.end(); ++it) { // print everything in the map
        cout << it->first << " " << it->second << endl; // print format: "word count\n" until freqMap.end()
    }
    cout << endl; // end of map, print 1 more endl
}

const int lexo::getMapWordCount(const string &sIn) {
    int count = 0; // if no match then the count will be 0
    if(freqMap.find(sIn) != freqMap.end()) { // if not found freqMap.find will equal freqMap.end
        count = freqMap.find(sIn)->second; // get the second element of the index in the map (int)
    }
    return count;
}


