#ifndef __MODULE_OPTIONS__
#define __MODULE_OPTIONS__

#include <complex.hpp>
#include <string>
#include <boost/program_options.hpp>

class options
 {
  public:

      enum class aspect_ratio { square, hdtv };

      // generic commands
      bool help;
      bool version;
      bool verbose;

      // resolution
      int resolution;
      aspect_ratio aspect;

      // point of interest
      complex center;
      float scale;

      int max_iterations;
  
      // files
      std::string output_filename;

  public:
  
      static void show_help();
      static void show_version();

  options()
   : help(false),
     version(false),
     verbose(false),
     resolution(1000),
     aspect(aspect_ratio::square),
     center(0),
     scale(2),
     max_iterations(1000),
     output_filename("output.ppm")
  {}


  options(int,const char * const []);

  ~options()=default;
 };

#endif
    // __MODULE_OPTIONS__
