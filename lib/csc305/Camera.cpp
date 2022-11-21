#include "Camera.hpp"

namespace csc305{
  //Public

  // Default Constructor
  Camera::Camera(){
    nearPlane_ = 1;
    leftCorner_ = 1;
    rightCorner_ = 1;
    top_ = 1;
    bot_ = 1;
    nColumns_ = 1;
    nRows_ = 1;
  }

  //main Constructor
  Camera::Camera(float nearPlane, float leftCorner, float rightCorner, float top, float bottom, int nColumns, int nRows){
    nearPlane_ = nearPlane;
    leftCorner_ = leftCorner;
    rightCorner_ = rightCorner;
    top_ = top;
    bot_ = bottom;
    nColumns_ = nColumns;
    nRows_ = nRows;
  }

  //Move Constructor
  Camera::Camera(Camera && other) = default;

  //Move Operator
  Camera::Camera & operator=(Camera && other) = default;

  //Copy Constructor
  Camera::Camera(const Camera &) = default;

  //Copy Operator
  Camera::Camera & operator=(const Camera &) = default;

  //Deconstructor
  Camera::~Camera() = default;


  //Private
}
