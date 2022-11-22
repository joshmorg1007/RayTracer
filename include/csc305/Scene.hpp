#include "glm.hpp"
#include "string_cast.hpp"
#include "Sphere.hpp"
#include "LightSource.hpp"
#include "Camera.hpp"
#include <iostream>
#include <string>
#ifndef scene_H
#define scene_H

namespace csc305{
    class Scene{
    public:

      //Default Constructor
      Scene();

      // Main Constructor
      Scene(Camera camera, Sphere* spheres, int numSpheres, LightSource* lightSources, int numLights, glm::vec3 backgroundColor, glm::vec3 ambientIntensity, std::string output);

      //Move Constructor
      Scene(Scene && other);

      //Move Operator
      Scene & operator=(Scene && other);

      //Copy Constructor
      Scene(const Scene & other);

      //Copy Operator
      Scene & operator=(const Scene & other);

      //Deconstructor
      ~Scene();

      void printScene(){
        std::string output = "Camera: \n    NEAR: ";
        output = output + std::to_string(camera_.getNearPlane());
        output = output + "\n    LEFT: ";
        output = output + std::to_string(camera_.getLeftCorner());
        output = output + "\n    RIGHT: ";
        output = output + std::to_string(camera_.getRightCorner());
        output = output + "\n    TOP: ";
        output = output + std::to_string(camera_.getTop());
        output = output + "\n    BOT: ";
        output = output + std::to_string(camera_.getBot());
        output = output + "\n    COL: ";
        output = output + std::to_string(camera_.getNColumns());
        output = output + "\n    ROW: ";
        output = output + std::to_string(camera_.getNRows());

        output = output + "\nSphere: \n";
        for(int i =0; i < numSpheres_; i++){
            output = output + "\n    " + spheres_[i].getName() + " :";
            output = output + "\n         Pos: " + glm::to_string(spheres_[i].getPos());
            output = output + "\n         Scale: " + glm::to_string(spheres_[i].getScale());
            output = output + "\n         Color: " + glm::to_string(spheres_[i].getColor());
            output = output + "\n         Ka: " + std::to_string(spheres_[i].getKa());
            output = output + "\n         Kd: " + std::to_string(spheres_[i].getKd());
            output = output + "\n         Ks: " + std::to_string(spheres_[i].getKs());
            output = output + "\n         Kr: " + std::to_string(spheres_[i].getKr());
            output = output + "\n         SpecExp: " + std::to_string(spheres_[i].getSpecExp());
        }

        output = output + "\nLight: \n";
        for(int i =0; i < numLights_; i++){
            output = output + "\n    " + lightSources_[i].getName() + " :";
            output = output + "\n         Pos: " + glm::to_string(lightSources_[i].getPos());
            output = output + "\n         Intensity: " + glm::to_string(lightSources_[i].getIntensity());
        }

        output = output + "\nBackground: " + glm::to_string(backgroundColor_);
        output = output + "\nAmbient Intensity: " + glm::to_string(ambientIntensity_);
        output = output + "\nOutput file: " + output_;
        std::cout << output;
      }

    private:
      // Attributes
      Camera camera_;
      Sphere* spheres_;
      int numSpheres_;
      LightSource* lightSources_;
      int numLights_;
      glm::vec3 backgroundColor_;
      glm::vec3 ambientIntensity_;
      std::string output_;
    };
}

#endif
