#include <regex> // regular expr!
#include <iostream>
#include <algorithm> // std::max
#include <list>

#include <options.hpp>

namespace {

 ////////////////////////////////////////
 boost::program_options::options_description make_options()
  {
   boost::program_options::options_description desc;
   boost::program_options::options_description generic("Generic options");
   boost::program_options::options_description image("Image options");
   boost::program_options::options_description files("File options");


   generic.add_options()
    ("help,h", "shows help")
    ("version,V", "shows version")
    ("verbose,v", "verbose")
    ;

   files.add_options()
    ("output,o",boost::program_options::value<std::string>(),"output filename (should have a .ppm extension)");

   image.add_options()
    ("center,c",boost::program_options::value<std::string>(),"center of intest, a+ib")
    ("scale,s",boost::program_options::value<float>(),"scale (defaults to 2, (-2,-2)--(2,2))")
    ("aspect,a",boost::program_options::value<std::string>(),"aspect ratio (square, hdtv)")
    ("resolution,r",boost::program_options::value<int>(),"image size, in pixels")
    ("iterations,i",boost::program_options::value<int>(),"max iterations (defaults to 1000)")
    ;

   desc.add(generic);
   desc.add(image);
   desc.add(files);

   return desc;
  }

 ////////////////////////////////////////
 boost::program_options::positional_options_description make_positionals()
  {
   boost::program_options::positional_options_description positionals;
   positionals.add("input", -1);
   return positionals;
  }


 // passe-passe limite cradocque pour
 // initialiser les options une seule fois
 // (et court-circuiter les warnings des
 // variables initialisées mais pas utilisées)
 boost::program_options::options_description desc = make_options();
 boost::program_options::positional_options_description positionals = make_positionals();

 bool at_most_one(const std::list<bool> & opt)
  {
   int c=0;
   for (bool o:opt) c+=o;
   return c<2;
  }
} // anonymous namespace

////////////////////////////////////////
#define stringize__(x) #x
#define stringize(x) stringize__(x)

////////////////////////////////////////
void options::show_version()
 {
  std::cout
   << stringize(__PROGNAME__)
   << " "
   << stringize(__PROGVER__)
   << std::endl;
 }

////////////////////////////////////////
void options::show_help()
 {
  std::cout << desc << std::endl;
 }

////////////////////////////////////////
options::options(int argc, const char * const argv[])
 : options()
 {
  // parsing options
  boost::program_options::variables_map vm;

  boost::program_options::store(
   boost::program_options::command_line_parser(argc, argv).
    options(desc).positional(positionals).run(), vm);

  boost::program_options::notify(vm);


  // extracting options

  help=vm.count("help");
  version=vm.count("version");
  verbose=vm.count("verbose");

  if (!at_most_one({help,version}))
   throw boost::program_options::error("mutually exclusive options specified!");

  // extract filename
  if (vm.count("output"))
   output_filename=vm["output"].as<std::string>();

  // extract resolution
  if (vm.count("resolution"))
   resolution=vm["resolution"].as<int>();

  if (vm.count("iterations"))
   max_iterations=std::max(0,std::min(1000,vm["iterations"].as<int>()));

  // parse aspect
  if (vm.count("aspect"))
   {
    if (vm["aspect"].as<std::string>()=="square")
     aspect=aspect_ratio::square;
    else
     if (vm["aspect"].as<std::string>()=="hdtv")
      aspect=aspect_ratio::hdtv;
     else
      throw boost::program_options::error("unkown value "+vm["aspect"].as<std::string>());
   }
      
  // parse complex number
  if (vm.count("center"))
   {
    std::regex r("^(-)?\\s*(\\d+(\\.\\d+)?)\\s*([-+])i\\s*(\\d+(\\.\\d+)?)$");
    std::smatch m; // match result iterator (as std::string)
    
    std::string n=vm["center"].as<std::string>();

    if (std::regex_match(n.cbegin(),n.cend(),m,r))
     {
      //for (int i=0;i<6;i++) std::cout << "m[" << i << "]=" << m[i] << std::endl;
                                           
      float re=std::stof(m[2].str()); // partie reelle
      float im=std::stof(m[5].str()); // partie imaginaire
      if (m[1].matched) re=-re; // signe?
      if (m[4].str()=="-") im=-im; // signe partie imaginaire

      center=complex(re,im);
     }
   }

  // parse scale
  if (vm.count("scale"))
   scale=std::max(10e-30f,std::min(10.0f,vm["scale"].as<float>()));
 }
