#ifndef __MODULE_COMPLEX__
#define __MODULE_COMPLEX__

#include <cmath> // pour std::sqrt
#include <helpers.hpp>

class complex
 {
  //private:
  public:

      float a,b; // a + i b

  public:

      float re() const { return a; } // partie réelle
      float im() const { return b; } // partie imaginaire

      complex operator-() const { return complex(-a,-b); }

      complex operator+(const complex & other) const;
      complex operator*(const complex & other) const;
      float abs() const;

      complex operator=(const complex & other) { a=other.a; b=other.b; return *this; }

  // ctor et init-ctor par defaut
  complex(float a_=0, float b_=0)
   : a(a_), b(b_)
  {}

  // copy-ctor
  complex(const complex & other)
   : a(other.a),b(other.b)
  {}

  ~complex()=default; // rien de spécial à faire
 };


#endif
// __MODULE_COMPLEX__
