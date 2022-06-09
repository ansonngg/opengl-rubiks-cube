#include "RubiksCube.h"

#include <string>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

RubiksCube::RubiksCube(float rotateTime)
    : LAYERS_INDICES{
        { 2, 5, 8, 11, 14, 17, 20, 23, 26 },
        { 0, 3, 6, 9, 12, 15, 18, 21, 24 },
        { 6, 7, 8, 15, 16, 17, 24, 25, 26 },
        { 0, 1, 2, 9, 10, 11, 18, 19, 20 },
        { 0, 1, 2, 3, 4, 5, 6, 7, 8 },
        { 18, 19, 20, 21, 22, 23, 24, 25, 26 },
        { 9, 10, 11, 12, 13, 14, 15, 16, 17 },
        { 3, 4, 5, 12, 13, 14, 21, 22, 23 },
        { 1, 4, 7, 10, 13, 16, 19, 22, 25 },
        { 1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20, 22, 23, 25, 26 },
        { 0, 1, 3, 4, 6, 7, 9, 10, 12, 13, 15, 16, 18, 19, 21, 22, 24, 25 },
        { 3, 4, 5, 6, 7, 8, 12, 13, 14, 15, 16, 17, 21, 22, 23, 24, 25, 26 },
        { 0, 1, 2, 3, 4, 5, 9, 10, 11, 12, 13, 14, 18, 19, 20, 21, 22, 23 },
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 },
        { 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 }
    }
    , rotateTime(rotateTime)
    , rotating(false) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    for (int i = 0; i < 27; i++) {
        cubeIndices[i] = i;
        transMatrices[i] = glm::mat4(1.0f);
        tempTransMatrices[i] = transMatrices[i];
    }
}

void RubiksCube::Initialize() {
    Model();
    for (int i = 0; i < 27; i++) {
        textures[i].SetAnisotropy(16.0f);
        std::string path = "../texture/cube" + std::to_string(i) + ".png";
        textures[i].Setup(path.c_str());
    }
}

void RubiksCube::Paint(Shader shader, const glm::mat4 &vpMatrix) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                glBindVertexArray(vao);
                int cubeIndex = 9 * x + 3 * y + z;
                textures[cubeIndex].Bind(0);
                glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x - 1, y - 1, z - 1));
                glm::mat4 modelMatrix = transMatrices[cubeIndex] * translateMatrix;
                glm::mat4 MVP = vpMatrix * modelMatrix;
                shader.SetMat4("MVP", MVP);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            }
        }
    }
}

bool RubiksCube::RotateCube(RubiksCube::Rotate rotate) {
    if (!rotating) {
        rotating = true;
        glfwSetTime(0);
        for (int i = 0; i < 27; i++) {
            tempTransMatrices[i] = transMatrices[i];
        }
    } else {
        float currentFrame = (float)glfwGetTime();
        glm::vec3 axis;
        float angle = GetAngleAndAxis(rotate, axis);

        if (currentFrame < rotateTime) {
            for (int i = 0; i < 27; i++) {
                transMatrices[i] = glm::rotate(glm::mat4(1.0f), glm::radians(angle * currentFrame / rotateTime), axis) * tempTransMatrices[i];
            }
        } else {
            for (int i = 0; i < 27; i++) {
                transMatrices[i] = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * tempTransMatrices[i];
                RoundMat4(transMatrices[i]);
            }

            MoveIndices(rotate);
            rotating = false;
            return true;
        }
    }

    return false;
}

bool RubiksCube::MoveLayer(RubiksCube::Move move) {
    if (!rotating) {
        rotating = true;
        glfwSetTime(0);
        for (const auto &i : LAYERS_INDICES[(int)move % 15]) {
            int index = cubeIndices[i];
            tempTransMatrices[index] = transMatrices[index];
        }
    } else {
        float currentFrame = (float)glfwGetTime();
        glm::vec3 axis;
        float angle = GetAngleAndAxis(move, axis);

        if (currentFrame < rotateTime) {
            for (const auto &i : LAYERS_INDICES[(int)move % 15]) {
                int index = cubeIndices[i];
                transMatrices[index] = glm::rotate(glm::mat4(1.0f), glm::radians(angle * currentFrame / rotateTime), axis) * tempTransMatrices[index];
            }
        } else {
            for (const auto &i : LAYERS_INDICES[(int)move % 15]) {
                int index = cubeIndices[i];
                transMatrices[index] = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * tempTransMatrices[index];
                RoundMat4(transMatrices[index]);
            }

            MoveIndices(move);
            rotating = false;
            return true;
        }
    }

    return false;
}

void RubiksCube::Model() {
    float vertices[] = {
        // Front
        -0.5f, -0.5f,  0.5f, 0.50f, 0.25f,
         0.5f, -0.5f,  0.5f, 0.75f, 0.25f,
         0.5f,  0.5f,  0.5f, 0.75f, 0.50f,
        -0.5f,  0.5f,  0.5f, 0.50f, 0.50f,
        // Back
         0.5f, -0.5f, -0.5f, 0.00f, 0.25f,
        -0.5f, -0.5f, -0.5f, 0.25f, 0.25f,
        -0.5f,  0.5f, -0.5f, 0.25f, 0.50f,
         0.5f,  0.5f, -0.5f, 0.00f, 0.50f,
        // Up
        -0.5f,  0.5f,  0.5f, 0.25f, 0.50f,
         0.5f,  0.5f,  0.5f, 0.50f, 0.50f,
         0.5f,  0.5f, -0.5f, 0.50f, 0.75f,
        -0.5f,  0.5f, -0.5f, 0.25f, 0.75f,
        // Down
        -0.5f, -0.5f, -0.5f, 0.25f, 0.00f,
         0.5f, -0.5f, -0.5f, 0.50f, 0.00f,
         0.5f, -0.5f,  0.5f, 0.50f, 0.25f,
        -0.5f, -0.5f,  0.5f, 0.25f, 0.25f,
        // Left
        -0.5f, -0.5f, -0.5f, 0.25f, 0.25f,
        -0.5f, -0.5f,  0.5f, 0.50f, 0.25f,
        -0.5f,  0.5f,  0.5f, 0.50f, 0.50f,
        -0.5f,  0.5f, -0.5f, 0.25f, 0.50f,
        // Right
         0.5f, -0.5f,  0.5f, 0.75f, 0.25f,
         0.5f, -0.5f, -0.5f, 1.00f, 0.25f,
         0.5f,  0.5f, -0.5f, 1.00f, 0.50f,
         0.5f,  0.5f,  0.5f, 0.75f, 0.50f
    };

    GLuint indices[] = {
        //Front
         0,  1,  3,
         1,  2,  3,
        // Back
         4,  5,  7,
         5,  6,  7,
        // Up
         8,  9, 11,
         9, 10, 11,
        // Down
        12, 13, 15,
        13, 14, 15,
        // Left
        16, 17, 19,
        17, 18, 19,
        // Right
        20, 21, 23,
        21, 22, 23
    };

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    // uv
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
}

float RubiksCube::GetAngleAndAxis(RubiksCube::Rotate rotate, glm::vec3 &axis) {
    float angle = 0.0f;

    switch (rotate) {
    case Rotate::X:
        angle = -90.0f;
        axis = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    case Rotate::Y:
        angle = -90.0f;
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case Rotate::Z:
        angle = -90.0f;
        axis = glm::vec3(0.0f, 0.0f, 1.0f);
        break;
    case Rotate::XP:
        angle = 90.0f;
        axis = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    case Rotate::YP:
        angle = 90.0f;
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case Rotate::ZP:
        angle = 90.0f;
        axis = glm::vec3(0.0f, 0.0f, 1.0f);
        break;
    }

    return angle;
}

float RubiksCube::GetAngleAndAxis(RubiksCube::Move move, glm::vec3 &axis) {
    float angle = 0.0f;

    switch (move) {
    case Move::F:
    case Move::S:
    case Move::F2:
    case Move::BP:
    case Move::B2P:
        angle = -90.0f;
        axis = glm::vec3(0.0f, 0.0f, 1.0f);
        break;
    case Move::B:
    case Move::B2:
    case Move::FP:
    case Move::SP:
    case Move::F2P:
        angle = 90.0f;
        axis = glm::vec3(0.0f, 0.0f, 1.0f);
        break;
    case Move::U:
    case Move::U2:
    case Move::DP:
    case Move::EP:
    case Move::D2P:
        angle = -90.0f;
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case Move::D:
    case Move::E:
    case Move::D2:
    case Move::UP:
    case Move::U2P:
        angle = 90.0f;
        axis = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case Move::L:
    case Move::M:
    case Move::L2:
    case Move::RP:
    case Move::R2P:
        angle = 90.0f;
        axis = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    case Move::R:
    case Move::R2:
    case Move::LP:
    case Move::MP:
    case Move::L2P:
        angle = -90.0f;
        axis = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    }

    return angle;
}

void RubiksCube::MoveIndices(Rotate rotate) {
    switch (rotate) {
    case Rotate::X:
        RotateOnX(cubeIndices);
        RotateOnX(cubeIndices + 9);
        RotateOnX(cubeIndices + 18);
        break;
    case Rotate::Y:
        RotateOnY(cubeIndices);
        RotateOnY(cubeIndices + 3);
        RotateOnY(cubeIndices + 6);
        break;
    case Rotate::Z:
        RotateOnZ(cubeIndices);
        RotateOnZ(cubeIndices + 1);
        RotateOnZ(cubeIndices + 2);
        break;
    case Rotate::XP:
        RotateOnXP(cubeIndices);
        RotateOnXP(cubeIndices + 9);
        RotateOnXP(cubeIndices + 18);
        break;
    case Rotate::YP:
        RotateOnYP(cubeIndices);
        RotateOnYP(cubeIndices + 3);
        RotateOnYP(cubeIndices + 6);
        break;
    case Rotate::ZP:
        RotateOnZP(cubeIndices);
        RotateOnZP(cubeIndices + 1);
        RotateOnZP(cubeIndices + 2);
        break;
    }
}

void RubiksCube::MoveIndices(Move move) {
    switch (move) {
    case Move::F:
        RotateOnZ(cubeIndices + 2);
        break;
    case Move::B:
        RotateOnZP(cubeIndices);
        break;
    case Move::U:
        RotateOnY(cubeIndices + 6);
        break;
    case Move::D:
        RotateOnYP(cubeIndices);
        break;
    case Move::L:
        RotateOnXP(cubeIndices);
        break;
    case Move::R:
        RotateOnX(cubeIndices + 18);
        break;
    case Move::M:
        RotateOnXP(cubeIndices + 9);
        break;
    case Move::E:
        RotateOnYP(cubeIndices + 3);
        break;
    case Move::S:
        RotateOnZ(cubeIndices + 1);
        break;
    case Move::F2:
        RotateOnZ(cubeIndices + 1);
        RotateOnZ(cubeIndices + 2);
        break;
    case Move::B2:
        RotateOnZP(cubeIndices);
        RotateOnZP(cubeIndices + 1);
        break;
    case Move::U2:
        RotateOnY(cubeIndices + 3);
        RotateOnY(cubeIndices + 6);
        break;
    case Move::D2:
        RotateOnYP(cubeIndices);
        RotateOnYP(cubeIndices + 3);
        break;
    case Move::L2:
        RotateOnXP(cubeIndices);
        RotateOnXP(cubeIndices + 9);
        break;
    case Move::R2:
        RotateOnX(cubeIndices + 9);
        RotateOnX(cubeIndices + 18);
        break;
    case Move::FP:
        RotateOnZP(cubeIndices + 2);
        break;
    case Move::BP:
        RotateOnZ(cubeIndices);
        break;
    case Move::UP:
        RotateOnYP(cubeIndices + 6);
        break;
    case Move::DP:
        RotateOnY(cubeIndices);
        break;
    case Move::LP:
        RotateOnX(cubeIndices);
        break;
    case Move::RP:
        RotateOnXP(cubeIndices + 18);
        break;
    case Move::MP:
        RotateOnX(cubeIndices + 9);
        break;
    case Move::EP:
        RotateOnY(cubeIndices + 3);
        break;
    case Move::SP:
        RotateOnZP(cubeIndices + 1);
        break;
    case Move::F2P:
        RotateOnZP(cubeIndices + 1);
        RotateOnZP(cubeIndices + 2);
        break;
    case Move::B2P:
        RotateOnZ(cubeIndices);
        RotateOnZ(cubeIndices + 1);
        break;
    case Move::U2P:
        RotateOnYP(cubeIndices + 3);
        RotateOnYP(cubeIndices + 6);
        break;
    case Move::D2P:
        RotateOnY(cubeIndices);
        RotateOnY(cubeIndices + 3);
        break;
    case Move::L2P:
        RotateOnX(cubeIndices);
        RotateOnX(cubeIndices + 9);
        break;
    case Move::R2P:
        RotateOnXP(cubeIndices + 9);
        RotateOnXP(cubeIndices + 18);
        break;
    }
}

void RubiksCube::RotateOnX(int *arr) {
    int tempArr[9];
    for (int i = 0; i < 9; i++) {
        tempArr[i] = arr[i];
    }

    arr[0] = tempArr[6];
    arr[1] = tempArr[3];
    arr[2] = tempArr[0];
    arr[3] = tempArr[7];
    arr[5] = tempArr[1];
    arr[6] = tempArr[8];
    arr[7] = tempArr[5];
    arr[8] = tempArr[2];
}

void RubiksCube::RotateOnY(int *arr) {
    int tempArr[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tempArr[3 * i + j] = arr[9 * i + j];
        }
    }

    arr[0] = tempArr[2];
    arr[1] = tempArr[5];
    arr[2] = tempArr[8];
    arr[9] = tempArr[1];
    arr[11] = tempArr[7];
    arr[18] = tempArr[0];
    arr[19] = tempArr[3];
    arr[20] = tempArr[6];
}

void RubiksCube::RotateOnZ(int *arr) {
    int tempArr[9];
    for (int i = 0; i < 9; i++) {
        tempArr[i] = arr[3 * i];
    }

    arr[0] = tempArr[6];
    arr[3] = tempArr[3];
    arr[6] = tempArr[0];
    arr[9] = tempArr[7];
    arr[15] = tempArr[1];
    arr[18] = tempArr[8];
    arr[21] = tempArr[5];
    arr[24] = tempArr[2];
}

void RubiksCube::RotateOnXP(int *arr) {
    int tempArr[9];
    for (int i = 0; i < 9; i++) {
        tempArr[i] = arr[i];
    }

    arr[0] = tempArr[2];
    arr[1] = tempArr[5];
    arr[2] = tempArr[8];
    arr[3] = tempArr[1];
    arr[5] = tempArr[7];
    arr[6] = tempArr[0];
    arr[7] = tempArr[3];
    arr[8] = tempArr[6];
}

void RubiksCube::RotateOnYP(int *arr) {
    int tempArr[9];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tempArr[3 * i + j] = arr[9 * i + j];
        }
    }

    arr[0] = tempArr[6];
    arr[1] = tempArr[3];
    arr[2] = tempArr[0];
    arr[9] = tempArr[7];
    arr[11] = tempArr[1];
    arr[18] = tempArr[8];
    arr[19] = tempArr[5];
    arr[20] = tempArr[2];
}

void RubiksCube::RotateOnZP(int *arr) {
    int tempArr[9];
    for (int i = 0; i < 9; i++) {
        tempArr[i] = arr[3 * i];
    }

    arr[0] = tempArr[2];
    arr[3] = tempArr[5];
    arr[6] = tempArr[8];
    arr[9] = tempArr[1];
    arr[15] = tempArr[7];
    arr[18] = tempArr[0];
    arr[21] = tempArr[3];
    arr[24] = tempArr[6];
}

void RubiksCube::RoundMat4(glm::mat4 &matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = std::round(matrix[i][j]);
        }
    }
}
