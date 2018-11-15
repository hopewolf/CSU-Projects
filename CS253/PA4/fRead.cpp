/* Name: Luke Burford
 * Date: 09/14/17
 * Email: lburford@rams.colostate.edu
 */

#include <fRead.h>
#include <lexo.h>
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


int fRead::read(char* in) {
        // initiate a new file stream using the char pointer in
    ifstream fIn(in);
    // lexographical sort class
    lexo lex = lexo();
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
        //.fail() checks to see if the value is invalid (ie not an String) (may be redundant)
//         if (fIn.fail()){
//             cerr << "Failed to recieve String as input" << endl;
//             return -1;
//         }
            //pass current to lexo to check the grammer, and then add to the vector
            lex.lexo::checkEng(current);
    }
    // call lexo to sort lexographicaly, then sort calls lexPrint to print the strings
    lex.lexo::lexSort();
    // once sorted then print
    lex.lexo::lexPrint();
    return 0; //at the end if it was able to fully execute then return 0 (complete)
    
}
