#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
using std::string;

class HashTable {
public:
  HashTable(unsigned int sz = 99, unsigned int f = 7) 
    : size(sz), factor(f), counter(0) { table = new string[size]; }
  HashTable(const HashTable& src);
  ~HashTable();
  
  HashTable& operator = (const HashTable& src);
  inline unsigned int Count() const {return counter;}
  inline unsigned int Size() const {return size;}
  unsigned int Resize(unsigned int resize);
  inline int CharCode(unsigned char ch) const {return 2 + int(ch);}
  int Hash(const string& str) const;
  bool Contains(const string& str);
  bool Add(const string& str);

protected:
  unsigned int size;
  unsigned int factor;
  unsigned int counter;
  string* table;
};

#endif // HASH_TABLE_H
