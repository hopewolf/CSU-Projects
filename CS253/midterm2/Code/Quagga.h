#ifndef QUAGGA_DEFINED
#define QUAGGA_DEFINED
#include <iostream>
#include <string>
using std::string;
#include <ZooProperty.h>

// Animal class
class Animal {
public:
  Animal() {animal_ctr++; PrintIf("Animal Constructor");}
  ~Animal() {animal_ctr--; PrintIf("Animal Destructor");}
  inline string Behave() {return WarmUp();}
  virtual void Eat() = 0; // since this is virtual it will look to see whatever obj type is calling Eat use the appropriate one
  string WarmUp() {return "???";}
  void PrintIf(const string& str) {if (debug_flag) std::cout << str << std::endl;}
  void SetDebug(bool flag) {debug_flag = flag;}
protected:
  static int animal_ctr;
  static bool debug_flag;
};

// Mammal class inherits Animal
class Mammal : public Animal {
public:
  Mammal() {mammal_ctr += animal_ctr; PrintIf("Mammal Constructor");}
  ~Mammal() {mammal_ctr -= animal_ctr; PrintIf("Mammal Destructor");}
//   void Eat() { std::cout << "food"<< std::endl; } // NOTE
  virtual string WarmUp() {return "Shiver";}

protected:
  int body_temperature;
  static int mammal_ctr;
};

// Equine class inherits Mammal
class Equine : public Mammal {
public:
 Equine() : equine_ctr(1) {PrintIf("Equine Constructor");}
  ~Equine() {PrintIf("Equine Destructor");}
  Equine(int ctr) : equine_ctr(ctr) {}//{std::cout << "Equine ctr: " << ctr << std::endl;} // NOTE I added the prints
  void Eat() {std::cout << "Grass" << std::endl;} // NOTE I ADDED AN endl for readablilty
protected:
  int equine_ctr;
};

// Quagga class inherits Equine and ZooProperty
class Quagga : public Equine, public ZooProperty {
public:
 Quagga(int x) : Equine(2^x), ZooProperty(1000), ctr(x) {PrintIf("Quagga Constructor");} // 2^x is 2 XOR x (aka NOT 2nd bit)
  ~Quagga() {PrintIf("Quagga Destructor");}
  int CtrSum() {return ctr + equine_ctr + mammal_ctr + animal_ctr;}
  virtual string WarmUp() {return "Buck";}
protected:
  int ctr;
  bool debug_flag;
};

#endif // QUAGGA_DEFINED
