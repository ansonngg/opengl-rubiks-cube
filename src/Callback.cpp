#include "Callback.h"

#include "Painter.h"

void Callback::FramebufferSize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Callback::Key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Painter *painter = (Painter *)glfwGetWindowUserPointer(window);

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (painter->keyboardCtrl.acceptInput) {
        if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
            painter->keyboardCtrl.x = true;
            painter->keyboardCtrl.acceptInput = false;
        } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
            painter->keyboardCtrl.xp = true;
            painter->keyboardCtrl.acceptInput = false;
        } else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
            painter->keyboardCtrl.y = true;
            painter->keyboardCtrl.acceptInput = false;
        } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
            painter->keyboardCtrl.yp = true;
            painter->keyboardCtrl.acceptInput = false;
        } else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
            painter->keyboardCtrl.f = true;
            painter->keyboardCtrl.acceptInput = false;
        }
    }
}
