#ifndef CALLBACK_H
#define CALLBACK_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Callback {
void FramebufferSize(GLFWwindow *window, int width, int height);
void Key(GLFWwindow *window, int key, int scancode, int action, int mods);
}

#endif // CALLBACK_H
