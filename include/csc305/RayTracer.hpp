#include "Scene.hpp"
#include "PPM.hpp"

#ifndef ppm_h
#define ppm_h
namespace csc305{
    class RayTracer{
    public:

      //Default Constructor
      RayTracer();

      //Main Constructor
      RayTracer(Scene scene);

      //Move Constructor
      RayTracer(RayTracer && other);

      //Move Operator
      RayTracer & operator=(RayTracer && other);

      //Copy Constructor
      RayTracer(const RayTracer & other);

      //Copy Operator
      RayTracer & operator=(const RayTracer & other);

      //Deconstructor
      ~RayTracer();

      //Save Image
      // Modified From Given Code
      void save_imageP3(char* fname);

    private:
      //Attributes
      Scene scene_;
      PPM ppm_;
    };
}
#endif
