#version 460 core

in vec2 texCoord;

uniform sampler2D mTexture;

out vec4 FragColor;

void main() {
    FragColor = texture(mTexture, texCoord);
}
