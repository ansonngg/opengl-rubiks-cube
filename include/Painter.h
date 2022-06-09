#ifndef PAINTER_H
#define PAINTER_H

#include "Controller.h"
#include "RubiksCube.h"

class Painter {
public:
    Controller::Keyboard keyboardCtrl;

    Painter(int width, int height);
    void Initialize();
    void Loop();

private:
    const int SCR_WIDTH, SCR_HEIGHT;

    glm::vec3 eye, center;
    Shader shader;
    RubiksCube rubiksCube;

    void ProcessInput();
};

#endif // PAINTER_H
