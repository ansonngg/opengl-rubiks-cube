#ifndef PAINTER_H
#define PAINTER_H

#include <vector>

#include "Controller.h"
#include "Shader.h"
#include "Texture.h"

class Painter {
public:
    Controller::Keyboard keyboardCtrl;

    Painter(int width, int height);
    void Initialize();
    void Loop();

private:
    const int SCR_WIDTH, SCR_HEIGHT;
    const std::vector<int> LAYERS_INDICES[1];

    glm::vec3 eye, center;
    float rotateTime;
    GLuint vao, vbo, ebo;
    Shader shader;
    Texture textures[27];
    glm::mat4 transMatrices[27];
    glm::mat4 tempTransMatrices[27];
    int cubeIndices[27];
    bool rotating;
    float lastFrame;

    enum class Rotate {
        X, Y, Z, XP, YP, ZP
    };

    enum class Move {
        F, B, U, D, L, R, M, E, S
    };

    void Model();
    void ProcessInput();
    bool RotateCube(float angle, glm::vec3 axis);
    bool MoveLayer(Move move);
    void RotateOnX(int *arr);
    void RotateOnZ(int *arr);
    void RoundMat4(glm::mat4 &matrix);
};

#endif // PAINTER_H
