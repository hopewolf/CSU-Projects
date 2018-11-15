/* Name: Luke Burford
 * Date: 09/14/17
 * Email: lburford@rams.colostate.edu
 */

#include <fRead.h>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

int main(int argc, char* argv[]) {
/* TEMP TESTING STEM FUNCTIONS ONLY */

/* END OF TESTING */
    if(argc != 3) {
        cerr << "Missing file as argument" << endl;
        return -1;
    }
    fRead fr = fRead();
    return fr.read(argv[1], argv[2]);
 }
