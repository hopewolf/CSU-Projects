#ifndef ZOO_PROPERY_DEFINED
#define  ZOO_PROPERY_DEFINED

// ID class
class ID {
public:
 ID() : identifier() {identifier = new int(global_identifier++);}
  ~ID() {delete identifier; identifier = NULL;}
  int Identifier() const {return *identifier;}
protected:
  int* identifier;
  static int global_identifier;
};

// ZooProperty class inherits ID
class ZooProperty : public ID {
public:
  ZooProperty(const ZooProperty& zp) {std::cout << "ZooProperty Constructor" << std::endl;}
  virtual ~ZooProperty() {std::cout << "ZooProperty Destructor" << std::endl;}
  ZooProperty(int cost) : price(cost) {}

protected:
  int price;
};

#endif //  ZOO_PROPERY_DEFINED
