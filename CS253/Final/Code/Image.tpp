#ifndef IMAGE_TPP
#define IMAGE_TPP
#include<cstddef>
#include<memory>
using std::shared_ptr;

template<typename PIXEL>
class Image {
public:
  Image() {allocateMemory(0,0);}
  Image(unsigned int width, unsigned int height) {allocateMemory(width, height);}
  Image(unsigned int width, unsigned int height, const PIXEL& value) {allocateMemory(width, height); fill(value);}
  Image(const Image<PIXEL>& img) {allocateMemory(img.Width(), img.Height()); copyMemory(img);}
  ~Image() {deallocateMemory();}
  Image<PIXEL>& operator = (const Image& img) {deallocateMemory(); allocateMemory(img.Width(), img.Height()); copyMemory(img); return *this;}

  // simple acessors
  int Width() const {return width;}
  int Height() const {return height;}
  int Size() const {return size;}
  bool empty() const {return size == 0;}
  int use_count() const {return data.use_count();}
  shared_ptr<PIXEL> data_pointer() {return data;}

  // 1D random access
  const PIXEL& operator [] (unsigned int index) const {return data[index];}
  PIXEL& operator [] (unsigned int index) {return data[index];}

  // 2D random access
  const PIXEL& operator () (unsigned int x, unsigned int y) const {return rows[y].get() + x;}
  PIXEL operator () (unsigned int x, unsigned int y) {return *(rows[y].get() + x);}

protected:
  void allocateMemory(unsigned int w, unsigned int h);
  void deallocateMemory() {} /// deallocate does nothing?
  void copyMemory(const Image<PIXEL>& img);
  void fill(const PIXEL& value);

  unsigned int width;
  unsigned int height;
  unsigned int size;
  shared_ptr<PIXEL> data;
  shared_ptr<PIXEL>* rows;
};

/// Allocate internal memory for image; does not deallocate previous memory
template<typename PIXEL>
void Image<PIXEL>::allocateMemory(unsigned int w, unsigned int h)
{
  width = w;
  height = h;
  size = width * height;
  if (empty()) {
    data = shared_ptr<PIXEL>(NULL);
    rows = NULL;
  }
  else {
    PIXEL* first_pixel_ptr = new PIXEL[size]; /// 1 mem leak
    data = shared_ptr<PIXEL>(first_pixel_ptr); /// i think that this also leaks
    rows = new shared_ptr<PIXEL>[height];
    for(unsigned int i=0;  i < height; i++) {
      rows[i] = shared_ptr<PIXEL>(data, first_pixel_ptr+i);
    }
  }
}

// assumes size match
template<typename PIXEL>
void Image<PIXEL>::copyMemory(const Image<PIXEL>& img) 
{
  data = img.data;
  rows = new shared_ptr<PIXEL>[height];
  for(unsigned int i=0; i < height; i++) rows[i] = img.rows[i];
}

template<typename PIXEL>
void Image<PIXEL>::fill(const PIXEL& value) 
{
  PIXEL* ptr = data.get();
  PIXEL* end_ptr = ptr + height;
  for(; ptr != end_ptr; ptr++) *ptr = value;
}

#endif // IMAGE_TPP
