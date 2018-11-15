#include <Pixel.tpp>
#include<algorithm>
using std::min;
using std::max;

void HSV::rgb2hsv(double red, double green, double blue)
{
  double min_value = min(red, min(green, blue)); 
  value = max(red, max(green, blue));
  if (value <=  0.0) {
    value = 0.0;
    hue = nan("");
    saturation = 0.0;
    return;
  }
  
  double delta = value - min_value;
  if (delta <= 0.0) {
    hue = nan("");
    saturation = 0.0;
  }
  saturation = delta / value;

  if (red >= value) hue = (green - blue) / delta;
  else if (green >= value) hue = 2.0 + (blue - red) / delta;
  else hue = 4.0 + (red - green) / delta;

  hue *= 60.0;
  if (hue < 0.0) hue += 360.0;
}

HSV::operator unsigned char() const
{
  double value = double(*this);
  if (value < 0) return 0;
  if (value > 255) return 255;
  else return value;
}
