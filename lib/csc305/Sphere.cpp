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
    inverseMatrix_ = calcInverseTransform();
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
    inverseMatrix_ = calcInverseTransform();
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
  //getInvsere Transformation Matrix
  glm::mat4 Sphere::calcInverseTransform(){
    glm::vec4 col1(1,0,0,0);
    glm::vec4 col2(0,1,0,0);
    glm::vec4 col3(0,0,1,0);
    glm::vec4 col4(pos_.x,pos_.y,pos_.z,1);
    glm::mat4 translation(col1, col2, col3, col4);

    glm::vec4 col21(scale_.x,0,0,0);
    glm::vec4 col22(0,scale_.y,0,0);
    glm::vec4 col23(0,0,scale_.z,0);
    glm::vec4 col24(0,0,0,1);
    glm::mat4 scale(col21, col22, col23, col24);

    glm::mat4 result = translation * scale;

    return glm::inverse(result);
  }
}
