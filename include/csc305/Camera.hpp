#include "glm.hpp"
#ifndef camera_H
#define camera_H

namespace csc305{
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

      //setters
      void setNearPlane(float nearPlane){
        nearPlane_ = nearPlane;
      }

      void setLeftCorner(float leftCorner){
        leftCorner_ = leftCorner;
      }

      void setRightCorner(float rightCorner){
        rightCorner_ = rightCorner;
      }

      void setTop(float top){
        top_ = top;
      }

      void setBot(float bot){
        bot_ = bot;
      }

      void setNColumns(int nColumns){
        nColumns_ = nColumns;
      }

      void setNRows(int nRows){
        nRows_ = nRows;
      }

      //getter
      float getNearPlane(){
        return nearPlane_;
      }

      float getLeftCorner(){
        return leftCorner_;
      }

      float getRightCorner(){
        return rightCorner_;
      }

      float getTop(){
        return top_;
      }

      float getBot(){
        return bot_;
      }

      int getNColumns(){
        return nColumns_;
      }

      int getNRows(){
        return nRows_;
      }


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
