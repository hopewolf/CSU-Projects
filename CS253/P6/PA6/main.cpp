/* Name: Luke Burford
 * Date: 09/14/17
 * Email: lburford@rams.colostate.edu
 */

#include <fDriver.h>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;

int main(int argc, char* argv[]) {
/* TEMP TESTING STEM FUNCTIONS ONLY */

/* END OF TESTING */
    if(argc < 3) {
        cerr << "Missing file as argument" << endl;
        return -1;
    }
    fDriver fd = fDriver(argc);
    // process the files to be turned into lexo objects/vectors
    if(fd.read(argv) == -1)
        return -1;
    // calculate the matrix of Sim calcualtions between the files
    fd.calcMatrix();
    // print the results of Sim, pass in the number of files to check line length
//    fd.printDocMatrix();
    return 0;
 }
