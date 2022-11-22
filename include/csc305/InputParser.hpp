#include "glm.hpp"
#include "Scene.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#ifndef InputParser_H
#define InputParser_H

namespace csc305{
    class InputParser{
    public:

      //default Constructor
      InputParser();

      // Main Constructor
      InputParser(std::string inputfilename);

      //Get Scene
      Scene getScene();

      //Deconstructor
      ~InputParser();

    private:
      //Attributes
      Scene scene_;

      //Parse new file
      Scene parseFile(std::string inputfilename);

    };
}

#endif
