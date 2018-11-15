/* Name: Luke Burford
 * Date: 09/14/17
 * Email: lburford@rams.colostate.edu
 */

#ifndef FREAD_H_INCLUDE
#define FREAD_H_INCLUDE

#include <string>
#include <iostream>
#include <fstream>

// fRead, reads files and tests if file type being read is valid
class fRead {
public:
    // read will return -1 if error, 0 if success
    int read(char* list, char* in);
};

#endif //FREAD_H_INCLUDE
