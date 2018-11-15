/* Name: Luke Burford
 * Date: 09/14/17
 * Email: lburford@rams.colostate.edu
 */

#ifndef FREAD_H_INCLUDE
#define FREAD_H_INCLUDE

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

// fRead, reads files and tests if file type being read is valid
class fRead {
public:
    // read will return -1 if error, 0 if success
    int read(char* in);
};

#endif //FREAD_H_INCLUDE
