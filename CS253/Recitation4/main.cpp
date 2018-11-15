#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){

	int x = 0;
	int cnt[20];
  
    //fix for code was to init the array
    for(int i=0; i != 20; ++i)
       cnt[i] = 0;
    
	//check for correct number of args
	if (argc !=2)
	{
		cerr << "Usage: PA1 <filename>!" << endl;
		return -1;
	}

	ifstream istr(argv[1]);

	//Check if this file opens
	if (istr.fail())
	{
		cerr << "Cannot open file!" << endl;
		return -1;
	}
	
	istr >> x;
	if(istr.fail()) {
        cerr << "Empty file!" << endl;
        return -1;
    }
	
	//Read characters until it fails
	while(!istr.fail())
	{
		istr >> x;
		if ((x >= 0) && (x < 20))
			++cnt[x];
		else
		{
			cerr << "Number not in range!" << endl;
			return -1;
		}
	}
	
	if(istr.fail() && !istr.eof()) {
        cerr << "Wrong input!" << endl;
        return -1;
    }

	//Print values
	for(int  i = 0; i < 20; i++){
		cout << i << " " << cnt[i]<< endl;
	}

	istr.close();
	return 0;
}
