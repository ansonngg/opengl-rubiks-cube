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
    const std::vector<int> LAYERS_INDICES[15];

    glm::vec3 eye, center;
    float rotateTime;
    GLuint vao, vbo, ebo;
    Shader shader;
    Texture textures[27];
    glm::mat4 transMatrices[27];
    glm::mat4 tempTransMatrices[27];
    int cubeIndices[27];
    bool rotating;

    enum class Move {
        F, B, U, D, L, R, M, E, S, F2, B2, U2, D2, L2, R2,
        FP, BP, UP, DP, LP, RP, MP, EP, SP, F2P, B2P, U2P, D2P, L2P, R2P
    };

    void Model();
    void ProcessInput();
    bool RotateCube(float angle, glm::vec3 axis);
    bool MoveLayer(Move move);
    void RotateOnX(int *arr);
    void RotateOnY(int *arr);
    void RotateOnZ(int *arr);
    void RotateOnXP(int *arr);
    void RotateOnYP(int *arr);
    void RotateOnZP(int *arr);
    void RoundMat4(glm::mat4 &matrix);
};

#endif // PAINTER_H
