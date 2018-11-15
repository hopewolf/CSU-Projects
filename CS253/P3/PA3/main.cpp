/* Name: Luke Burford
 * Date: 09/14/17
 * Email: lburford@rams.colostate.edu
 */

#include <fRead.h>
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

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cerr << "Missing file as argument" << endl;
        return -1;
    }
    fRead fr = fRead();
    return fr.fRead::read(argv[1]);
}
