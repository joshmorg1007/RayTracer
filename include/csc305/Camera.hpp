#include "glm.hpp"
#ifndef camera_H
#define camera_H

namespace seng305{
    class Camera{
    public:

      // Default Constructor
      Camera();

      // Main Constructor
      Camera(float nearPlane, float leftCorner, float rightCorner, float top, float bottom, int nColumns, int nRows);

      //Move Constructor
      Camera(Camera && other);

      //Move Operator
      Camera & operator=(Camera && other);

      //Copy Constructor
      Camera(const Camera &);

      //Copy Operator
      Camera & operator=(const Camera &);

      //Deconstructor
      ~Camera();

    private:
      // Attributes
      float nearPlane_;
      float leftCorner_;
      float rightCorner_;
      float top_;
      float bot_;
      int nColumns_;
      int nRows_;
    };
}

#endif
