#include "Shader.h"

#include <fstream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &vShaderPath, const std::string &fShaderPath) {
    std::string vString = ReadShaderCode(vShaderPath);
    std::string fString = ReadShaderCode(fShaderPath);
    const char *vShaderCode = vString.c_str();
    const char *fShaderCode = fString.c_str();

    int success;
    char infoLog[512];

    GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShaderID, 1, &vShaderCode, NULL);
    glCompileShader(vShaderID);
    glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        std::cout << infoLog << '\n';
    };

    GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShaderID, 1, &fShaderCode, NULL);
    glCompileShader(fShaderID);
    glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fShaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
        std::cout << infoLog << '\n';
    };

    ID = glCreateProgram();
    glAttachShader(ID, vShaderID);
    glAttachShader(ID, fShaderID);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
        std::cout << infoLog << '\n';
    }

    glDeleteShader(vShaderID);
    glDeleteShader(fShaderID);
}

void Shader::Use() {
    glUseProgram(ID);
}

void Shader::SetBool(const char *name, bool value) {
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetInt(const char *name, int value) {
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::SetFloat(const char *name, float value) {
    glUniform1f(glGetUniformLocation(ID, name), value);
}

void Shader::SetVec3(const char *name, glm::vec3 value) {
    glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
}

void Shader::SetMat4(const char *name, glm::mat4 value) {
    GLuint location = glGetUniformLocation(ID, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

std::string Shader::ReadShaderCode(const std::string &path) {
    std::ifstream shaderFile(path);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}
