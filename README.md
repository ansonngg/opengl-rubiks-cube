# OpenGL Rubik's Cube
This is an application that renders a Rubik's cube and allows users to play around. The project is written in C++ and built using CMake. It is basically a practice of using OpenGL and understanding the procedure of rendering computer graphics, as well as writing structured code in C++.

## Dependencies
* GLFW 3.3.7
* GLAD
    * [Webservice](https://glad.dav1d.de/)
    * Language: C/C++
    * Specification: OpenGL
    * gl: Version 4.6
    * Profile: Core
    * Generate a loader
* GLM 0.9.9.8
* stb_image.h

## Project Building
1. Download or build the binaries of GLFW. 
2. Download the source code of the other dependencies. (For the detail of generating GLAD source code, read the section of [Dependencies](#Dependencies).)
    1. (GLAD) Copy the folders `glad` and `KHR` into `include`, copy `glad.c` into `src`.
    2. (GLM) Copy the folder `glm` (the one directly containing the headers of GLM) into `include`.
    3. (stb_image.h) Simply copy this file into `include`.
3. Build the project using CMake. Make sure you have specified `glfw3_DIR` as the path of `glfw3Config.cmake` (it is in `./GLFW/lib/cmake/glfw3` by default). You may add it together with the path of `glfw3.dll` into the PATH environment variable as well for easier compiling.
4. Enjoy the project!

## Key Binding
The key binding basically follows the popular notation developed by David Singmaster. To rotate a side anticlockwise, hold <kbd>'</kbd>. To rotate two layers at once, hold <kbd>Shift</kbd>.
