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
#include <algorithm>
#include <string>
using namespace std;

void lexo::addVector(string &sIn) {
    // push_back puts the string in the back of the vector
    lVect.push_back(sIn);
}

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
    SoS = 0; //default SoS is 0, but if it contains and end of sentence char then it will be set back to 1
    //keep looking to find the length of the punctuation string
    for(unsigned int i=pos; i != sIn.length(); ++i) {
        //if the string contains a non punctuation then we found the full punc string
        if(!ispunct(sIn.at(i)) || sIn.at(i) == '\'')
            break;
        // check if the punc is an end of sentence char to set the startOfSentence bit
        if((sIn.at(i) == '.' || sIn.at(i) == '!' || sIn.at(i) == '?'))
            SoS = 1;
        if(sIn.at(i) == '.' && i+1 != sIn.length())
            if(isdigit(sIn.at(i+1))) {
                checkDig(sIn, pos);
                return;
            }
        pos++;
    }
    // send to subString to seperate and add to vector
    sIn = subString(sIn, pos);
}
void lexo::checkDig(string &sIn, int pos) {
    stemTest = false;
    SoS = 0; // digits count as a valid SoS char
    //keep looking to find the length of the digit string
    for(unsigned int i=pos; i != sIn.length(); ++i) {
        char nextCheck;
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
int addPlus = 0;
    // check if the startOfSentence bit is true
    if(SoS == 1 && isupper(sIn.front())) {
        // if the first letter is upper then we need to concat a '+' char in front of the string
        addPlus = 1;
        SoS = 0;
    }
    else
        SoS = 0; // if it is not valid addPlus then it is a valid letter for SoS thus SoS = 0
    //keep looking to find the length of the alpha string
    for(unsigned int i=pos; i != sIn.length(); ++i) {
        char nextCheck;
        char nextCheck2;
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
        // any capital char wont stem
        if(isupper(sIn.at(i)))
            stemTest = false;
        
        if(isdigit(sIn.at(i)) || (isupper(sIn.at(i)) && i != 0)) {
            stemTest = false;
            addPlus = 0;
        }
        //check for the super corner case of p.123, which needs to be broken up into 3 strings
        if(nextCheck == '.' && isdigit(nextCheck2))
            sIn.insert(i+2," ");
        //if the string contains a non alpha then we found the full alpha string
        if(ispunct(sIn.at(i)) && sIn.at(i) != '\'') // unless its an apostrophe
            break;
        //check to make sure that the word is not an acronym
        if(addPlus == 1 && (isdigit(sIn.at(i)) || isupper(sIn.at(i))) && i != 0) {
            stemTest = false;
            addPlus = 0;
        }
        pos++;
    }
    // if the addPlus bit is still true then concat a + char in front of the string, and incriment pos to accomidate
    if(addPlus == 1) {
        sIn = "+" + sIn;
        pos++;
    }
    // send to subString to seperate and add to vector
    sIn = subString(sIn, pos);
}
string lexo::subString(string &sIn, int size) {
    string out = ""; //string that we will send to addVector
    //substr takes a index and a length of string to substring
    out = sIn.substr(0,size); //substring the current part of the string that we want to add to the Vector
    if(out.at(0) != '+' && out.length() > 2 && stemTest) {
//         cout << "being passed into stem: " << out << endl;
        out = stem.Step1(out);
        stemTest = true;
    }
    stemTest = true;
    addVector(out); // call addVector
    //erase takes a index and a length of string to delete
    sIn = sIn.erase(0,size); // erase the sub-string that we added to the vector
    return sIn; // return the remaining string (could be empty) to continue to sort through
}
void lexo::lexSort() {
    // uses the algorithm sort function to sort lexographicaly
    sort(lVect.begin(), lVect.end());
}

void lexo::lexPrint() {
    //uses the vector iterator
    for (vector<string>::iterator it = lVect.begin() ; it != lVect.end(); ++it) {
        //count for the repeating strings
        int sCount = 1;
        //check to see if the string has any repeats after it, if not count is 1
        while((it != lVect.end()) && (*it == *(it+1))) {
            sCount++;
            it++;
        }
        cout << *it << " " << sCount << endl;
    }
}
