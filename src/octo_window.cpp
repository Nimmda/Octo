#include "octo_window.hpp"

namespace octo
{
    OctoWindow::OctoWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name}
    {
        initWindow();
    }

    OctoWindow::~OctoWindow()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void OctoWindow::initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No OpenGL Mode
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    }
} // namespace octo