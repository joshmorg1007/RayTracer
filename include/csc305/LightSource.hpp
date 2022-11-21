#include "glm.hpp"
#ifndef lightsource_H
#define lightsource_H

namespace seng305{
    class LightSource{
    public:

      // Default Constructor
      LightSource();

      // Main Constructor
      LightSource(glm::vec3 pos, float intensity);

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

    private:
      // Attributes
      glm::vec3 pos_;
      float intensity_;
    };
}

#endif
