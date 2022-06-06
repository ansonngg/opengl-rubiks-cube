#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

class Texture {
public:
	void Setup(const char *path);
	void Bind(GLuint slot);
	void Unbind();

private:
	GLuint ID;
};

#endif // TEXTURE_H
