#include <iostream>
#include <algorithm> // pour max, max_element, etc.

#include <options.hpp>

#include <rgb.hpp>
#include <palette.hpp>
#include <bitmap.hpp>

#include <helpers.hpp>
#include <complex.hpp>


////////////////////////////////////////
//
// Implémentation plutôt naïve de l'itération
//
int spin( const complex & c,
          int max_iter=100,
          float radius=2.0f
          )
 {
  complex z(c); // z=c mandelbrot
  complex c0(-0.8,0.156); // julia
  int i=0;

  while ( (i<max_iter)
          && (z.abs()<=radius) )
   {
    z=sqr(z)+c; //+c0; pour julia
    i++;
   }
  
  return (z.abs()<=radius) ? 0 : 1+transfer[i];
 }

////////////////////////////////////////
int main(int argc, char * argv[])
 {
  try
   {
    options opt(argc,argv);

    if (opt.version) { opt.show_version(); return 0; }
    if (opt.help) { opt.show_help(); return 0; }

    int resx=opt.resolution;
    int resy=opt.aspect==options::aspect_ratio::square ?
              opt.resolution : (opt.resolution*9)/16;
    
    float scaling=2*opt.scale/resx;
    float hx=resx/2.0f;
    float hy=resy/2.0f;

    if (opt.verbose)
     std::cout
      << "resolution : " << opt.resolution << std::endl
      << "aspect     : " << (opt.aspect==options::aspect_ratio::square ? "square":"hdtv") << std::endl
      << "w x h      : " << resx << "x" << resy << std::endl
      << "center     : " << opt.center.re() << "+i" << opt.center.im() << std::endl
      << "scale      : " << opt.scale << " (" << scaling << ")" << std::endl
      << "max iter   : " << opt.max_iterations << std::endl
      << "output     : " << opt.output_filename << std::endl
      ;

    bitmap fractale(resx,resy);

    #pragma omp parallel for
    for (int y=0;y<resy;y++)
     for (int x=0;x<resx;x++)
      {
       complex z( (x-hx)*scaling,
                  (y-hy)*scaling);

       fractale.set_pixel(x,y,palette[spin(z+opt.center,opt.max_iterations) ]);
      }

    fractale.save_as_ppm(opt.output_filename);
   }

  catch (boost::program_options::error & this_exception)
   {
    std::cerr << this_exception.what() << std::endl;
    return 1;
   }

  return 0;
 }
