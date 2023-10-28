# Ray Tracer

Ray Tracer done in C++. This project is to learning about how Raytracing works. 


## Features

* Implementation of all features included in [Peter Shirley's Ray Tracing In One Weekend](https://github.com/RayTracing/raytracing.github.io/blob/master/books/RayTracingInOneWeekend.html)
  * Spheres
  * Surface Normals
  * Antialiasing
  * Diffuse Materials
  * Metal
  * Dielectrics
  * Positionable Camera
  * Defocus Blur (“depth of field”)
- PNG image output  



## Installation

This program has been tested on Pop OS and MacOS but should work under any system that has cmake and a C++ compiler installed.

Once project files are download and you are currently in the project directory, you can generate the Makefile using the following command:

```
mkdir build
cd build/
cmake ..
```
Now you can build the binary by running:

```
make
```

## Roadmap
- Project Refactoring
- CPU/GPU multi-threading to speed up rending
- SDL Project conversion
- Runtime Rendering (being able to move the camera in a graphics window)



## Authors
- Laurence Sadler - [SirLorrence](https://gitlab.com/SirLorrence)

## License
This code is released under the [MIT License](https://gitlab.com/SirLorrence/raytracer/-/blob/main/LICENSE).

## Project status

### In Development

## Built with
- [Tiny PNG Output](https://www.nayuki.io/page/tiny-png-output) - to write PNG file

## References
- [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- [An Overview of the Ray-Tracing Rendering Technique
](https://scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/ray-tracing-rendering-technique-overview.html)
- [3D Math Primer for Graphics and Game Development.](https://gamemath.com/) - Digitial and Physical 
- [ChatGPT](chat.openai.com) - How to create a CMake file and cryptic compiler errors
- [Adobe | What is a PPM file?](https://www.adobe.com/creativecloud/file-types/image/raster/ppm-file.html)

