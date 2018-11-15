/* Name: Luke Burford
* Date: 10/03/17
* Email: lburford@rams.colostate.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <Stem.h>
#include <lexo.h>
// wont need to include iostream later on!
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;
#include <string>
using std::string;
using namespace std;

//TODO NEED TO FIX SOMETHING, lexicographically and detriment are not stemming right! (could be somthing in lexo or StemExcep!)

/* ----STEP METHODS 1-8---- */
string Stem::Step1(string sIn) {
    // check to see if the string has an apostrophe
    if(sIn.front() == '\'') // the special case for step 1
        sIn = sIn.erase(0,1);
    if(Find(sIn,"\'s\'"))
        sIn = Replace(sIn,"",sIn.find("\'s\'"));
    //check to remove a suffix appostrophe
    else if(Find(sIn,"\'"))
        sIn.pop_back(); // remove the apostrophe
    // check to remove a 's suffix
    else if(Find(sIn, "\'s"))
        sIn = Replace(sIn, "", sIn.find("\'")); // remove everything after the apostrophe
//     cout << "Step1 when done: " << sIn << endl;
    if(sIn.size() <= 1)
        return sIn;
    else
     return Step2(sIn); // return the return of Step2
}

string Stem::Step2(string &sIn) {
    //check the first row 
    if(Find(sIn,"sses"))
        sIn = Replace(sIn, "ss", sIn.find("sses")); //replace
    // check the second row
    else if(Find(sIn,"ied") || Find(sIn,"ies")) {
        if(Preceder(sIn, "ied").length() > 1) // replacement conditions
            sIn = Replace(sIn, "i", (sIn.size())-lSuffix);
        else
            sIn = Replace(sIn, "ie", (sIn.size())-lSuffix);
    }
    // check the third and fourth row
    else if(sIn.back() == 's' && !(Find(sIn, "us") || Find(sIn, "ss"))) {
        if(isVowel(sIn.substr(0,sIn.length()-2))) // conditon for 4th row
            sIn = Replace(sIn,"",sIn.find_last_of("s"));
    }
//     cout <<"Step2 when done: " << sIn << endl;
    if(sIn.size() <= 1)
        return sIn;
    else
        return Step3(sIn); // return the return of Step3
}

string Stem::Step3(string &sIn) {
    if(Find(Region1(sIn),"eed") || Find(Region1(sIn),"eedly")) // row 1 including conditions
        sIn = Replace(sIn,"ee", sIn.find("eed"));
    else if((Find(sIn, "edly") && isVowel(Preceder(sIn,"edly"))) 
        || (Find(sIn, "ingly") && isVowel(Preceder(sIn,"ingly")))) { //row 2 "edly" and "ingly" 
        if((Find(sIn, "edly")))
           sIn = step3Replace(sIn, "edly"); //step 3 special Replace overide
        else
            sIn = step3Replace(sIn, "ingly");
    }
    else if((Find(sIn, "ed") && isVowel(Preceder(sIn,"ed")))
        || (Find(sIn, "ing") && isVowel(Preceder(sIn,"ing")))) { // row 2 "ing" and "ed"
        if((Find(sIn, "ed")))
           sIn = step3Replace(sIn, "ed");
        else
            sIn = step3Replace(sIn, "ing");
    }
//    cout <<"Step3 when done: " << sIn << endl;
    if(sIn.size() <= 1)
        return sIn;
    else
        return Step4(sIn);
}

string Stem::Step4(string &sIn) {
    if(sIn.back() == 'y') { // check to make sure the suffix (last char) is y
        string preceder = Preceder(sIn,"y");
        // Suffix follows a non-vowel that is not the first letter of the preceder.
        if(!isVowel(preceder, preceder.length()-1) && preceder.length() > 1) {
            lSuffix = 1; // set the suffix length to 1 since we dont call a Find method
            sIn = Replace(sIn, "i", sIn.length()-1); // replace 'y' with 'i'
        }
    }
    if(sIn.size() <= 1)
        return sIn;
    else
        return Step5(sIn);
}

// Comments in this block are messed up, sorry, just a long if else is all...
string Stem::Step5(string &sIn) {
    // 1st conditon
    if(Find(sIn, "ational"))
        sIn = Replace(sIn, "ate", (sIn.size())-lSuffix);
    else if(Find(sIn, "iveness"))
        sIn = Replace(sIn, "ive", (sIn.size())-lSuffix);
    else if(Find(sIn, "ization"))
        sIn = Replace(sIn, "ize", (sIn.size())-lSuffix);
    else if(Find(sIn, "ousness"))
        sIn = Replace(sIn, "ous", (sIn.size())-lSuffix);
    else if(Find(sIn, "biliti"))
        sIn = Replace(sIn, "ble", (sIn.size())-lSuffix);
    else if(Find(sIn, "fulness"))                                       
        sIn = Replace(sIn, "ful", (sIn.size())-lSuffix);
    else if(Find(sIn, "lessli"))
        sIn = Replace(sIn, "less", (sIn.size())-lSuffix);
    else if(Find(sIn, "tional"))
        sIn = Replace(sIn, "tion", sIn.find("tional"));
    else if(Find(sIn, "alism") || Find(sIn, "aliti"))
        sIn = Replace(sIn, "al", (sIn.size())-lSuffix);
    else if(Find(sIn, "ation"))
        sIn = Replace(sIn, "ate", (sIn.size())-lSuffix);
    // 3rd condition
    else if(Find(sIn, "entli"))
        sIn = Replace(sIn, "ent", (sIn.size())-lSuffix);
    else if (Find(sIn, "iviti"))                 
        sIn = Replace(sIn, "ive", (sIn.size())-lSuffix);
    else if(Find(sIn, "fulli"))
        sIn = Replace(sIn, "ful", (sIn.size())-lSuffix);
    else if(Find(sIn, "ousli"))
        sIn = Replace(sIn, "ous", (sIn.size())-lSuffix);
    else if(Find(sIn, "alli"))
        sIn = Replace(sIn, "al", (sIn.size())-lSuffix);
    // 1.5 conditon
    else if(Find(sIn, "enci") || Find(sIn, "anci"))
        sIn = Replace(sIn, "ance", (sIn.size())-lSuffix);
    else if(Find(sIn, "abli"))
        sIn = Replace(sIn, "able", (sIn.size())-lSuffix);
    else if(Find(sIn, "ator")) 
        sIn = Replace(sIn, "ate", (sIn.size())-lSuffix);
    else if(Find(sIn, "izer") || Find(sIn, "ization"))                  
        sIn = Replace(sIn, "ize", (sIn.size())-lSuffix);
    // 2nd conditon
    else if(Find(sIn, "bli"))                    
        sIn = Replace(sIn, "ble", (sIn.size())-lSuffix);
    // 12th condition (has special condition: Suffix preceded by l)
    else if(Find(sIn, "ogi") && Preceder(sIn,"ogi").back() == 'l')
        sIn = Replace(sIn, "og", (sIn.size())-lSuffix);
    // 13th & 14th condition
    // 16th condition (has special condition: Preceder ends in a valid li ending)
    else if(Find(sIn, "li") && isLiEnding(Preceder(sIn,"li")))
        sIn = Replace(sIn, "", (sIn.size())-lSuffix);
    if(sIn.size() <= 1)
        return sIn;
    else
        return Step6(sIn);
}

string Stem::Step6(string &sIn) {
    // 2nd condition
    if(step6SufIsReg1(sIn, "ational")) // step6 helper finds the suffix and makes sure that it is in region1
        sIn = Replace(sIn, "ate", sIn.size()-lSuffix);
    // 1st condition
    else if(step6SufIsReg1(sIn, "tional"))
        sIn = Replace(sIn, "tion", sIn.size()-lSuffix);
    // 3rd condition
    else if(step6SufIsReg1(sIn, "alize"))
        sIn = Replace(sIn, "al", sIn.size()-lSuffix);
    // 4th condition
    else if(step6SufIsReg1(sIn, "icate") || step6SufIsReg1(sIn, "iciti") || step6SufIsReg1(sIn, "ical"))
        sIn = Replace(sIn, "ic", sIn.size()-lSuffix);
    // 5th condition
    else if(step6SufIsReg1(sIn, "ful") || step6SufIsReg1(sIn, "ness")) {
        if(Find(sIn, "ful"))
            sIn = Replace(sIn, "", sIn.size()-lSuffix);
        else
            sIn = Replace(sIn, "", sIn.size()-lSuffix);
    }
    // 6th condition
    else if(step6SufIsReg2(sIn, "ative")) // step6 helper finds the suffix and makes sure that it is in region2
            sIn = Replace(sIn, "", sIn.size()-lSuffix);
    if(sIn.size() <= 1)
        return sIn;
    else
        return Step7(sIn);
}

string Stem::Step7(string &sIn) {
    if(Find(Region2(sIn), "ion")) {
        string preceder = Preceder(sIn, "ion");
        if(preceder.back() == 's' || preceder.back() == 't')
            sIn = preceder;
    }
    sIn = step7Region2(sIn); //else iff
    if(sIn.size() <= 1)
        return sIn;
    else
        return Step8(sIn);
}

string Stem::Step8(string &sIn) {
    // Suffix appears in Region2 OR suffix appears in Region1 and preceder does not end in a short syllable
    if(Find(Region2(sIn), "e") || (Find(Region1(sIn), "e") && !isShortSyllable(Preceder(sIn, "e"))))
        sIn = Replace(sIn, "", sIn.find_last_of("e"));
    // Suffix appears in Region2 and preceder ends in l (so word ends in ll)
    else if(Find(Region2(sIn), "l") && Preceder(sIn,"l").back() == 'l')
        sIn = Replace(sIn, "", sIn.find_last_of("l"));
    if(sIn.size() <= 1)
        return sIn;
    else
        return sIn;
}

/* ----STEP# HELPER METHODS---- */
const string Stem::step3Replace(string &sIn, const string &suffix) {
    string preceder = Preceder(sIn, suffix);
    sIn = Replace(sIn, "", sIn.find_last_of(suffix[0])); // replace the suffix with nothing
    if(preceder.size() < 2) {
        return sIn;
    }
    char back = preceder.at(preceder.length()-1); // get the last char of the preceder
    char back1 = preceder.at(preceder.length()-2); // ge the second to last char of the preceder
    if((back1 == 'a' && back == 't') || (back1 == 'b' && back == 'l') || (back1 == 'i' && back == 'z')) // if preceder ends in at, bl, or iz
        sIn.push_back('e'); // add an 'e' to back
    else if(isDouble(preceder, preceder.length()-2)) //  if preceder ends in a double
        sIn = Replace(sIn,"",sIn.length()-1); // remove only the last letter
    else if(isShort(preceder)) //  if the preceder is short
         sIn.push_back('e'); // add an 'e' to back
    return sIn;
}

const bool Stem::step6SufIsReg1(const string &sIn, const string &suffix) {
    const string reg1 = Region1(sIn); // get region1 of sIn
    if(Find(reg1, suffix))      // check if the suffix is in region1
        return true;
    else
        return false;
}

const bool Stem::step6SufIsReg2(const string &sIn, const string &suffix) {
    const string reg2 = Region2(sIn); // get region1 of sIn
    if(Find(reg2, suffix))      // check if the suffix is in region1
        return true;
    else
        return false;
}

string Stem::step7Region2(string &sIn) {
    string suffixes[] = {"ement","ance","able","ence","ible","ment",
        "ate","ant","ent","ism","iti","ive","ize","ous","al","er","ic"}; // all suffixes for step7 row1
    string suffixO = "";    // output suffix
    string reg2 = "";
    reg2 = Region2(sIn);  // region2 of the string
    for(unsigned int i=0; i<(sizeof(suffixes)/sizeof(*suffixes)); ++i) {
        suffixO = suffixes[i];
        if(Find(sIn, suffixO)) {
            if(Find(reg2,suffixO)) // check if the suffix is in region2
                return Replace(sIn, "", sIn.length()-suffixO.length()); // if so remove the suffix
            else
                return sIn; // if you found the correct (LONGEST) suffix but it does not exist in reg2 then just return
        }
    }

    return sIn; //iterate through the whole array, if find none then just return
}

/* ----GENERAL HELPER METHODS---- */
const bool Stem::isVowel(const string &sIn, int at) {
    char c = sIn.at(at);
    bool isLowercaseVowel, isUppercaseVowel, isYVowel;
    // evaluates to 1 (true) if c is a lowercase vowel
    isLowercaseVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    // evaluates to 1 (true) if c is an uppercase vowel
    isUppercaseVowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
    // evaluates to 1 (true) if c is y and if y is a vowel (y is a vowel unless it is the first char or immediatly follows a vowel).
    isYVowel = (at != 0 && (c == 'y' || c == 'Y'));
    if(isYVowel)    // checking if y follows a vowel (recursivly)
        isYVowel = !isVowel(sIn, at-1);
    // evaluates to 1 (true) if either isLowercaseVowel or isUppercaseVowel or isYVowel is true
    if (isLowercaseVowel || isUppercaseVowel || isYVowel)
        return true;
    else
        return false;
}

const bool Stem::isVowel(const string &sIn) {
    char c;
    bool isLowercaseVowel, isUppercaseVowel, isYVowel;
    for(unsigned int i = 0; i<sIn.length(); ++i) {
        c = sIn.at(i);
        // evaluates to 1 (true) if c is a lowercase vowel
        isLowercaseVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
        // evaluates to 1 (true) if c is an uppercase vowelsIn
        isUppercaseVowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
        // evaluates to 1 (true) if c is y and if y is a vowel (y is a vowel unless it is the first char or immediatly follows a vowel).
        isYVowel = (i != 0 && (c == 'y' || c == 'Y'));
        if(isYVowel)    // checking if y follows a vowel (recursivly)
            isYVowel = !isVowel(sIn, i-1);
        // evaluates to 1 (true) if either isLowercaseVowel or isUppercaseVowel or isYVowel is true
        if (isLowercaseVowel || isUppercaseVowel || isYVowel)
            return true;
    }
    return false; // if it gets all the way through the string then it does not have a vowel
}

const bool Stem::isDouble(const string &sIn, int at) {
    char c = toupper (sIn.at(at)); // char to compare that ignores case by just making everything upercase
    //check if the given char is at the end, if so then it has no double after it, thus false
    if((unsigned int) at+1 == sIn.length()) // need to cast at as an unsigned for comparing to length
        return false;
    //check if the char at the index is a valid pair letter, and is the same as the next char, if true then it is a double
    else if((c == 'B' || c == 'D' || c == 'F' || c == 'G' || c == 'M' || c == 'N' || c == 'P' || c == 'T' || c == 'R')
        && c == toupper (sIn.at(at+1)))
        return true;
    // if its not, then its not a double
    else
        return false;
}

const bool Stem::isLiEnding(const string &sIn) {
    char c = toupper (sIn.back());
    //check if the last char is a valid letter for li-ending, if so, is valid li-ending
    if(c == 'C' || c == 'D' || c == 'E' || c == 'G' ||
        c == 'H' || c == 'K' || c == 'M' || c == 'N' || c == 'R' || c == 'T')
        return true;
    //if not then not a li-ending
    else
        return false;
}

const string Stem::Region1(const string &sIn) {
    string sOut = ""; // region1 can be empty
    for(unsigned int i = 1; i <sIn.length(); ++i) {
        //if the current char is a consonant (not vowel) and the previous char is a vowel, then the rest is in region1
        if(!isVowel(sIn, i) && isVowel(sIn, i-1)) {
            sOut = sIn.substr(i+1, sIn.length()); // substring starting at i+1 and ending at the last char
            break;
        }
    }
    return sOut;   
}

const string Stem::Region2(const string &sIn) {
    string sOut = Region1(sIn); // get Region1 first since Region2 is the Region1 of Region1
    int inOffset = sIn.length() - sOut.length();
    for(unsigned int i = 1; i <sOut.length(); ++i) {
        //if the current char is a consonant (not vowel) and the previous char is a vowel, then the rest is in region2
        if((!isVowel(sOut, i) && isVowel(sOut, i-1))
            || (isVowel(sIn, (i-1)+inOffset))) {
            return sOut.substr(i+1, sOut.length()); // substring starting at i+1 and ending at the last char
            
        }
    }
    return "";
}

const string Stem::Preceder(const string &sIn, const string &suffix) {
    string sOut = "";
    // get the substring of the input of everything besides the suffix
    sOut = sIn.substr(0, sIn.length()-suffix.length());
//    cout << sOut << endl;
    return sOut;
}

const bool Stem::isShortSyllable(const string &sIn) {
    char last = toupper (sIn.back());    // last char to compare (ignoring case)
    // checks to see if the string is 2 chars or shorter and has a vowel followed by a non-vowel
    if(sIn.length() <= 2 
        && (isVowel(sIn,0) && !isVowel(sIn, 1)))
        return true;
    // check if the 3rd to last char is a consonant, the 2nd to last is a vowel, and the last is a consonant excluding "wxy"
    else if(!isVowel(sIn, sIn.length()-3) 
        && isVowel(sIn, sIn.length()-2) 
            && (!isVowel(sIn, sIn.length()-1) && last != 'W' && last != 'X' && last != 'Y')) {
        return true;
    }
    else
        return false;
}

const bool Stem::isShort(const string &sIn) {
    if(isShortSyllable(sIn) && Region1(sIn) == "")
        return true;
    else
        return false;
}

string Stem::Replace(string &sIn, const string &sNew, int start) {
    //if the suffix is the string in, then just return the replacement
    if(sIn.length() == lSuffix)
        return sNew;
    // remove the desired suffix starting at start
    sIn = sIn.erase(start, sIn.length()-1);
    // concat sNew to the end of sIn
    sIn += sNew;
    return sIn; // return the newly modified sIn
}

const bool Stem::Find(const string &sIn, const string &suffix) {
    if(sIn.find(suffix) == string::npos) // if suffix does not exist at all then dont bother checking if its at the end
        return false;
    int suLen = suffix.length();
    string temp = sIn.substr(sIn.length()-suLen, sIn.length());
//    cout << "temp string: " << temp << endl;
    // use the string find function, if it does not equal the npos(no pos) then it is in the string
    if(temp.find(suffix) == 0) {
        lSuffix = suLen;
        return true;
    }
    else
        return false;
}
