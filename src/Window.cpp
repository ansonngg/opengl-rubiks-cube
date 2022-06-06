#include "Window.h"

#include <glad/glad.h>

#include "Callback.h"
#include "Painter.h"

Window::Window(int width, int height)
    : SCR_WIDTH(width)
    , SCR_HEIGHT(height) {}

int Window::Exec() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Rubik's Cube", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, Callback::FramebufferSize);
    glfwSetKeyCallback(window, Callback::Key);

    Painter painter(SCR_WIDTH, SCR_HEIGHT);
    painter.Initialize();

    while (!glfwWindowShouldClose(window)) {
        painter.Loop();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
