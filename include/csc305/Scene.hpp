#include "glm.hpp"
#include "Sphere.hpp"
#include "LightSource.hpp"
#include "Camera.hpp"
#include <string>
#ifndef scene_H
#define scene_H

namespace seng305{
    class Scene{
    public:

      // Default Constructor
      Scene();

      // Main Constructor
      Scene(Camera camera, Sphere* spheres, int numSpheres, LightSource* lightSources, int numLights, glm::vec3 backgroundColor, float ambientIntensity, std::string output);

      //Move Constructor
      Scene(Scene && other);

      //Move Operator
      Scene & operator=(Scene && other);

      //Copy Constructor
      Scene(const Scene & other);

      //Copy Operator
      Scene & operator=(const Scene & other);

      //Deconstructor
      ~Scene();

    private:
      // Attributes
      Camera camera_;
      Sphere* spheres_;
      int numSpheres_;
      LightSource* lightSources_;
      int numLights_;
      glm::vec3 backgroundColor_;
      float ambientIntensity_;
      std::string output_;
    };
}

#endif
