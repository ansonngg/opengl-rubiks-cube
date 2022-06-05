#include "Painter.h"

#include <glm/gtc/matrix_transform.hpp>

#include "GlobalVar.h"

Painter::Painter()
    : shader("../shader/VertexShader.glsl", "../shader/FragmentShader.glsl") {
    glGenVertexArrays(26, vao);
    glGenBuffers(26, vbo);
    glGenBuffers(26, ebo);
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

    glm::mat4 rotateMatrix;
    glm::mat4 translateMatrix;
    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(EYE_X, EYE_Y, EYE_Z), glm::vec3(CENTER_X, CENTER_Y, CENTER_Z), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.SetMat4("viewMatrix", viewMatrix);
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
    shader.SetMat4("projectionMatrix", projectionMatrix);

    glBindVertexArray(vao[0]);
    translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, -1.0f));
    rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = rotateMatrix * translateMatrix;
    shader.SetMat4("modelMatrix", modelMatrix);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Painter::Model() {
    float vertices[] = {
        // Front
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
        // Back
         0.5f, -0.5f, -0.5f, 0.0f, 155.0f / 255.0f, 72.0f / 255.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 155.0f / 255.0f, 72.0f / 255.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 155.0f / 255.0f, 72.0f / 255.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 155.0f / 255.0f, 72.0f / 255.0f,
        // Up
        -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        // Down
        -0.5f, -0.5f, -0.5f, 1.0f, 213.0f / 255.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 213.0f / 255.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 213.0f / 255.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 213.0f / 255.0f, 0.0f,
        // Left
        -0.5f, -0.5f, -0.5f, 183.0f / 255.0f, 18.0f / 255.0f, 52.0f / 255.0f,
        -0.5f, -0.5f,  0.5f, 183.0f / 255.0f, 18.0f / 255.0f, 52.0f / 255.0f,
        -0.5f,  0.5f,  0.5f, 183.0f / 255.0f, 18.0f / 255.0f, 52.0f / 255.0f,
        -0.5f,  0.5f, -0.5f, 183.0f / 255.0f, 18.0f / 255.0f, 52.0f / 255.0f,
        // Right
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f
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

    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
}
