#include "Ray.hpp"
namespace csc305{

    //public
    //Default Constructor
    Ray::Ray(){
      start_ = glm::vec3(0,0,0);
      dir_ =  glm::vec3(1, 0, 0);
    }

    //Main Constructor
    Ray::Ray(glm::vec3 start, glm::vec3 dir){
      start_ = start;
      dir_ = dir;
    }

    //Move Constructor
    Ray::Ray(Ray && other) = default;

    //Move Operator
    Ray & Ray::operator=(Ray && other) = default;

    //Copy Constructor
    Ray::Ray(const Ray & other) = default;

    //Copy Operator
    Ray & Ray::operator=(const Ray & other) = default;

    //Deconstructor
    Ray::~Ray() = default;

    //Get Pos Along Ray
    glm::vec3 Ray::getRayPos(float t){
      return start_ + t*dir_;
    }

    //Get Inverted Ray
    Ray Ray::getInvertedRay(glm::mat4 transformMatrix){
      glm::vec4 homoStart(start_.x, start_.y, start_.z, 1);
      glm::vec4 homoDir(dir_.x, dir_.y, dir_.z, 0);

      glm::vec4 transformedStart = (transformMatrix * homoStart);
      glm::vec4 transformedDir = (transformMatrix * homoDir);
      return Ray(glm::vec3(transformedStart.x, transformedStart.y, transformedStart.z), glm::vec3(transformedDir.x, transformedDir.y, transformedDir.z));
    }

    //Private

}
