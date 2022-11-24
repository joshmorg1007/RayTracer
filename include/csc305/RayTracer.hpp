#include "Scene.hpp"
#include "PPM.hpp"
#include "Ray.hpp"
#include "glm.hpp"
#include <limits>
#include <cmath>

#ifndef raytracer_h
#define raytracer_h
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

      //RayTrace Scene
      void rayTraceScene();

      //save image
      void saveImage();

    private:
      //Attributes
      Scene scene_;
      PPM ppm_;

      // Recursive raytrace helper function
      glm::vec3 raytrace(Ray ray, int depth);

      // Helper function to get ray from eye to pixel
      Ray eyeToPixelRay(int c, int r, int nCols, int nRows);

      bool checkValidSolution(Ray ray);

      float solveIntersection(Ray ray);
    };
}
#endif
