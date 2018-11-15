#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::cerr;
#include <Reader.h>
//#include <HashTable.h>
#include <string>

int main(int argc, char* argv[])
{
    string a = "a z c b f g !";
    string b = "z y g f";
    cout << "string a: '" << a << "' string b: '" << b << "'" << endl << endl;
    cout << "HashTable Function Test: " << endl;
     HashTable ht1(33, 50);
     HashTable ht2;
     
     ht1 = ht2;
//     int x = ht1.Count();
//     x++;
//     cout << x + x << endl;
//     cout << ht1.Count() << endl;
    
//     HashTable* ht = new HashTable(99, 7);
//     ht1.Add(a);
//     cout << ht1.Count() << endl;
//     ht1.Resize(a.length());
//     ht1.Add(b);
//     cout << ht1.Count() << endl;
    
//    HashTable ht2 = HashTable(ht1);
//    HashTable ht2;
//     ht2.Resize(1);
//     ht2.Add(a);
//     cout << ht2.Contains(a) << endl;
//     ht2.Add(b);
//     cout << ht2.Contains(a) << endl;
//    ht1 = ht2; // causes a mem leak (dont know exactly what though)
    
    
//     cout << "Reader Function Test: " << endl; 
//     Reader r = Reader(a);
//     cout << "count: " << r.Count() << endl;
//     cout << "size: " << r.Size() << endl;
//     cout << "compare before resize: " << r.Compare(b) << endl;
//     cout << "resize: " << r.Resize(a.length()) << endl;
//     cout << "new size: " << r.Size() << endl;
//     cout << "compare after resize: " << r.Compare(b) << endl;
    //delete ht; 
    return 1;
}
