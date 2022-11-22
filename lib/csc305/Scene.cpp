#include "Scene.hpp"

namespace csc305{
  //Public

  // Default Constructor
  Scene::Scene(){
    camera_ = Camera();
    spheres_ = nullptr;
    numSpheres_ = 0;
    lightSources_ = nullptr;
    numLights_ = 0;
    backgroundColor_ = glm::vec3(0,0,0);
    ambientIntensity_ = glm::vec3(0,0,0);
    output_ = "output.ppm";
  }

  //main Constructor
  Scene::Scene(Camera camera, Sphere* spheres, int numSpheres, LightSource* lightSources, int numLights, glm::vec3 backgroundColor, glm::vec3 ambientIntensity, std::string output){
    camera_ = camera;

    spheres_ = new Sphere[numSpheres];
    for(int i = 0; i < numSpheres; i++){
      spheres_[i] = spheres[i];
    }

    numSpheres_ = numSpheres;

    lightSources_ = new LightSource[numLights];
    for(int i = 0; i < numLights; i++){
      lightSources_[i] = lightSources[i];
    }

    numLights_ = numLights;
    backgroundColor_ = backgroundColor;
    ambientIntensity_ = ambientIntensity;
    output_ = output;
  }

  //Move Constructor
  Scene::Scene(Scene && other){
    delete [] spheres_;
    delete [] lightSources_;

    spheres_ = other.spheres_;
    other.spheres_ = nullptr;
    numSpheres_ = other.numSpheres_;

    lightSources_ = other.lightSources_;
    other.lightSources_  = nullptr;
    numLights_ = other.numLights_;

    camera_ = other.camera_;
    backgroundColor_ = other.backgroundColor_;
    ambientIntensity_ = other.ambientIntensity_;
    output_ = other.output_;
  }

  //Move Operator
  Scene & Scene::operator=(Scene && other){
    delete [] spheres_;
    delete [] lightSources_;

    spheres_ = other.spheres_;
    other.spheres_ = nullptr;
    numSpheres_ = other.numSpheres_;

    lightSources_ = other.lightSources_;
    other.lightSources_  = nullptr;
    numLights_ = other.numLights_;

    camera_ = other.camera_;
    backgroundColor_ = other.backgroundColor_;
    ambientIntensity_ = other.ambientIntensity_;
    output_ = other.output_;
    return *this;
  }

  //Copy Constructor
  Scene::Scene(const Scene & other){
    camera_ = other.camera_;
    backgroundColor_ = other.backgroundColor_;
    ambientIntensity_ = other.ambientIntensity_;
    output_ = other.output_;
    numLights_ = other.numLights_;
    numSpheres_ = other.numSpheres_;

    spheres_ = new Sphere[numSpheres_];
    lightSources_ = new LightSource[numLights_];

    for(int i = 0; i < numSpheres_; i++){
      spheres_[i] = other.spheres_[i];
    }
    for(int i = 0; i < numLights_; i++){
      lightSources_[i] = other.lightSources_[i];
    }
  }

  //Copy Operator
  Scene & Scene::operator=(const Scene & other){
    camera_ = other.camera_;
    backgroundColor_ = other.backgroundColor_;
    ambientIntensity_ = other.ambientIntensity_;
    output_ = other.output_;
    numLights_ = other.numLights_;
    numSpheres_ = other.numSpheres_;

    spheres_ = new Sphere[numSpheres_];
    lightSources_ = new LightSource[numLights_];

    for(int i = 0; i < numSpheres_; i++){
      spheres_[i] = other.spheres_[i];
    }
    for(int i = 0; i < numLights_; i++){
      lightSources_[i] = other.lightSources_[i];
    }
    return *this;
  }

  //Deconstructor
  Scene::~Scene(){
    delete [] spheres_;
    delete [] lightSources_;
  }


  //Private
}
