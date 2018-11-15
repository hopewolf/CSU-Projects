//#include <Pixel.cpp>
#include <Pixel.tpp>
#include <Image.tpp>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
template<typename TYPE>
void printRGB(RGB<TYPE> myRGB){
	cout<<"("<<myRGB.Red()<<","<<myRGB.Green()<<","<<myRGB.Blue()<<")"; // does not print a newline
}

void printHSV(HSV myHSV){
	cout<<"["<<myHSV.Hue()<<","<<myHSV.Saturation()<<","<<myHSV.Value()<<"]"<<endl;
}
/* NOTE on rgbTest1:
 * - Cant make a string RGB pixel due to invalid static_cast from string to double, and doesnt compile.
 * - Everything else at first glance works fine.
 */ 
void rgbTest1(){
	cout<<"RGB<int> test:"<<endl;
	RGB<int> myRGBi(1,4,255);
	//cout<<"("<<myRGBi.Red()<<","<<myRGBi.Green()<<","<<myRGBi.Blue()<<")"<<endl;
	printRGB(myRGBi);
	cout<<"\nRGB<double> test:"<<endl;
	RGB<double> myRGBd(1,2.4, 34.667);
	//cout<<myRGBd.Red()<<endl<<myRGBd.Green()<<endl<<myRGBd.Blue()<<endl;
	printRGB(myRGBd);
	cout<<"\nRGB<float> test:"<<endl;
	RGB<float> myRGBf(1.1, 0.0, 3.14);
	printRGB(myRGBf);
	//RGB<string> myRGBs("Rojo", "Verde", "Azul"); // Invalid static_cast from string to double does not compile.
	//printRGB(myRGBs);
	cout<<"\nRGB<char> test:"<<endl;
	RGB<char> myRGBc('r','g','b');
	printRGB(myRGBc);
	cout<<"\nUninitialized then assign RGB<int>"<<endl;
	RGB<int> unitRGBi;
    cout << "Uniniitialized: ";
	printRGB(unitRGBi);
	unitRGBi = myRGBi;
    cout << "\nInitialize w/ RGB<int>: ";
	printRGB(unitRGBi);
    cout << endl; // printRGB doesnt newline
return;
}

/* NOTE on hsvTest1:
 * - Seems to have a conversion error when making a HSV pixel from a RGB one (the number seems wrong)
 * but it is based off an online converter so it might not be a relevant problem.
 */ 
void hsvTest1(){
	cout<<"HSV with no initialization:"<<endl;
	HSV myHSV;
	printHSV(myHSV);
	cout<<"HSV with 42.7 initialization:"<<endl;
	HSV numHSV(42.7); // gives a "grayvalue", hue=nan & saturation=0 pixel
	printHSV(numHSV);
	cout<<"Assign HSV = RGBint(5,7,11):"<<endl;
	RGB<int> rgbInt(5, 7, 11); // make a Int RGB pixel
	HSV HSVfromRGB(rgbInt); // make a HSV pixel using RGB pixel values (seems to do it incorrectly) based off of this site: https://codebeautify.org/rgb-to-hsv-converter
	printHSV(HSVfromRGB);
	cout<<"And make RGB<int> rgbName(HSV)"<<endl;
	RGB<int> rgbInt2(HSVfromRGB); // make a RGB pixel using a HSV pixel that uses a RGB pixel
	printRGB(rgbInt2);
	cout<<"\nNow make RGB<double> from HSV(5)"<<endl;
	HSV anotherHSV(5); //int HSV pixel
	printHSV(anotherHSV);
	RGB<double> dblRGB(anotherHSV); // declare a double RGB pixel using a int HSV pixel (might be a conversion problem)
	printRGB(dblRGB);
    cout << endl; // printHSV doesnt newline
}

/* NOTE cnvtTest1:
 *  -When you convert from a double HSV to a char RGB in cnvtTest1 and print the char RGB, prints an unknown
 * char (obviously its because the ascii table doesn't know a char for 124.277 but its still worth noting).
 * 
 */
void cnvtTest1(){
	cout<<"RGB<char> charRGB('r','g','b'); HSV charHSV(charRGB) then back"<<endl;
	RGB<char> charRGB('r','g','b');
	printRGB(charRGB);
    cout << " ";
	HSV charHSV(charRGB);
	printHSV(charHSV);
	RGB<char> char2RGB(charHSV);
	printRGB(char2RGB);
	cout<<"\nUsing charHSV to make RGB<int>"<<endl;
	RGB<int> intcharRGB(charHSV);
	printRGB(intcharRGB);
	cout<<"\nusing charHSV to make RGB<double>"<<endl;
	RGB<double> dblcharRGB(charHSV);
	printRGB(dblcharRGB);
    cout << endl;
	
	cout<<"\nDouble to HSV to Char, then int, then float:"<<endl;
	RGB<double> dble2RGB(2.3, 97.7, 9.1);
	printRGB(dble2RGB);
	HSV dblHSV (dble2RGB);
	printHSV(dblHSV);
	RGB<char> char3RGB(dblHSV);
	printRGB(char3RGB); // this prints an unknown char and still compiles and runs just fine
	RGB<int> int2RGB(dblHSV);
	printRGB(int2RGB);
	RGB<float> floatRGB(dblHSV);
	printRGB(floatRGB);
    cout << endl;
	return;
}

void cnvtTest2(){
	RGB<int> rgbInt(49, 70, 99);
	printRGB(rgbInt);
	cout<<" " << double(rgbInt)<<endl; // Prints the (r+g+b)/3 defined by the RGB opereator double() const
	printRGB(RGB<char>(rgbInt));
	
	cout<< " " << (unsigned char)rgbInt<<endl; // Prints the char value (probably truncated) defined by RGB operator unsigned char() const
	
	HSV newHSV(rgbInt);
	cout<<(unsigned char)newHSV<<endl; // prints the value of the HSV pixel, defined by HSV operator unsigned char() const in Pixel.cpp 
	return;
}

template<typename PIXEL>
void printImageTwoD(Image<PIXEL> img){
	int width = img.Width();
	int height = img.Height();
	int w = 0;
	int h = 0;
	cout<<"w: "<<width<<", h: "<<height<<endl;
	cout<<"size: "<<img.Size()<<endl<<"Use_Count: "<<img.use_count()<<endl;
	cout<<"shared ptr: "<<img.data_pointer()<<endl;
	if(img.Size() == 0){
		return;
	}
	for(unsigned int i = 0; i< (unsigned int)(width*height); i++){
		
		//myIntImg[i] = *(new RGB<int> rgb(i,i,i));
		//printRGB(*myIntImg[i]);
		//img(w, h);
		//cout<<w<<","<<h<<" : "<<i<<" = ";
		printRGB(img(w, h));
		//printRGB(img[i]);
		//w++;
		w++;
		if(w>=width){
			w=0;
			h++;
			cout<<endl;
		}
	}
	
}

template<typename PIXEL>
void printImageOneD(Image<PIXEL> img){
	shared_ptr<PIXEL> data = img.data_pointer();
	for(unsigned int i = 0; i<img.Size(); i++){
		
		
		//Chase shared pointer, get address, add offset then chase to pixel[i] and print
		printRGB(*(((&(*data))+i)));
		
		if((i+1)%img.Width() ==0){
			//allows for formatting
			cout<<endl;
		}
	}
}

void imageTest1(){
	int width = 4;
	int height = 2;
	RGB<int> pix(1,1,1);
	Image<RGB<int>> myIntImg(width, height,pix);
	int w = 0;
	int h = 0;
	cout<<"Using 1D access to populate"<<endl;
	for(unsigned int i = 0; i< (unsigned int)(width*height); i++){
		
		//myIntImg[i] = *(new RGB<int> rgb(i,i,i));
		//printRGB(*myIntImg[i]);
		myIntImg(w, h);
		//cout<<w<<","<<h<<endl<<i<<endl;
		//printRGB(myIntImg(w, h));
		RGB<int>* temp =new RGB<int>(i,i,i);
		//printRGB(*temp);
		shared_ptr<RGB<int> > data = myIntImg.data_pointer();
		*(((&(*data))+i)) = *temp; // <----- O GOOD GOD WHY?!?!? I think that this just gets the pixel[i]
		printRGB(*(((&(*data))+i)));
		//cout<<myIntImg
		//myIntImg(w,h) = *temp;
		//myIntImg[i].get() = *temp;
		w++;
		if(w>=width){
			w=0;
			h++;
			cout<<endl;
		}
	}
	cout<<endl<<endl;
	cout<<"Using Ptr Arithmatic to walk"<<endl;
	printImageOneD(myIntImg);
	cout<<"Using 2D access"<<endl;
	printImageTwoD(myIntImg); // 2D access seems to fill incorrectly (may want to GDB to really know why)
}

void imageTest2(int W, int H){
	RGB<int> pix(1,2,3);
	//Image<RGB<int> > myImg(W,H,pix);
	for(int height = 1; height <=H; height++){
		for(int width = 1; width <=W; width ++){
			//printRGB(myImg(width, height));
			Image<RGB<int> > myImg(width, height,pix);
			printImageTwoD(myImg);
			cout<<endl;
		}
		cout<<endl;
		
	}
}

void imageTest3(int w, int h){
	RGB<int> pix(1,1,1);
	Image<RGB<int> >myImg(w,h,pix);
	printImageOneD(myImg);
	printImageTwoD(myImg);
}

/* NOTE imageMemTest1:
 * - Use valgrind on this to better understand what is leaking.
 * - Just making a Image<RGB<int> > myImg (w,h,pix) leaks 3 blocks (4 allocs, 1 free).
 * - When you print it 1D or 2D w/ same declaration leaks 6 blocks (9 allocs, 2 frees).
 * - Obviously if height is 0 and width is 0 then leak nothing, else leak mem
 * - Copy constructor also leaks memory (even if Height and Width is 0) passed image by value leaks one shared_ptr
 */
void imageMemTest1(int w, int h) {
    RGB<int> pix(5,8,11);
    //cout << "Image created with 2 doubles: " << endl;
    Image<RGB<int> > myImg(w,h,pix);
    printImageOneD(myImg);
    cout << "\nImage created as a copy constructor: " << endl;
    //Image<RGB<int> > newImg(myImg);
    //printImageTwoD(newImg);
    return;
}

int main(int argc, char** argv){
	//rgbTest1();
	//hsvTest1();
	//cnvtTest1();
	//cnvtTest2();
	//imageTest1();
	//imageTest2(4,4);
	//imageTest3(3,3);
    //imageMemTest1(4,3);
    RGB<HSV> myRGB(1,2,3);
    //cout << myRGB.Red();
    //printRGB(myRGB);
    
    
	return 0;
}

