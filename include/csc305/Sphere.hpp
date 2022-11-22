#include "glm.hpp"
#include <string>
#ifndef sphere_H
#define sphere_H

namespace seng305{
    class Sphere{
    public:

      // Default Constructor
      Sphere();

      // Main Constructor
      Sphere(std::string name, glm::vec3 pos, glm::vec3 scale, glm::vec3 color, float Ka, float Kd, float Ks, float Kr, int specExp);

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

      //setters
      void setName(std::string name){
         name_ = name;
      }

      void setPos(glm::vec3 pos){
        pos_ = pos;
      }

      void setScale(glm::vec3 scale){
        scale_ = scale;
      }

      void setColor(glm::vec3 color){
        color_ = color;
      }

      void setKa(float Ka){
        Ka_ = Ka;
      }

      void setKd(float Kd){
        Kd_ = Kd;
      }

      void setKs(float Ks){
        Ks_ = Ks;
      }

      void setKr(float Kr){
        Kr_ = Kr;
      }

      boid setSpecExp(int specExp){
        specExp_ = specExp;
      }

    private:
      // Attributes
      std::string name_;
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
