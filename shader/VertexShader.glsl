#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 mColor;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
    mColor = color;
}
