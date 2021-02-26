#include "first_app.hpp"

// std
#include <stdexcept>

namespace octo
{
    FirstApp::FirstApp()
    {
        loadModels();
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    FirstApp::~FirstApp()
    {
        vkDestroyPipelineLayout(octoDevice.device(), pipelineLayout, nullptr);
    }

    void FirstApp::run()
    {
        while (!octoWindow.shouldClose())
        {
            glfwPollEvents();
            drawFrame();
        }
        vkDeviceWaitIdle(octoDevice.device());
    }

    void FirstApp::loadModels()
    {
        std::vector<OctoModel::Vertex> vertices{
            {{0.0f, -0.5f}},
            {{0.5f, 0.5f}},
            {{-0.5f, 0.5f}}};
        octoModel = std::make_unique<OctoModel>(octoDevice, vertices);
    }

    void FirstApp::createPipelineLayout()
    {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(octoDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void FirstApp::createPipeline()
    {
        auto pipelineConfig = OctoPipeline::defaultPipelineConfigInfo(octoSwapChain.width(), octoSwapChain.height());
        pipelineConfig.renderPass = octoSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        octoPipeline = std::make_unique<OctoPipeline>(
            octoDevice,
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv",
            pipelineConfig);
    }

    void FirstApp::createCommandBuffers()
    {
        commandBuffer.resize(octoSwapChain.imageCount());
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = octoDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffer.size());

        if (vkAllocateCommandBuffers(octoDevice.device(), &allocInfo, commandBuffer.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for (int i = 0; i < static_cast<int>(commandBuffer.size()); i++)
        {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(commandBuffer[i], &beginInfo) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = octoSwapChain.getRenderPass();
            renderPassInfo.framebuffer = octoSwapChain.getFrameBuffer(i);

            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = octoSwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
            clearValues[1].depthStencil = {1.0f, 0};

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffer[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            octoPipeline->bind(commandBuffer[i]);
            octoModel->bind(commandBuffer[i]);
            octoModel->draw(commandBuffer[i]);

            vkCmdEndRenderPass(commandBuffer[i]);

            if (vkEndCommandBuffer(commandBuffer[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    }
    void FirstApp::drawFrame()
    {
        uint32_t imageIndex;
        auto result = octoSwapChain.acquireNextImage(&imageIndex);

        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("failed to aquire swap chain image!");
        }

        result = octoSwapChain.submitCommandBuffers(&commandBuffer[imageIndex], &imageIndex);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to present swap chain image!");
        }
    }
} // namespace octo