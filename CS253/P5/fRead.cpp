/* Name: Luke Burford
 * Date: 09/14/17
 * Email: lburford@rams.colostate.edu
 */

#include <fRead.h>
#include <lexo.h>
#include <StemExcep.h>
#include <string>
using namespace std;
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;
#include <fstream>
using std::ifstream;
using std::ws;


int fRead::read(char* list, char* in) {
    // stem exception to check stemming special cases
    StemExcep se = StemExcep();
    // creates the exception and replacement list (stem exception isnt used until lexo from here)
    if(se.initExcep(list))
        return -1; // StemExcep returned an error while init the file and vectors
    // initiate a new file stream using the char pointer in
    ifstream fIn(in);
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
    // remove any remaining ambigous string and add them to the vector to be sorted
    lex.clearAmb();
    // call lexo to sort lexographicaly, then sort calls lexPrint to print the strings
    lex.lexSort();
    // once sorted then print
    lex.lexPrint();
    return 0; //at the end if it was able to fully execute then return 0 (complete)
    
}
