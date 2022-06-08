#include "Callback.h"

#include "Painter.h"

void Callback::FramebufferSize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Callback::Key(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Painter *painter = (Painter *)glfwGetWindowUserPointer(window);

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, true);
        } else if (key == GLFW_KEY_APOSTROPHE) {
            painter->keyboardCtrl.prime = true;
        } else if (key == GLFW_KEY_LEFT_SHIFT) {
            painter->keyboardCtrl.shift = true;
        } else if (painter->keyboardCtrl.acceptInput) {
            if (key == GLFW_KEY_UP || key == GLFW_KEY_X && !painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.x = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_LEFT || key == GLFW_KEY_Y && !painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.y = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_Z && !painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.z = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_DOWN || key == GLFW_KEY_X && painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.xp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_RIGHT || key == GLFW_KEY_Y && painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.yp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_Z && painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.zp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_F && !painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.f = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_B && !painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.b = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_U && !painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.u = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_D && !painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.d = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_L && !painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.l = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_R && !painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.r = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_M && !painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.m = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_E && !painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.e = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_S && !painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.s = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_F && painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.fp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_B && painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.bp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_U && painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.up = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_D && painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.dp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_L && painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.lp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_R && painter->keyboardCtrl.prime && !painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.rp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_M && painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.mp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_E && painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.ep = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_S && painter->keyboardCtrl.prime) {
                painter->keyboardCtrl.sp = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_F && !painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.f2 = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_B && !painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.b2 = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_U && !painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.u2 = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_D && !painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.d2 = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_L && !painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.l2 = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_R && !painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.r2 = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_F && painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.f2p = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_B && painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.b2p = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_U && painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.u2p = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_D && painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.d2p = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_L && painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.l2p = true;
                painter->keyboardCtrl.acceptInput = false;
            } else if (key == GLFW_KEY_R && painter->keyboardCtrl.prime && painter->keyboardCtrl.shift) {
                painter->keyboardCtrl.r2p = true;
                painter->keyboardCtrl.acceptInput = false;
            }
        }
    } else if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_APOSTROPHE) {
            painter->keyboardCtrl.prime = false;
        } else if (key == GLFW_KEY_LEFT_SHIFT) {
            painter->keyboardCtrl.shift = false;
        }
    }
}
