#include <Quagga.h>
int Animal::animal_ctr = 0;
bool Animal::debug_flag = false;
int Mammal::mammal_ctr = 0;
int ID::global_identifier = 0;

int main (int argc, char* argv[]) {
// NOTE YOU CANT MAKE A MAMMAL OR A ANIMAL ALONE!!!!
//    Animal* avec[4];
//     Quagga q = Quagga(1);
//     q.Eat();
//    avec[1] = &q;
//    avec[1]->Eat();
//      ZooProperty zp = ZooProperty(q);
//     Equine e1 = Equine();
//     Quagga q1 = Quagga(2);
//     Quagga q2 = Quagga(3);

//     std::cout << "Quagga WarmUp: " << q1.WarmUp() << std::endl; // will use Quagga method
//     std::cout << "CtrSum: " << q2.Quagga::CtrSum() << std::endl;
    

     Quagga* q3 = new Quagga(0);
//     std::cout << "Behave: " << q3.Quagga::Behave() << std::endl;
//     std::cout << "WarmUp: " << q3.WarmUp() << std::endl;
//     
//     q1.SetDebug(true);
//         Animal* m = new Quagga(2);
//         delete m;
//       std::cout >> m -> Behave() >> std::endl;
    ZooProperty zp(1);
    ZooProperty* zp1 = new ZooProperty(&q3);
    delete zp1;
    return 0;   
}
