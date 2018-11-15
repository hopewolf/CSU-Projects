#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;    // I ADDED ALL THIS SHIT ABOVE
#include <HashTable.h>

HashTable::HashTable(const HashTable& src) : size(src.size), factor(src.factor), counter(src.counter)
{
  table = new string[size];
  for(unsigned int index = 0; index < size; index++) {
    table[index] = src.table[index];
  }
}

HashTable::~HashTable()
{
  delete [] table;
  table = 0;
  size = 0;
}

HashTable& HashTable::operator = (const HashTable& src)
{
  table = new string[size];
  cout << size << endl;
  for(unsigned int index = 0; index < size; index++) {
    table[index] = src.table[index];
  }
  size = src.size;
  factor = src.factor;
  //delete [] table; //i added this, this is only a partial fix
  return *this; // returns a pointer to this hashTable, could be the source of mem leak
}

unsigned int HashTable::Resize(unsigned int new_size)
{
  string* temp = table; // set a temp pointer to the table (pointer to a string)
  table = new string[new_size]; //set table to a new empty array of strings pointing to the first string
  for(unsigned int index = 0; index < new_size; index++) {
    table[index] = temp[index];
  }
  delete [] temp;
  size = new_size;
  return size;
}

int HashTable::Hash(const string& str) const
{
  int code = 1;
  for(unsigned int index = 0; index < str.length(); index++) {
    code *= CharCode(str.at(index));    //charCode = 2 + int(ch)
  }
  cout << "Hash for: " << str << " is: " << code % size << endl; // I ADDED THIS
  return code % size;
}

bool HashTable::Contains(const string& str)
{
    cout << "Getting the contains hash index: "; // i added this
  int index = Hash(str);
  return (0 == str.compare(table[index]));
}

bool HashTable::Add(const string& str)
{
  cout << "Getting the add hash index: "; // i added this
  int index = Hash(str);
  if (table[index].empty()) {
    table[index] = str;
    counter++;
    return false;
  }
  else if (0 == str.compare(table[index])) {
    return false;
  }
  else {
    Resize(size * factor);
    Add(str);
    return true;
  }
}
