#include <Reader.h>
#include <sstream>
using std::istringstream;
#include <iostream>

Reader::Reader(const string& input)
{
  istringstream istr(input);
  string str;
  istr >> str;
  while(!istr.fail()) {
    ht.Add(str);
    istr >> str;
  }
}

int Reader::Compare(string comp_str) 
{
  int ctr = 0;
  istringstream istr(comp_str);
  string str;
  istr >> str;
  while(!istr.fail()) {
    if (ht.Contains(str)) ctr++;
    istr >> str;
  }
  return ctr;
}
