#ifndef __MODULE_RGB__
#define __MODULE_RGB__

#include <cstdint>

////////////////////////////////////////
//
// classe minimale pour définir un pixel
// avec une résolution de couleur 24 bits
//
class rgb
 {
  public:

      uint8_t r,g,b;

  // operator= pour assignation
  rgb operator=(const rgb & other)
   {
    r=other.r;
    g=other.g;
    b=other.b;
    return *this;
   }

  // ctor et init-ctor par defaut
  rgb(uint8_t r_=0,
      uint8_t g_=0,
      uint8_t b_=0)
   : r(r_),g(g_),b(b_)
   {}

  // copy-ctor
  rgb(const rgb & other)
   : r(other.r),g(other.g),b(other.b)
   {}
 };

#endif
// __MODULE_RGB__
