#include "RayTracer.hpp"

namespace csc305{
  //public

  //Default Constructor
  RayTracer::RayTracer(){
    scene_ = Scene();
    ppm_ = PPM();
  }

  //Main Constructor
  RayTracer::RayTracer(Scene scene){
    scene_ = scene;
    ppm_ = PPM();
  }

  //Move Constructor
  RayTracer::RayTracer(RayTracer && other) = default;

  //Move Operator
  RayTracer & RayTracer::operator=(RayTracer && other) = default;

  //Copy Constructor
  RayTracer::RayTracer(const RayTracer &) = default;

  //Copy Operator
  RayTracer & RayTracer::operator=(const RayTracer &) = default;

  //Deconstructor
  RayTracer::~RayTracer() = default;

  //RayTrace Scene
  void RayTracer::rayTraceScene(){
    int width = scene_.getCamera().getNColumns();
    int height = scene_.getCamera().getNRows();
    glm::vec3* pixels = new glm::vec3 [width*height];

    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
        Ray ray = eyeToPixelRay(j, i, width, height);
        glm::vec3 color = raytrace(ray, 1);
        pixels[i*width + j] = color;
      }
    }

    ppm_ = PPM(width, height, pixels);
  }

  // save image
  void RayTracer::saveImage(){
    ppm_.save_imageP3(scene_.getOutput().c_str());
  }

  //private

  // Recursive raytrace helper function
  glm::vec3 RayTracer::raytrace(Ray ray, int depth){
    const int maxDepth = 3;
    if(depth > maxDepth){
      return glm::vec3(0,0,0);
    }

    float minT = std::numeric_limits<float>::max();
    int minSphereIndex = -1;
    Ray candidateInvertedRay;
    for(int i = 0; i < scene_.getNumSpheres(); i++){
      Sphere current = scene_.getSphere(i);
      if(ray.getStartingName() == current.getName()){
        continue;
      }
      Ray invertedRay = ray.getInvertedRay(current.getInverseTransform());

      if(!checkValidSolution(invertedRay)){
        continue;
      }

      float intersection_time = solveIntersection(invertedRay);
      if(intersection_time < minT){
        minT = intersection_time;
        minSphereIndex = i;
        candidateInvertedRay = invertedRay;
      }
    }

    // no intersections return background color
    if(minSphereIndex == -1 && depth == 1){
      return scene_.getBackgroundColor();
    }
    else if (minSphereIndex == -1 && depth >= 1){
      return glm::vec3(0,0,0);
    }

    glm::vec3 collision_point = ray.getRayPos(minT);
    Sphere intersectedSphere = scene_.getSphere(minSphereIndex);
    glm::mat4 inverseTranspose = intersectedSphere.getInverseTransposeTransform();
    glm::vec3 normal = candidateInvertedRay.getRayPos(minT);
    glm::vec4 normalExtended = glm::vec4(normal.x, normal.y, normal.z, 0);

    glm::vec4 inverseTransposeNormalExtended = inverseTranspose * normalExtended;
    glm::vec3 sphereNormal = glm::vec3(inverseTransposeNormalExtended.x, inverseTransposeNormalExtended.y, inverseTransposeNormalExtended.z);
    glm::vec3 sphereUnitNormal = glm::normalize(sphereNormal);

    //local lighting equation
    glm::vec3 sphereColor = intersectedSphere.getColor();
    glm::vec3 sceneAmbient = scene_.getAmbient();
    glm::vec3 clocal(0,0,0);
    if(intersectedSphere.getKa() != 0.0){
      clocal = sceneAmbient*intersectedSphere.getKa()*sphereColor;
    }


    // iterate through all lights
    for(int i = 0; i < scene_.getNumLights(); i++){
      LightSource currentLight = scene_.getLight(i);
      glm::vec3 pos = currentLight.getPos();
      Ray newRay(collision_point, glm::normalize(pos - collision_point));

      //for lighting equattions
      glm::vec3 L = glm::normalize(pos - collision_point);
      glm::vec3 V = glm::normalize(-collision_point);
      glm::vec3 R = glm::reflect(-L, sphereUnitNormal);

      glm::vec3 intensity = currentLight.getIntensity();

      //logic to check if intersections ray is blocked by another object
      bool isBlocked = false;
      for(int j = 0; j < scene_.getNumSpheres(); j++){
        Sphere currentSphere = scene_.getSphere(j);
        Ray invertedRay = newRay.getInvertedRay(currentSphere.getInverseTransform());
        if(checkValidSolution(invertedRay)){
          float T = solveIntersection(invertedRay);
          if(T <= -0.0001){
            continue;
          }
          isBlocked = true;
          break;
        }
      }
      if(!isBlocked){
        float temp = glm::dot(R, V);
        if(temp < 0.0){
          temp = glm::dot(-R, V);
        }
        glm::vec3 spec(0,0,0);
        if(intersectedSphere.getKs() != 0.0){
          spec = intersectedSphere.getKs()*currentLight.getIntensity();
          spec *= std::powf(temp, (float)intersectedSphere.getSpecExp());
        }

        float  normalDotLight = glm::dot(sphereUnitNormal, L);

        glm::vec3 diffuse = intensity*normalDotLight*sphereColor*intersectedSphere.getKd();

        glm::vec3 pointLightContribution =  spec + diffuse;
        clocal += pointLightContribution;
      }
    }
    clocal = glm::clamp(clocal, glm::vec3(0,0,0), glm::vec3(1,1,1));
    if(intersectedSphere.getKr() != 0.0 && collision_point.y > 0.1){
      glm::vec3 reflectedDir = glm::reflect(ray.getDir() , sphereUnitNormal);
      Ray reflected(collision_point ,reflectedDir);
      reflected.setStartingName(intersectedSphere.getName());
      glm::vec3 reflectedContribution = raytrace(reflected, depth+1);
      return clocal + reflectedContribution * intersectedSphere.getKr();
    }
    else{
      return clocal;
    }

  }

  Ray RayTracer::eyeToPixelRay(int c, int r, int nCols, int nRows){
    float H = scene_.getCamera().getTop();
    float W = scene_.getCamera().getRightCorner();
    float N = scene_.getCamera().getNearPlane();

    glm::vec3 eye(0,0,0); //might need to change this.

    glm::vec3 dir(W*((2.0*c/nCols)-1.0), H*((2.0*r/nRows)-1.0), -N);

    float x = -N/dir.z;
    return Ray(eye + dir*x, glm::normalize(dir)); // removed normalize
  }

  bool RayTracer::checkValidSolution(Ray ray){
    glm::vec3 start = ray.getStart();
    glm::vec3 dir = ray.getDir();

    float B = glm::dot(start,dir);
    float B2 = B * B;
    float A = glm::dot(dir, dir);
    float C = (glm::dot(start, start) - 1);

    float t1 = -B/(A) + std::sqrt(B2 - A*C)/(A);
    float t2 = -B/(A) - std::sqrt(B2 - A*C)/(A);

    if(t1 < 0.0 && t2 < 0.0){
      return false;
    }
    return (B2 - A*C > 0);
  }

  float RayTracer::solveIntersection(Ray ray){
    glm::vec3 start = ray.getStart();
    glm::vec3 dir = ray.getDir();

    float B = glm::dot(start,dir);
    float B2 = B * B;
    float A = glm::dot(dir, dir);
    float C = (glm::dot(start, start) - 1);

    float t1 = -B/(A) + std::sqrt(B2 - A*C)/(A);
    float t2 = -B/(A) - std::sqrt(B2 - A*C)/(A);

    if(t1 < t2){
      return t1;
    }
    else{
      return t2;
    }
  }


}
