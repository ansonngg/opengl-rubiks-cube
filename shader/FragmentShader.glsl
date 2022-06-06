#version 460 core

in vec2 texCoor;

uniform sampler2D mTexture;

out vec4 FragColor;

void main() {
    FragColor = texture(mTexture, texCoor);
}
