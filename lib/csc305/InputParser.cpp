#include "InputParser.hpp"

namespace csc305{
  //Public


  //main Constructor
  InputParser::InputParser(std::string inputfilename){
    Scene scene_ = parseFile(inputfilename);
  }

  //Get Scene
  Scene getScene();

  //Deconstructor
  InputParser::~InputParser() = default;

  //Private

  //Parse new file
  Scene parseFile(std::string inputfilename){
    std::fstream fs(inputfilename);
    std::string line;

    Camera cam;
    Sphere spheres = new Sphere[30];
    LightSource lights = new LightSource[30];
    int numSpheres = 0;
    int numLights = 0;
    glm::vec3 BG;
    glm::vec3 AM;
    std::string name;

    while(std::getline(fs, line)){
      std::istringstream line_stream(line);
      std::string current;
      std::getline(line_stream, current, ' ');
      cout << current;//Debug

      switch(current){
        case "NEAR":
          std::getline(line_stream, current, ' ');
          cam.setNearPlane(std::stof(current));
          break;
        case "LEFT":
          std::getline(line_stream, current, ' ');
          cam.setLeftCorner(std::stof(current));
          break;
        case "RIGHT":
          std::getline(line_stream, current, ' ');
          cam.setRightCorner(std::stof(current));
          break;
        case "BOTTOM":
          std::getline(line_stream, current, ' ');
          cam.setBot(std::stof(current));
          break;
        case "TOP":
          std::getline(line_stream, current, ' ');
          cam.setTop(std::stof(current));
          break;
        case "RES":
          std::getline(line_stream, current, ' ');
          int x = std::stoi(current);
          cam.setNColumns(x);

          std::getline(line_stream, current, ' ');
          int y = std::stoi(current);
          cam.setNRows(y);
          break;
        case "SPHERE":
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
          break;
        case "LIGHT":
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
          break;
        case "BACK":
          std::getline(line_stream, current, ' ');
          float c_r = std::stof(current);

          std::getline(line_stream, current, ' ');
          float c_g = std::stof(current);

          std::getline(line_stream, current, ' ');
          float c_b = std::stof(current);
          sphere.setColor(glm::vec3(c_r, c_g, c_b));

          BG = new glm::vec3(c_r, c_g, c_b);
          break;
        case "AMBIENT":
          std::getline(line_stream, current, ' ');
          float c_r = std::stof(current);

          std::getline(line_stream, current, ' ');
          float c_g = std::stof(current);

          std::getline(line_stream, current, ' ');
          float c_b = std::stof(current);
          sphere.setColor(glm::vec3(c_r, c_g, c_b));

          AM = new glm::vec3(c_r, c_g, c_b);
          break;
        case "OUTPUT":
          std::getline(line_stream, current, ' ');
          name = current;
          break;
        default:
          cout << "Invalid Input Upon Parsing input file: ";
          cout << first;
          break;
      }
    }
    return Scene(cam, spheres, numSpheres, lights, numLights, BG, AM, name);
  }
}
