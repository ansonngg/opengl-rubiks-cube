#ifndef SHADER_H
#define SHADER_H

#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string &vShaderPath, const std::string &fShaderPath);
    void Use();
    void SetBool(const char *name, bool value);
    void SetInt(const char *name, int value);
    void SetFloat(const char *name, float value);
    void SetVec3(const char *name, glm::vec3 value);
    void SetMat4(const char *name, glm::mat4 value);

private:
    GLuint ID;

    std::string ReadShaderCode(const std::string &path);
};

#endif // SHADER_H
