#include "LightSource.hpp"

namespace csc305{
  //Public

  // Default Constructor
  LightSource::LightSource(){
    pos_ = glm::vec3(0,0,0);
    intensity_ = glm::vec3(0,0,0);
  }

  //main Constructor
  LightSource::LightSource(std::string name, glm::vec3 pos, glm::vec3 intensity){
    name_ = name;
    pos_ = pos;
    intensity_ = intensity;
  }

  //Move Constructor
  LightSource::LightSource(LightSource && other) = default;

  //Move Operator
  LightSource & LightSource::operator=(LightSource && other) = default;

  //Copy Constructor
  LightSource::LightSource(const LightSource &) = default;

  //Copy Operator
  LightSource & LightSource::operator=(const LightSource &) = default;

  //Deconstructor
  LightSource::~LightSource() = default;


  //Private
}
