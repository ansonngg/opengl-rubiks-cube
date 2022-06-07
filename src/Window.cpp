#include "Window.h"

#include "Callback.h"
#include "Painter.h"

Window::Window(int width, int height, int sampleNum)
    : SCR_WIDTH(width)
    , SCR_HEIGHT(height)
    , SAMPLE_NUM(sampleNum) {}

int Window::Exec() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (SAMPLE_NUM > 1) {
        glfwWindowHint(GLFW_SAMPLES, SAMPLE_NUM);
    }

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

    Painter painter(SCR_WIDTH, SCR_HEIGHT);
    glfwSetWindowUserPointer(window, (void *)&painter);
    glfwSetFramebufferSizeCallback(window, Callback::FramebufferSize);
    glfwSetKeyCallback(window, Callback::Key);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    if (SAMPLE_NUM > 1) {
        glEnable(GL_MULTISAMPLE);
    }

    painter.Initialize();

    while (!glfwWindowShouldClose(window)) {
        painter.Loop();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
