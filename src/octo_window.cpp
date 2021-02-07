#include "octo_window.hpp"

#include <stdexcept>

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

    void OctoWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
        {
            throw ::std::runtime_error("failed to create window surface");
        }
    }
} // namespace octo