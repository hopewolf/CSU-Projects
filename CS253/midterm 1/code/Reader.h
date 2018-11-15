#ifndef READER_H
#define READER_H

#include <HashTable.h>

class Reader {
public:
  Reader(const string& input); // constructor
  
  // counts the passed in string to the constructor, calls hashTable count to do so
  inline unsigned int Count() const {return ht.Count();}
  // gets the size of the hashTable
  unsigned int Size() {return ht.Size();}
  // resizes the hashTable size
  unsigned int Resize(unsigned int resize) {return ht.Resize(resize);}
  // compares the string passed to the constructor to the one passed into the resize
  int Compare(string comp_string);

protected:
  HashTable ht;
};

#endif // READER_h
