#include "stem.h"
#include <string>

// This is for demonstration only
// You should not use this in your PA4

string Stem::step1(string s)
{
	if(s.size() == 0)
		return s;
	if(s[0] == '\'')
		return s.substr(1, s.size()-1);
    return s;
}

void Stem::step2(string &s)
{
    if(s.size() >= 4 && s.substr(s.size()-4, 4) == "sses") 
    {
        s.pop_back();
        s.pop_back();
    }
}
