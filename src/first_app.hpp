#pragma once

#include "octo_window.hpp"

namespace octo
{
    class FirstApp
    {
    private:
        OctoWindow octoWindow{WIDTH, HEIGHT, "Hello Vulkan!"};

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        void run();
    };

} // namespace octo
