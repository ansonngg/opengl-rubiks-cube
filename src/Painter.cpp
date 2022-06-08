#include "Painter.h"

#include <string>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Controller.h"

Painter::Painter(int width, int height)
    : SCR_WIDTH(width)
    , SCR_HEIGHT(height)
    , LAYERS_INDICES{
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
    , eye(-5.0f, 5.0f, 10.0f)
    , center(0.0f, 0.0f, 0.0f)
    , rotateTime(0.2f)
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

void Painter::Initialize() {
    Model();
    shader.Setup("../shader/VertexShader.glsl", "../shader/FragmentShader.glsl");
    for (int i = 0; i < 27; i++) {
        textures[i].SetAnisotropy(16.0f);
        std::string path = "../texture/cube" + std::to_string(i) + ".png";
        textures[i].Setup(path.c_str());
    }
}

void Painter::Loop() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.Use();

    glm::mat4 translateMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

    shader.SetMat4("viewMatrix", viewMatrix);
    shader.SetMat4("projectionMatrix", projectionMatrix);

    ProcessInput();

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                glBindVertexArray(vao);
                int cubeIndex = 9 * x + 3 * y + z;
                textures[cubeIndex].Bind(0);
                translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x - 1, y - 1, z - 1));
                modelMatrix = transMatrices[cubeIndex] * translateMatrix;
                shader.SetMat4("modelMatrix", modelMatrix);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            }
        }
    }
}

void Painter::Model() {
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
         0,  1,  3,
         1,  2,  3,
         4,  5,  7,
         5,  6,  7,
         8,  9, 11,
         9, 10, 11,
        12, 13, 15,
        13, 14, 15,
        16, 17, 19,
        17, 18, 19,
        20, 21, 23,
        21, 22, 23
    };

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Painter::ProcessInput() {
    if (keyboardCtrl.x) {
        if (RotateCube(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f))) {
            keyboardCtrl.x = false;
            RotateOnX(cubeIndices);
            RotateOnX(cubeIndices + 9);
            RotateOnX(cubeIndices + 18);
        }
    } else if (keyboardCtrl.y) {
        if (RotateCube(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f))) {
            keyboardCtrl.y = false;
            RotateOnY(cubeIndices);
            RotateOnY(cubeIndices + 3);
            RotateOnY(cubeIndices + 6);
        }
    } else if (keyboardCtrl.z) {
        if (RotateCube(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f))) {
            keyboardCtrl.z = false;
            RotateOnZ(cubeIndices);
            RotateOnZ(cubeIndices + 1);
            RotateOnZ(cubeIndices + 2);
        }
    } else if (keyboardCtrl.xp) {
        if (RotateCube(90.0f, glm::vec3(1.0f, 0.0f, 0.0f))) {
            keyboardCtrl.xp = false;
            RotateOnXP(cubeIndices);
            RotateOnXP(cubeIndices + 9);
            RotateOnXP(cubeIndices + 18);
        }
    } else if (keyboardCtrl.yp) {
        if (RotateCube(90.0f, glm::vec3(0.0f, 1.0f, 0.0f))) {
            keyboardCtrl.yp = false;
            RotateOnYP(cubeIndices);
            RotateOnYP(cubeIndices + 3);
            RotateOnYP(cubeIndices + 6);
        }
    } else if (keyboardCtrl.zp) {
        if (RotateCube(90.0f, glm::vec3(0.0f, 0.0f, 1.0f))) {
            keyboardCtrl.zp = false;
            RotateOnZP(cubeIndices);
            RotateOnZP(cubeIndices + 1);
            RotateOnZP(cubeIndices + 2);
        }
    } else if (keyboardCtrl.f) {
        if (MoveLayer(Move::F)) {
            keyboardCtrl.f = false;
            RotateOnZ(cubeIndices + 2);
        }
    } else if (keyboardCtrl.b) {
        if (MoveLayer(Move::B)) {
            keyboardCtrl.b = false;
            RotateOnZP(cubeIndices);
        }
    } else if (keyboardCtrl.u) {
        if (MoveLayer(Move::U)) {
            keyboardCtrl.u = false;
            RotateOnY(cubeIndices + 6);
        }
    } else if (keyboardCtrl.d) {
        if (MoveLayer(Move::D)) {
            keyboardCtrl.d = false;
            RotateOnYP(cubeIndices);
        }
    } else if (keyboardCtrl.l) {
        if (MoveLayer(Move::L)) {
            keyboardCtrl.l = false;
            RotateOnXP(cubeIndices);
        }
    } else if (keyboardCtrl.r) {
        if (MoveLayer(Move::R)) {
            keyboardCtrl.r = false;
            RotateOnX(cubeIndices + 18);
        }
    } else if (keyboardCtrl.m) {
        if (MoveLayer(Move::M)) {
            keyboardCtrl.m = false;
            RotateOnXP(cubeIndices + 9);
        }
    } else if (keyboardCtrl.e) {
        if (MoveLayer(Move::E)) {
            keyboardCtrl.e = false;
            RotateOnYP(cubeIndices + 3);
        }
    } else if (keyboardCtrl.s) {
        if (MoveLayer(Move::S)) {
            keyboardCtrl.s = false;
            RotateOnZ(cubeIndices + 1);
        }
    } else if (keyboardCtrl.f2) {
        if (MoveLayer(Move::F2)) {
            keyboardCtrl.f2 = false;
            RotateOnZ(cubeIndices + 1);
            RotateOnZ(cubeIndices + 2);
        }
    } else if (keyboardCtrl.b2) {
        if (MoveLayer(Move::B2)) {
            keyboardCtrl.b2 = false;
            RotateOnZP(cubeIndices);
            RotateOnZP(cubeIndices + 1);
        }
    } else if (keyboardCtrl.u2) {
        if (MoveLayer(Move::U2)) {
            keyboardCtrl.u2 = false;
            RotateOnY(cubeIndices + 3);
            RotateOnY(cubeIndices + 6);
        }
    } else if (keyboardCtrl.d2) {
        if (MoveLayer(Move::D2)) {
            keyboardCtrl.d2 = false;
            RotateOnYP(cubeIndices);
            RotateOnYP(cubeIndices + 3);
        }
    } else if (keyboardCtrl.l2) {
        if (MoveLayer(Move::L2)) {
            keyboardCtrl.l2 = false;
            RotateOnXP(cubeIndices);
            RotateOnXP(cubeIndices + 9);
        }
    } else if (keyboardCtrl.r2) {
        if (MoveLayer(Move::R2)) {
            keyboardCtrl.r2 = false;
            RotateOnX(cubeIndices + 9);
            RotateOnX(cubeIndices + 18);
        }
    } else if (keyboardCtrl.fp) {
        if (MoveLayer(Move::FP)) {
            keyboardCtrl.fp = false;
            RotateOnZP(cubeIndices + 2);
        }
    } else if (keyboardCtrl.bp) {
        if (MoveLayer(Move::BP)) {
            keyboardCtrl.bp = false;
            RotateOnZ(cubeIndices);
        }
    } else if (keyboardCtrl.up) {
        if (MoveLayer(Move::UP)) {
            keyboardCtrl.up = false;
            RotateOnYP(cubeIndices + 6);
        }
    } else if (keyboardCtrl.dp) {
        if (MoveLayer(Move::DP)) {
            keyboardCtrl.dp = false;
            RotateOnY(cubeIndices);
        }
    } else if (keyboardCtrl.lp) {
        if (MoveLayer(Move::LP)) {
            keyboardCtrl.lp = false;
            RotateOnX(cubeIndices);
        }
    } else if (keyboardCtrl.rp) {
        if (MoveLayer(Move::RP)) {
            keyboardCtrl.rp = false;
            RotateOnXP(cubeIndices + 18);
        }
    } else if (keyboardCtrl.mp) {
        if (MoveLayer(Move::MP)) {
            keyboardCtrl.mp = false;
            RotateOnX(cubeIndices + 9);
        }
    } else if (keyboardCtrl.ep) {
        if (MoveLayer(Move::EP)) {
            keyboardCtrl.ep = false;
            RotateOnY(cubeIndices + 3);
        }
    } else if (keyboardCtrl.sp) {
        if (MoveLayer(Move::SP)) {
            keyboardCtrl.sp = false;
            RotateOnZP(cubeIndices + 1);
        }
    } else if (keyboardCtrl.f2p) {
        if (MoveLayer(Move::F2P)) {
            keyboardCtrl.f2p = false;
            RotateOnZP(cubeIndices + 1);
            RotateOnZP(cubeIndices + 2);
        }
    } else if (keyboardCtrl.b2p) {
        if (MoveLayer(Move::B2P)) {
            keyboardCtrl.b2p = false;
            RotateOnZ(cubeIndices);
            RotateOnZ(cubeIndices + 1);
        }
    } else if (keyboardCtrl.u2p) {
        if (MoveLayer(Move::U2P)) {
            keyboardCtrl.u2p = false;
            RotateOnYP(cubeIndices + 3);
            RotateOnYP(cubeIndices + 6);
        }
    } else if (keyboardCtrl.d2p) {
        if (MoveLayer(Move::D2P)) {
            keyboardCtrl.d2p = false;
            RotateOnY(cubeIndices);
            RotateOnY(cubeIndices + 3);
        }
    } else if (keyboardCtrl.l2p) {
        if (MoveLayer(Move::L2P)) {
            keyboardCtrl.l2p = false;
            RotateOnX(cubeIndices);
            RotateOnX(cubeIndices + 9);
        }
    } else if (keyboardCtrl.r2p) {
        if (MoveLayer(Move::R2P)) {
            keyboardCtrl.r2p = false;
            RotateOnXP(cubeIndices + 9);
            RotateOnXP(cubeIndices + 18);
        }
    }
}

bool Painter::RotateCube(float angle, glm::vec3 axis) {
    if (!rotating) {
        rotating = true;
        glfwSetTime(0);

        for (int i = 0; i < 27; i++) {
            tempTransMatrices[i] = transMatrices[i];
        }
    } else {
        float currentFrame = (float)glfwGetTime();

        if (currentFrame < rotateTime) {
            for (int i = 0; i < 27; i++) {
                transMatrices[i] = glm::rotate(glm::mat4(1.0f), glm::radians(angle * currentFrame / rotateTime), axis) * tempTransMatrices[i];
            }
        } else {
            for (int i = 0; i < 27; i++) {
                transMatrices[i] = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * tempTransMatrices[i];
                RoundMat4(transMatrices[i]);
            }

            keyboardCtrl.acceptInput = true;
            rotating = false;
            return true;
        }
    }

    return false;
}

bool Painter::MoveLayer(Move move) {
    if (!rotating) {
        rotating = true;
        glfwSetTime(0);

        for (const auto &i : LAYERS_INDICES[(int)move % 15]) {
            int index = cubeIndices[i];
            tempTransMatrices[index] = transMatrices[index];
        }
    } else {
        float currentFrame = (float)glfwGetTime();
        float angle;
        glm::vec3 axis;

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
        default:
            angle = -90.0f;
            axis = glm::vec3(1.0f, 0.0f, 0.0f);
            break;
        }

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

            keyboardCtrl.acceptInput = true;
            rotating = false;
            return true;
        }
    }

    return false;
}

void Painter::RotateOnX(int *arr) {
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

void Painter::RotateOnY(int *arr) {
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

void Painter::RotateOnZ(int *arr) {
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

void Painter::RotateOnXP(int *arr) {
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

void Painter::RotateOnYP(int *arr) {
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

void Painter::RotateOnZP(int *arr) {
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

void Painter::RoundMat4(glm::mat4 &matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = std::round(matrix[i][j]);
        }
    }
}
