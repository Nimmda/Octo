#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace octo
{
    class OctoWindow
    {
    public:
        OctoWindow(int w, int h, std::string name);
        ~OctoWindow();

        OctoWindow(const OctoWindow &) = delete;
        OctoWindow &operator=(const OctoWindow &) = delete;

        bool shouldClose() { return glfwWindowShouldClose(window); }

    private:
        GLFWwindow *window;

        const int width;
        const int height;

        std::string windowName;

        void initWindow();
    };
} // namespace octo