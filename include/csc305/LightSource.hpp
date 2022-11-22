#include "glm.hpp"
#include <string>
#ifndef lightsource_H
#define lightsource_H

namespace seng305{
    class LightSource{
    public:

      // Default Constructor
      LightSource();

      // Main Constructor
      LightSource(std::string name, glm::vec3 pos, glm::vec3 intensity);

      //Move Constructor
      LightSource(LightSource && other);

      //Move Operator
      LightSource & operator=(LightSource && other);

      //Copy Constructor
      LightSource(const LightSource &);

      //Copy Operator
      LightSource & operator=(const LightSource &);

      //Deconstructor
      ~LightSource();

      //setters
      void setPos(glm::vec3 pos){
        pos_ = pos;
      }

      void setIntensity(float intensity){
        intensity_ = intensity;
      }

      void setName(std::string name){
        name_ = name;
      }

    private:
      // Attributes
      glm::vec3 pos_;
      glm::vec3 intensity_;
      std::string name_;
    };
}

#endif
