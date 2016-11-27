#include "lodepng.h"
#include <iostream>
#include <iomanip>


void halftone2src(const char* filename)
{
  std::vector<unsigned char> image; //the raw pixels
  unsigned width, height;

  //decode
  unsigned error = lodepng::decode(image, width, height, filename);

  //if there's an error, display it
  if (error) {
      std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
      return;
  }

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA...
  int single = 0;
  //std::cout << "Size:" << image.size() << std::endl;
  for (size_t i=0; i<image.size(); i++) {
    unsigned char data = image[i];
    if ((i != 0) && (i % (4*8) == 0)) {
      std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << single << ", ";
      single = 0;
    }
    if ((i != 0) && (i % (4*8*16) == 0)) {
      std::cout << std::endl;
    }
    if (i % 4 == 0) { //looking at red
      single = single >> 1;
      if (data > 127) {
        single |= 0x80; //black
      }
    }
    i++;
  }
  std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << single << ", ";
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  const char* filename = argc > 1 ? argv[1] : "chad_h4x4a.png";

  halftone2src(filename);
}

