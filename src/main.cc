#include "../include/color.h"
#include "../include/vec3.h"

#include <iostream>


int main(){
  // image size in pixels (using c20)
  constexpr int height = 256;
  constexpr int width = height; // 1x1 size
  
  std::cout<<"P3\n" << height << 'x' << width << "\n255\n";
  
  for(int y = 0; y < height; ++y){
    //logging the  progress
    std::clog <<"\r Lines Remaining:" << (height - y) << ' ' << std::flush;
    for(int x = 0; x < width; ++x){
      double r = double(x)/width - 1;
      double g = double(y)/height - 1;
      vec3 pixel_color = color(r,g,0);
      write_color(std::cout, pixel_color);
      
      
//      // want to be specific on how i cast things
//      double r = static_cast<double>(x)/(width - 1);
//      double g = static_cast<double>(y)/(height - 1);
//      double b = 0.0;
//
//      double scaler = 255.999; // multiplier/max colour
//
//      int whole_r = static_cast<int>(scaler * r);
//      int whole_g = static_cast<int>(scaler * g);
//      int whole_b = static_cast<int>(scaler * b); //will always be 0
//
//      std::cout<< whole_r << ' ' << whole_g << ' ' << whole_b << '\n';
    }
  }
  std::clog << "\r Done. \n";
}