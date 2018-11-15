#ifndef PIXEL_TPP
#define PIXEL_TPP
#include <math.h>
#include <cmath>
class HSV;

class Pixel {
public:
  virtual ~Pixel() {}
  virtual operator unsigned char() const = 0;
  virtual operator double() const = 0;
};

template<typename TYPE>
class RGB : public Pixel {
public:
  RGB() : red(static_cast<TYPE>(0)),
	  green(static_cast<TYPE>(0)),
	  blue(static_cast<TYPE>(0)) {}
  RGB(const TYPE& r, const TYPE& g, const TYPE& b)
    : red(r), green(g), blue(b) {}
  RGB(const HSV& hsv);
  ~RGB() {}

  // type conversions
  virtual operator unsigned char() const;
  operator double() const;
  
  // accessors
  inline const TYPE& Red() const {return red;}
  inline const TYPE& Green() const {return green;}
  inline const TYPE& Blue() const {return blue;}

  // mutators
  inline TYPE& Red() {return red;}
  inline TYPE& Green() {return green;}
  inline TYPE& Blue() {return blue;}

protected:
  void hsv2rgb(double hue, double saturation, double value);
  
  TYPE red;
  TYPE green;
  TYPE blue;
};

class HSV : public Pixel {
public:
  HSV() : hue(nan("")), saturation(0.0), value(0.0) {}
  HSV(double grayvalue) : hue(nan("")), saturation(0.0), value(grayvalue) {}
  template<typename TYPE> HSV(RGB<TYPE> rgb);
  ~HSV() {}

  virtual operator unsigned char() const;
  virtual operator double() const {return value;}
  template<typename TYPE> operator RGB<TYPE>() const;

  inline double Hue() const {return hue;} 
  inline double Saturation() const {return saturation;}
  inline double Value() const {return value;}

protected:
  void rgb2hsv(double red, double green, double blue);
  
  double hue;
  double saturation;
  double value;
};

template<typename TYPE>
RGB<TYPE>::RGB(const HSV& hsv)
{
  hsv2rgb(hsv.Hue(), hsv.Saturation(), hsv.Value());
}

template<typename TYPE>
RGB<TYPE>::operator unsigned char() const
{
  double value = static_cast<double>(*this);
  if (value >= 255.0) return static_cast<unsigned char>(255);
  if (value <= 0.0) return static_cast<unsigned char>(0);
  else return static_cast<unsigned char>(value);
}

template<typename TYPE>
RGB<TYPE>::operator double() const
{
  double red = static_cast<double>(Red());
  double green = static_cast<double>(Green());
  double blue = static_cast<double>(Blue());
  return (red+green+blue)/3;
}

template<typename TYPE>
void RGB<TYPE>::hsv2rgb(double hue, double saturation, double value)
{
  if (saturation <= 0.0) {
    red = green = blue = value;
    return;
  }
  if (hue >= 360) hue = 0;
  hue /= 60;
  int i = hue;
  double ff = hue - i;
  double p = value * (1.0 - saturation);
  double q = value * (1.0 - (saturation * ff));
  double t = value * (1.0 - (saturation * (1.0 - ff)));

  switch(i) {
  case 0: red = value;
    green = t;
    blue = p;
    return;
  case 1: red = q;
    green = value;
    blue = p;
    return;
  case 2: red = p;
    green = value;
    blue = t;
    return;
  case 3: red = p;
    green = q;
    blue = value;
    return;
    
    
  }
}

template<typename TYPE>
HSV::HSV(RGB<TYPE> rgb)
{
  rgb2hsv(static_cast<double>(rgb.Red()),
	  static_cast<double>(rgb.Green()),
	  static_cast<double>(rgb.Blue()));
}

#endif // PIXEL_TPP
