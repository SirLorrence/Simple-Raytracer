#include <cmath>
#include <iostream>

int main(){
  // image size in pixels (using c20)
  constexpr int height = 512;
  constexpr int width = height; // 1x1 size
  
  std::cout<<"P3\n" << height << 'x' << width << "\n255\n";
  
  for(int y = 0; y < height; ++y){
    for(int x = 0; x < width; ++x){
      // want to be specific on how i cast things
      double r = static_cast<double>(x)/(width - 1);
      double g = static_cast<double>(y)/(height - 1);
      double b = 0.0;
      
      double scaler = 255.999; // multiplier/max colour
      
      int whole_r = static_cast<int>(scaler * r);
      int whole_g = static_cast<int>(scaler * g);
      int whole_b = static_cast<int>(scaler * b); //will always be 0
      
      std::cout<< whole_r << ' ' << whole_g << ' ' << whole_b << '\n';
    }
  }
}