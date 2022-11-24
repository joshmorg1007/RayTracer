#include "glm.hpp"

#ifndef ray_h
#define ray_h
namespace csc305{
    class Ray{
    public:

      //Default Constructor
      Ray();

      //Main Constructor
      Ray(glm::vec3 start, glm::vec3 dir);

      //Move Constructor
      Ray(Ray && other);

      //Move Operator
      Ray & operator=(Ray && other);

      //Copy Constructor
      Ray(const Ray & other);

      //Copy Operator
      Ray & operator=(const Ray & other);

      //Deconstructor
      ~Ray();

      //Get Pos Along Ray
      glm::vec3 getRayPos(float time);

      //Get Inverted Ray
      Ray getInvertedRay(glm::mat4 transformMatrix);

      glm::vec3 getStart(){
        return start_;
      }

      glm::vec3 getDir(){
        return dir_;
      }

    private:
      //Attributes
      glm::vec3 start_;
      glm::vec3 dir_;

    };
}
#endif
