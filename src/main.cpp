#include "game.h"
#include "resourcemanager.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <Windows.h>
extern "C" {
    _declspec(dllexport) DWORD NvOptimusEnablement = 1;
}
#endif

inline constexpr uint32_t SCREEN_WIDTH = 800;
inline constexpr uint32_t SCREEN_HEIGHT = 600;

Game breakout{SCREEN_WIDTH, SCREEN_HEIGHT};

void key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode);
void framebuffer_size_callback(GLFWwindow* window, int32_t width, int32_t height);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __AAPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    breakout.Init();

    float delta_time = 0.0f;
    float last_frame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        glfwPollEvents();

        breakout.ProcessInput(delta_time);
        breakout.Update(delta_time);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        breakout.Render();

        glfwSwapBuffers(window);
    }
    ResourceManager::getInstance().Clear();
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            breakout.SetKey(key, true);
        } else if (action == GLFW_RELEASE) {
            breakout.SetKey(key, false);
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int32_t width, int32_t height)
{
    (void)window;
    glViewport(0, 0, width, height);
}