#include "glm.hpp"
#ifndef sphere_H
#define sphere_H

namespace seng305{
    class Sphere{
    public:

      // Default Constructor
      Sphere();

      // Main Constructor
      Sphere(glm::vec3 pos, glm::vec3 scale, glm::vec3 color, float Ka_, float Kd_, float Ks_, float Kr_, int specExp_);

      //Move Constructor
      Sphere(Sphere && other);

      //Move Operator
      Sphere & operator=(Sphere && other);

      //Copy Constructor
      Sphere(const Sphere &);

      //Copy Operator
      Sphere & operator=(const Sphere &);

      //Deconstructor
      ~Sphere();

    private:
      // Attributes
      glm::vec3 pos_;
      glm::vec3 scale_;
      glm::vec3 color_;
      float Ka_;
      float Kd_;
      float Ks_;
      float Kr_;
      int specExp_;
    };
}

#endif
