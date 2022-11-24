#include "InputParser.hpp"

namespace csc305{
  //Public

  //default Constructor
  InputParser::InputParser(){
    scene_ = Scene();
  }

  //main Constructor
  InputParser::InputParser(std::string inputfilename){
    scene_ = parseFile(inputfilename);
  }

  //Get Scene
  Scene InputParser::getScene(){
    return scene_;
  }

  //Deconstructor
  InputParser::~InputParser() = default;

  //Private

  //Parse new file
  Scene InputParser::parseFile(std::string inputfilename){
    std::fstream fs(inputfilename);
    std::string line;

    Camera cam;
    Sphere* spheres = new Sphere[30];
    LightSource* lights = new LightSource[30];
    int numSpheres = 0;
    int numLights = 0;
    glm::vec3 BG(0,0,0);
    glm::vec3 AM(0,0,0);
    std::string name;

    while(std::getline(fs, line)){
      if(line == ""){
        continue;
      }
      std::regex e("\\s+");
      line = std::regex_replace(line, e, " ");
      std::istringstream line_stream(line);
      std::string current;
      std::getline(line_stream, current, ' ');

      if(current == "NEAR"){
        std::getline(line_stream, current, ' ');
        cam.setNearPlane(std::stof(current));
      }
      else if(current == "LEFT"){
        std::getline(line_stream, current, ' ');
        cam.setLeftCorner(std::stof(current));
      }
      else if(current == "RIGHT"){
        std::getline(line_stream, current, ' ');
        cam.setRightCorner(std::stof(current));
      }

      else if(current == "BOTTOM"){
        std::getline(line_stream, current, ' ');
        cam.setBot(std::stof(current));
      }
      else if(current == "TOP"){
        std::getline(line_stream, current, ' ');
        cam.setTop(std::stof(current));
      }
      else if(current == "RES"){
        std::getline(line_stream, current, ' ');
        int x = std::stoi(current);
        cam.setNColumns(x);

        std::getline(line_stream, current, ' ');
        int y = std::stoi(current);
        cam.setNRows(y);
      }
      else if(current == "SPHERE"){
        Sphere sphere;
        std::getline(line_stream, current, ' ');
        sphere.setName(current);

        std::getline(line_stream, current, ' ');
        float p_x = std::stof(current);

        std::getline(line_stream, current, ' ');
        float p_y = std::stof(current);

        std::getline(line_stream, current, ' ');
        float p_z = std::stof(current);
        sphere.setPos(glm::vec3(p_x, p_y, p_z));

        std::getline(line_stream, current, ' ');
        float s_x = std::stof(current);

        std::getline(line_stream, current, ' ');
        float s_y = std::stof(current);

        std::getline(line_stream, current, ' ');
        float s_z = std::stof(current);
        sphere.setScale(glm::vec3(s_x, s_y, s_z));

        std::getline(line_stream, current, ' ');
        float c_r = std::stof(current);

        std::getline(line_stream, current, ' ');
        float c_g = std::stof(current);

        std::getline(line_stream, current, ' ');
        float c_b = std::stof(current);
        sphere.setColor(glm::vec3(c_r, c_g, c_b));

        std::getline(line_stream, current, ' ');
        sphere.setKa(std::stof(current));

        std::getline(line_stream, current, ' ');
        sphere.setKd(std::stof(current));

        std::getline(line_stream, current, ' ');
        sphere.setKs(std::stof(current));

        std::getline(line_stream, current, ' ');
        sphere.setKr(std::stof(current));

        std::getline(line_stream, current, ' ');
        sphere.setSpecExp(std::stoi(current));

        spheres[numSpheres] = sphere;
        ++numSpheres;
      }
      else if( current == "LIGHT"){
        LightSource light;
        std::getline(line_stream, current, ' ');
        light.setName(current);

        std::getline(line_stream, current, ' ');
        float p_x = std::stof(current);

        std::getline(line_stream, current, ' ');
        float p_y = std::stof(current);

        std::getline(line_stream, current, ' ');
        float p_z = std::stof(current);
        light.setPos(glm::vec3(p_x, p_y, p_z));

        std::getline(line_stream, current, ' ');
        float i_r = std::stof(current);

        std::getline(line_stream, current, ' ');
        float i_g = std::stof(current);

        std::getline(line_stream, current, ' ');
        float i_b = std::stof(current);
        light.setIntensity(glm::vec3(i_r, i_g, i_b));

        lights[numLights] = light;
        ++numLights;
      }
      else if (current == "BACK"){
        std::getline(line_stream, current, ' ');
        float c_r = std::stof(current);

        std::getline(line_stream, current, ' ');
        float c_g = std::stof(current);

        std::getline(line_stream, current, ' ');
        float c_b = std::stof(current);

        BG = glm::vec3(c_r, c_g, c_b);
      }
      else if (current == "AMBIENT"){
        std::getline(line_stream, current, ' ');
        float c_r = std::stof(current);

        std::getline(line_stream, current, ' ');
        float c_g = std::stof(current);

        std::getline(line_stream, current, ' ');
        float c_b = std::stof(current);

        AM = glm::vec3(c_r, c_g, c_b);
      }
      else if(current == "OUTPUT"){
        std::getline(line_stream, current, ' ');
        name = current;
      }
      else{
        std::cout << "Invalid Input Upon Parsing input file: ";
        std::cout << current;
      }
    }
    return Scene(cam, spheres, numSpheres, lights, numLights, BG, AM, name);
  }
}
