#include "glm.hpp"
#include "Ray.hpp"
#include "string_cast.hpp"
#include <string>
#ifndef sphere_H
#define sphere_H

namespace csc305{
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
        inverseMatrix_ = calcInverseTransform();
      }

      void setScale(glm::vec3 scale){
        scale_ = scale;
        inverseMatrix_ = calcInverseTransform();
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

      void setSpecExp(int specExp){
        specExp_ = specExp;
      }

      //getters
      std::string getName(){
        return name_;
      }

      glm::vec3 getPos(){
        return pos_;
      }

      glm::vec3 getScale(){
        return scale_;
      }

      glm::vec3 getColor(){
        return color_;
      }

      float getKa(){
        return Ka_;
      }

      float getKd(){
        return Kd_;
      }

      float getKs(){
        return Ks_;
      }

      float getKr(){
        return Kr_;
      }

      int getSpecExp(){
        return specExp_;
      }

      glm::mat4 getInverseTransform(){
        return inverseMatrix_;
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
      glm::mat4 inverseMatrix_;

      //getInvsere Transformation Matrix
      glm::mat4 calcInverseTransform();
    };
}

#endif
