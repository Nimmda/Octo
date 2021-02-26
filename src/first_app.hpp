#pragma once

#include "octo_window.hpp"
#include "octo_pipeline.hpp"
#include "octo_device.hpp"
#include "octo_swap_chain.hpp"
#include "octo_model.hpp"

//std
#include <memory>
#include <vector>

namespace octo
{
    class FirstApp
    {
    private:
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();

        OctoWindow octoWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
        OctoDevice octoDevice{octoWindow};
        OctoSwapChain octoSwapChain{octoDevice, octoWindow.getExtend()};
        std::unique_ptr<OctoPipeline> octoPipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffer;
        std::unique_ptr<OctoModel> octoModel;

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        FirstApp();
        ~FirstApp();

        FirstApp(const FirstApp &) = delete;
        void operator=(const FirstApp &) = delete;

        void run();
    };

} // namespace octo
