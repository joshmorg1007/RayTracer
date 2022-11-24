#include "PPM.hpp"
namespace csc305{
  //Public

  //Default Constructor
  PPM::PPM(){
    pixels_ = nullptr;
    height_ = 0;
    width_ = 0;
  }

  // Main Constructor
  PPM::PPM(int width, int height, unsigned char* pixels){
    width_ = width;
    height_ = height;
    pixels_ = pixels;
  }

  //Move Constructor
  PPM::PPM(PPM && other){
    delete [] pixels_;
    pixels_ = other.pixels_;
    other.pixels_ = nullptr;
    height_ = other.height_;
    width_ = other.width_;
  }

  //Move Operator
  PPM & PPM::operator=(PPM && other){
    delete [] pixels_;
    pixels_ = other.pixels_;
    other.pixels_ = nullptr;
    height_ = other.height_;
    width_ = other.width_;
    return *this;
  }

  //Copy Constructor
  PPM::PPM(const PPM & other){
    delete [] pixels_;
    height_ = other.height_;
    width_ = other.height_;
    pixels_ = new unsigned char[height_ * width_ * 3];
    for(int i = 0; i < height_*width_*3; i++){
      pixels_[i] = other.pixels_[i];
    }
  }

  //Copy Operator
  PPM & PPM::operator=(const PPM & other){
    delete [] pixels_;
    height_ = other.height_;
    width_ = other.height_;
    pixels_ = new unsigned char[height_ * width_ * 3];
    for(int i = 0; i < height_*width_*3; i++){
      pixels_[i] = other.pixels_[i];
    }
    return *this;
  }

  void PPM::save_imageP3(const char* fname) {
    FILE *fp;
    const int maxVal=255;

    printf("Saving image %s: %d x %d\n", fname,width_,height_);
    fp = fopen(fname,"w");
    if (!fp) {
      printf("Unable to open file '%s'\n",fname);
      return;
    }
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", width_, height_);
    fprintf(fp, "%d\n", maxVal);

    int k = 0 ;
    for(int j = 0; j < height_; j++) {

      for( int i = 0 ; i < width_; i++)
      {
        fprintf(fp," %d %d %d", pixels_[k],pixels_[k+1],pixels_[k+2]) ;
        k = k + 3 ;
      }
      fprintf(fp,"\n") ;
    }
    fclose(fp);
  }

  //Deconstructor
  PPM::~PPM(){
    delete [] pixels_;
  }
}
