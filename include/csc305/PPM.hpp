#include <stdio.h>

#ifndef ppm_h
#define ppm_h
namespace csc305{
    class PPM{
    public:

      //Default Constructor
      PPM();

      //Main Constructor
      PPM(int width, int height, unsigned char* pixels);

      //Move Constructor
      PPM(PPM && other);

      //Move Operator
      PPM & operator=(PPM && other);

      //Copy Constructor
      PPM(const PPM & other);

      //Copy Operator
      PPM & operator=(const PPM & other);

      //Deconstructor
      ~PPM();

      //Save Image
      // Modified From Given Code
      void save_imageP3(char* fname);

    private:
      //Attributes
      int height_;
      int width_;
      unsigned char* pixels_;
    };
}
#endif
