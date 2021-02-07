#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
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
        VkExtent2D getExtend() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    private:
        GLFWwindow *window;

        const int width;
        const int height;

        std::string windowName;

        void initWindow();
    };
} // namespace octo