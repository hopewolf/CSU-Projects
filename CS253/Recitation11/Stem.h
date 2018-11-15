/**
 * @file Stem.h
 * @author Jason
 * @date 7 Nov 2017
 * @brief This is an sample stem header file
 * <br> Of course I need a new line for briefs
 * 
 * 
 * @see http://www.cs.colostate.edu/~cs253/Fall17/
 */

#ifndef STEM_H
#define STEM_H

#include <iostream>
#include <vector>
#include <string>

/**
 * @brief My Stemmer class
 * 
 * Detailed explanation about my stemmer class.
 */
class Stem {
public:
    /**
     * @brief Stem constructer
     * 
     * Some detailed explanation about this constructer. And @p s is the parameter.
     * Constructer never returns anything, including @c void or <code>int</code>.
     * Are you sure you don't know how to use a constructer? Here is an example
     * @code 
     * Stem *stem_ins = new Stem("word1");
     * @endcode
     * Clear enough?
     * But I'm not done yet.
     * Here is more typesetting using <b>HTML</b> if you <i>still</i> remebers it.
     * 
     * 
     * @param s Stem constructer takes a string reference
     *          Of course we need two lines to explain one parameter
     * @return Told you no return
     * @note Nothing more to say
     * @warning Never use this code
     */
    Stem (string& s):stringToStem(s) {}
    
    /**
     * Just want to show that you can link to other functions, 
     * like the Stem() constructer.
     * Of course, #Stem works too.
     * How about Stem?
     */
    void Step1() {}
    
    /**
     * Let me try linking to Step1() or #Step1 or Step1.
     */
    void Step2() {}
private:
    string& stringToStem; /**< This is the string to stem */
};

#endif /* Over */
