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
    unsigned char* pixels = new unsigned char [width*height*3];

    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j += 3){
        Ray ray = eyeToPixelRay(j, i, width, height);
        glm::vec3 color = raytrace(ray, 1);
        pixels[i*width + j] = (unsigned char)color.x*256;
        pixels[i*width + j + 1] = (unsigned char)color.y*256;
        pixels[i*width + j + 2] = (unsigned char)color.z*256;
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
    const int maxDepth = 3; // might need to change to 3
    if(depth > maxDepth){
      return glm::vec3(0,0,0);
    }

    float minT = std::numeric_limits<float>::max();
    int minSphereIndex = -1;
    for(int i = 0; i < scene_.getNumSpheres(); i++){
      Sphere current = scene_.getSphere(i);
      Ray invertedRay = ray.getInvertedRay(current.getInverseTransform());

      if(!checkValidSolution(invertedRay)){
        continue;
      }

      float intersection_time = solveIntersection(invertedRay);
      if(intersection_time < minT){
        minT = intersection_time;
        minSphereIndex = i;
      }
    }

    // no intersections return background color
    if(minSphereIndex == -1){
      return scene_.getBackgroundColor();
    }

    glm::vec3 interection_point = ray.getRayPos(minT);
    Sphere intersectedSphere = scene_.getSphere(minSphereIndex);
    glm::vec3 sphereNormal(interection_point.x - intersectedSphere.getPos().x,  interection_point.y - intersectedSphere.getPos().y,interection_point.z - intersectedSphere.getPos().z);
    glm::vec3 sphereUnitNormal = sphereNormal/(sphereNormal*sphereNormal);

    //local lighting equation
    glm::vec3 sphereColor = intersectedSphere.getColor();
    glm::vec3 sceneAmbient = scene_.getAmbient();
    glm::vec3 clocal = sceneAmbient*intersectedSphere.getKa()*sphereColor;

    // iterate through all lights

    for(int i = 0; i < scene_.getNumLights(); i++){
      LightSource currentLight = scene_.getLight(i);
      glm::vec3 pos = currentLight.getPos();
      Ray newRay(interection_point, pos - interection_point);

      //for lighting equattions
      glm::vec3 L = glm::normalize(pos - interection_point);
      glm::vec3 V = glm::normalize(-interection_point);
      glm::vec3 R = glm::reflect(-L, sphereUnitNormal);

      bool isBlocked = false;
      for(int j = 0; j < scene_.getNumSpheres(); j++){
        Sphere currentSphere = scene_.getSphere(i);
        Ray invertedRay = newRay.getInvertedRay(currentSphere.getInverseTransform());
        if(checkValidSolution(invertedRay)){
          isBlocked = true;
          break;
        }
      }
      if(!isBlocked){
        float temp =glm::dot(R, V);
        float temp2 = glm::dot(sphereUnitNormal,L);
        glm::vec3 diffuse = intersectedSphere.getKd()*currentLight.getIntensity()*(temp2)*sphereColor;
        glm::vec3 spec = intersectedSphere.getKs()*currentLight.getIntensity();
        spec *= std::pow(temp, intersectedSphere.getSpecExp());
        glm::vec3 pointLightContribution =  diffuse + spec;
        clocal += pointLightContribution;
      }
    }
    //need to apply reflected
    //don't need to do refraction
    glm::vec3 reflectedDir = glm::reflect(ray.getDir(), sphereUnitNormal);
    Ray reflected(interection_point ,reflectedDir);
    glm::vec3 reflectedContribution = raytrace(reflected, depth+1);


    return clocal + reflectedContribution * intersectedSphere.getKr();
  }

  Ray RayTracer::eyeToPixelRay(int c, int r, int nCols, int nRows){
    float H = scene_.getCamera().getTop();
    float W = scene_.getCamera().getBot();
    float N = scene_.getCamera().getNearPlane();

    glm::vec3 eye(0,0,0); //might need to change this.

    float uc = -W + W*(2*c/nCols);
    float ur = -H + H*(2*r/nRows);

    glm::vec3 dir(-N, W*((2*c/nCols)-1), H*((2*r/nRows)-1));

    return Ray(eye, dir);
  }

  bool RayTracer::checkValidSolution(Ray ray){
    glm::vec3 start = ray.getStart();
    glm::vec3 dir = ray.getDir();

    float B2 = (glm::dot(start,dir)) * (glm::dot(start,dir));
    float A = glm::dot(dir, dir);
    float C = (glm::dot(start, start) - 1);
    return (B2 - A*C > 0);
  }

  float RayTracer::solveIntersection(Ray ray){
    glm::vec3 start = ray.getStart();
    glm::vec3 dir = ray.getDir();

    float B = glm::dot(start,dir);
    float B2 = B * B;
    float A = glm::dot(dir, dir);
    float C = (glm::dot(start, start) - 1);

    float t1 = -B/A + std::sqrt(B2 - A*C)/A;
    float t2 = -B/A + std::sqrt(B2 - A*C)/A;

    if(t1 < t2){
      return t1;
    }
    else{
      return t2;
    }
  }


}
