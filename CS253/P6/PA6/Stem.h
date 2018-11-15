/**
 * @file Stem.h
 * @author Luke Burford
 * @date 10/03/17
 * @brief Header file for the stem class which stems string that is passed into it
 * @see lburford@rams.colostate.edu
*/

#ifndef STEM_H_INCLUDE
#define STEM_H_INCLUDE

#include <iostream>
#include <string>
using std::string;
using namespace std;

/**
 * @brief My Stemmer class
 * 
 * Stem will take in strings and using a algorithim return a very specific change to that
 * string depending on the algorithim.
 * @note stem uses the default constructor
 */

class Stem {
public:    
    /**
     * Step #1 starts with a special case: if the word (i.e. string) begins with an apostrophe, remove the
     * apostrophe. Then apply the longest of the following substitutions that apply
     * (see assignment sheet for break down)
     */
    string Step1(string sIn);
    /**
     * Step #2 is as follows (remember, use only the longest that applies)
     * (see assignment sheet for break down)
     */
    string Step2(string &sIn);
    /**
     * Step #3 
     * (see assignment sheet for break down)
     */
    string Step3(string &sIn);
    /**
     * Step #4
     * (see assignment sheet for break down)
     */
    string Step4(string &sIn);
    /**
     * Step #5
     * (see assignment sheet for break down)
     */
    string Step5(string &sIn);
    /**
     * Step #6
     * rules all require that the prefix be in Region1 
     * (one of the rules has a stronger condition, and requires the prefix to be in Region2)
     * (see assignment sheet for break down)
     */
    string Step6(string &sIn);
    /**
     * Step #7
     *  (see assignment sheet for break down)
     */
    string Step7(string &sIn);
    /**
     * Step #8
     *  (see assignment sheet for break down)
     */
    string Step8(string &sIn);
    /**
     * driver for step3, checks conditions for the 2nd row replace
     * (see assignment sheet for break down)
     */
    const string step3Replace(string &sIn, const string &suffix);
    /**
     * driver for step6, checks to see if the suffix is inside of region1
     * if suffix is in region1 return true
     * else return false
     */
    const bool step6SufIsReg1(const string &sIn, const string &suffix);
    /**
     * driver for step6, checks to see if the suffix is inside of region2 (which is in region1)
     * if suffix is in region1 return true
     * else return false
     */
    const bool step6SufIsReg2(const string &sIn, const string &suffix);
    /**
     * driver for step7, checks the row1 suffixs to be in region2
     * 
     */
    string step7Region2(string &sIn);
    /**
     * Checks to see if a certain char in the string is a vowel
     * A vowel is any of {‘a’, ‘e’, ‘i’, ‘o’, ‘u’} or the letter ‘y’ UNLESS the ‘y’ is the first letter
     * in a word or immediately follows a vowel. (Note that this is a recursive definition.)
     * Therefor the letter ‘y’ is considered a vowel in the word try but a consonant (non-vowel)
     * in the words yellow and today.
     */
    const bool isVowel(const string &sIn, int at);
    /**
     * Overide of isVowel, where it checks if in any part of a string there is a vowel
     */
    const bool isVowel(const string &sIn);
    /**
     * Checks to see if a string contains a double, takes a int, will check that char(at index) and the char after for pair
     * A double is any of the following letter pairs: 
     * {‘bb’, ‘dd’, ‘ff’, ‘gg’, ‘mm’, ‘nn’, ‘pp’, ‘rr’, ‘tt’}.
     */
    const bool isDouble(const string &sIn, int at);
    /**
     * Checks to see if a string contains a valid li-ending
     * A valid li-ending is one of {‘c’, ‘d’, ‘e’, ‘g’, ‘h’, ‘k’, ‘m’, ‘n’, ‘r’, ‘t’}.
     */
    const bool isLiEnding(const string &sIn);
    /**
     * Region1 is the substring that follows the first consonant (non-vowel) that follows a
     * vowel. Region1 may be empty (it often is for short words). Examples: Region1(try) is
     * empty, but Region1(definition) is inition
     */
    const string Region1(const string &sIn);
    /**
     * Region2 is the Region1 of Region1. In other words, Region2(definition) =
     * Region1(inition) = ition.
     */
    const string Region2(const string &sIn);
    /**
     * The preceder is the part of a word before a given suffix. For example, if the suffix is ing
     * then the preceder of talking is talk.
     */
    const string Preceder(const string &sIn, const string &suffix);
    /**
     * A string ends in a short syllable if either
     * 1. It ends with a non-vowel followed by a vowel followed by a non-vowel that is not one of {‘w’, ‘x’ or ‘y’}
     * 2. The string is only two characters long, and is a vowel followed by a non-vowel
     */
    const bool isShortSyllable(const string &sIn);
    /**
     * A word is called short if both (1) it ends in a short syllable and (2) its Region1 is empty.
     * For example, bed, shed, and shred are short words, but bead, embed and beds are not.
     */
    const bool isShort(const string &sIn);
    /**
     * Replace will erase a portion of string sIn starting at start to length of sIn
     * Replace then will push the string sNew to the back, if sNew is null then nothing will be pushed to back
     */
    string Replace(string &sIn, const string &sNew, int start);
    /**
     * Find if the suffix is in the sIn string
     * Return true if it is in it, false if not
     */
    const bool Find(const string &sIn, const string &suffix);
private:
    unsigned int lSuffix = 0; /**< This is the current length of the suffix */
};

#endif // STEM_H_INCLUDE
