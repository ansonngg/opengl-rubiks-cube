#ifndef PAINTER_H
#define PAINTER_H

#include "Shader.h"
#include "Texture.h"

class Painter {
public:
    Painter(int width, int height);
    void Initialize();
    void Loop();

private:
    const int SCR_WIDTH, SCR_HEIGHT;
    glm::vec3 eye, center;
    GLuint vao, vbo, ebo;
    Shader shader;
    Texture textures[26];

    void Model();
};

#endif // PAINTER_H
