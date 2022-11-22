#include "InputParser.hpp"
#include "Scene.hpp"
#include <iostream>

int main(int argc, char *argv[]){

  csc305::InputParser parse(argv[1]);

  csc305::Scene scene = parse.getScene();
  scene.printScene();
  return 0;
}
