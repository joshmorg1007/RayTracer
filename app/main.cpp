#include "InputParser.hpp"
#include "Scene.hpp"
#include "RayTracer.hpp"
#include <iostream>

int main(int argc, char *argv[]){

  csc305::InputParser parse(argv[1]);

  csc305::Scene scene = parse.getScene();
  scene.printScene();
  csc305::RayTracer rayTracer(scene);
  rayTracer.rayTraceScene();
  rayTracer.saveImage();
  return 0;
}
