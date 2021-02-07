#include "first_app.hpp"

namespace octo
{
    void FirstApp::run()
    {
        while (!octoWindow.shouldClose())
        {
            glfwPollEvents();
        }
    }
} // namespace octo