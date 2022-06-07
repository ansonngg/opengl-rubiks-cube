#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture {
public:
	Texture();
	void SetAnisotropy(float value);
	void Setup(const char *path);
	void Bind(GLuint slot);
	void Unbind();

private:
	GLuint ID;
	float anisotropy;
};

inline void Texture::SetAnisotropy(float value) {
	anisotropy = value;
}

#endif // TEXTURE_H
