#ifndef PAINTER_H
#define PAINTER_H

#include "Shader.h"

class Painter {
public:
    Painter();
    void Initialize();
    void Loop();

private:
    Shader shader;
    GLuint vao[26], vbo[26], ebo[26];

    void Model();
};

#endif // PAINTER_H
