#ifndef PAINTER_H
#define PAINTER_H

#include "Shader.h"
#include "Texture.h"

class Painter {
public:
    Painter();
    void Initialize();
    void Loop();

private:
    Shader shader;
    GLuint vao, vbo, ebo;
    Texture textures[26];

    void Model();
};

#endif // PAINTER_H
