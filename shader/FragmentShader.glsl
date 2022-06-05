#version 460 core

in vec3 mColor;

out vec4 FragColor;

void main() {
    FragColor = vec4(mColor, 1.0);
}
