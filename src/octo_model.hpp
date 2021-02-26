#pragma once
#include "octo_device.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

// std
#include <vector>

namespace octo
{
    class OctoModel
    {
    public:
        struct Vertex
        {
            glm::vec2 position;
            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        OctoModel(OctoDevice &device, const std::vector<Vertex> &vertices);
        ~OctoModel();

        OctoModel(const OctoModel &) = delete;
        void operator=(const OctoModel &) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

    private:
        void createVertexBuffers(const std::vector<Vertex> &vertices);

        OctoDevice &octoDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
    };

} // namespace octo
