#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 texCoor;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);
    texCoor = uv;
}
