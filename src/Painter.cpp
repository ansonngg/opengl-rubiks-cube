#include "Painter.h"

#include <string>

#include <glm/gtc/matrix_transform.hpp>

#include "GlobalVar.h"

Painter::Painter()
    : shader("../shader/VertexShader.glsl", "../shader/FragmentShader.glsl") {
    for (int i = 0; i < 26; i++) {
        std::string path = "../texture/cube" + std::to_string(i) + ".png";
        textures[i].Setup(path.c_str());
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
}

void Painter::Initialize() {
    Model();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void Painter::Loop() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.Use();

    glm::mat4 rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 0.0f));;
    glm::mat4 translateMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(EYE_X, EYE_Y, EYE_Z), glm::vec3(CENTER_X, CENTER_Y, CENTER_Z), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetMat4("viewMatrix", viewMatrix);
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
    shader.SetMat4("projectionMatrix", projectionMatrix);

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                if (x == 1 && y == 1 && z == 1) {
                    continue;
                }

                glBindVertexArray(vao);
                int textureIndex = 9 * x + 3 * y + z;
                if (textureIndex >= 14) {
                    textureIndex--;
                }
                textures[textureIndex].Bind(0);
                translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x - 1, y - 1, z - 1));
                modelMatrix = rotateMatrix * translateMatrix;
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
