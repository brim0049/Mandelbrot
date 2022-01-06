#ifndef __MODULE_BITMAP__
#define __MODULE_BITMAP__

#include <cstddef> // pour size_t
#include <string>
#include <fstream>
#include <stdexcept>

#include <rgb.hpp>

////////////////////////////////////////
//
// Classe minimale pour un bitmap en
// 24 bits
//
class bitmap
 {
  private:

      size_t width, height;
      rgb * pixels;

 public:


     void set_pixel(size_t x, size_t y, const rgb & color) { pixels[y*width+x]=color; }

     void save_as_ppm(const std::string & filename)
      {
       std::ofstream out(filename,std::ios::binary);

       if (out)
        {
         // ref: https://en.wikipedia.org/wiki/Netpbm_format
         out
          << "P6 "
          << width << ' ' << height << ' '
          << 255
          << std::endl;

         // binary write!
         out.write((char*)pixels, width*height*sizeof(rgb));
        }
       else
        throw std::runtime_error("Ne peut sauver "+filename);
      }

  bitmap(size_t w_, size_t h_)
   : width(w_),
     height(h_),
     pixels(new rgb[w_*h_])
   {}

  ~bitmap()
   {
    delete[] pixels;
   }
 };


#endif
// __MODULE_BITMAP__
