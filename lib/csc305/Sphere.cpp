#include "Sphere.hpp"

namespace csc305{
  //Public

  // Default Constructor
  Sphere::Sphere(){
    pos_ = glm::vec3(0,0,0);
    scale_ = glm::vec3(0,0,0);
    color_ = glm::vec3(0,0,0);
    Ka_ = 0.0;
    Kd_ = 0.0;
    Ks_ = 0.0;
    Kr_ = 0.0;
    specExp_ = 1;
  }

  //main Constructor
  Sphere::Sphere(std::string name, glm::vec3 pos, glm::vec3 scale, glm::vec3 color, float Ka, float Kd, float Ks, float Kr, int specExp){
    name_ = name;
    pos_ = pos;
    scale_ = scale;
    color_ = color;
    Ka_ = Ka;
    Kd_ = Kd;
    Ks_ = Ks;
    Kr_ = Kr;
    specExp_ = specExp;
  }

  //Move Constructor
  Sphere::Sphere(Sphere && other) = default;

  //Move Operator
  Sphere & Sphere::operator=(Sphere && other) = default;

  //Copy Constructor
  Sphere::Sphere(const Sphere &) = default;

  //Copy Operator
  Sphere & Sphere::operator=(const Sphere &) = default;

  //Deconstructor
  Sphere::~Sphere() = default;


  //Private
}
