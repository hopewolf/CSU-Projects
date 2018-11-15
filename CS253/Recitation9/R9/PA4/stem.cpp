#include "stem.h"
#include <string>

// This is for demonstration only
// You should not use this in your PA4

string Stem::step1(string s)
{
    // return s if s is empty
	if(s.size() == 0)
		return s;
    // remove the first apostrophe
	if(s[0] == '\'')
		return s.substr(1, s.size()-1);
    return s;
}

void Stem::step2(string &s)
{
    if(s.size() >= 5 && s.substr(s.size()-4, 4) == "sses") 
    {
        s.pop_back();
        s.pop_back();
    }
}

void Stem::step3(string &s)
{
    if(s.size() >= 4 && s.substr(s.size()-3, 3) == "ing") 
    {
        size_t i = 0;
        for (; i != s.size() - 3; ++i)
        {
            if (isVowel(s[i]))
                break;
        }
        if (i != s.size() - 3) // means a vowel in preceder
        {
            s.pop_back();
            s.pop_back();
            s.pop_back();
        }
    }
}

bool Stem::isVowel(const char& c)
{
    switch (c) 
    {
        case 'a':
            return 1;
        case 'e':
            return 1;
        case 'i':
            return 1;
        case 'o':
            return 1;
        case 'u':
            return 1;
            
        default:
            return 0;
    }
}

