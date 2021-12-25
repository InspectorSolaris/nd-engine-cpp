#pragma once

#include "pch.hpp"
#include "shared.hpp"

#include "instance.hpp"
#include "device.hpp"
#include "swapchain.hpp"
#include "descriptor_pool.hpp"
#include "descriptor_set_layout.hpp"
#include "descriptor_set.hpp"
#include "render_pass.hpp"
#include "shader_module.hpp"
#include "pipeline_layout.hpp"
#include "pipeline.hpp"
#include "image.hpp"
#include "image_view.hpp"
#include "framebuffer.hpp"
#include "buffer.hpp"
#include "buffer_view.hpp"
#include "command_pool.hpp"
#include "command_buffer.hpp"
#include "synchronization.hpp"

namespace nd::src::graphics::vulkan
{
    struct VulkanContextConfigurationExternal final
    {
        const std::string& applicationName;
        const std::string& engineName;

        const std::vector<std::string>& layers;
        const std::vector<std::string>& extensions;

        const uint32_t width;
        const uint32_t height;
    };

    struct VulkanContextInitializers final
    {
        const std::function<VkSurfaceKHR(const VkInstance)>& getSurface;
    };

    struct VulkanContextConfigurations final
    {
    };

    class VulkanContext final
    {
    public:
        struct Configuration final
        {
            const std::map<uint32_t, std::vector<VkQueue>>& deviceQueues;
            const std::map<uint32_t, std::vector<VkQueue>>& swapchainQueues;

            const std::vector<QueueFamily>& deviceQueueFamilies;
            const std::vector<QueueFamily>& swapchainQueueFamilies;

            const std::vector<VkImage>&         swapchainImages;
            const std::vector<VkImageView>&     swapchainImageViews;
            const std::vector<VkFramebuffer>&   swapchainFramebuffers;
            const std::vector<VkShaderModule>&  shaderModules;
            const std::vector<VkDescriptorSet>& descriptorSets;
            const std::vector<VkPipeline>&      pipelines;
            const std::vector<VkCommandBuffer>& commandBuffers;

            const std::vector<VkSemaphore>& imageAcquiredSemaphores;
            const std::vector<VkSemaphore>& imageRenderedSemaphores;
            const std::vector<VkFence>&     imageAcquiredFences;
            const std::vector<VkFence>&     imageRenderedFences;

            const size_t framesCount;

            const VkInstance            instance;
            const VkDevice              device;
            const VkSurfaceKHR          surface;
            const VkSwapchainKHR        swapchain;
            const VkRenderPass          renderPass;
            const VkDescriptorPool      descriptorPool;
            const VkDescriptorSetLayout descriptorSetLayout;
            const VkPipelineLayout      pipelineLayout;
            const VkCommandPool         commandPool;
        };

        VulkanContext(const Configuration& configuration);

        VulkanContext(const VulkanContext& vulkanContext) = delete;
        VulkanContext(VulkanContext&& vulkanContext)      = delete;

        VulkanContext&
        operator=(const VulkanContext& vulkanContext) = delete;
        VulkanContext&
        operator=(VulkanContext&& vulkanContext) = delete;

        ~VulkanContext();

        void
        drawNextFrame();

    private:
        std::map<uint32_t, std::vector<VkQueue>> deviceQueues_ {};
        std::map<uint32_t, std::vector<VkQueue>> swapchainQueues_ {};

        std::vector<QueueFamily> deviceQueueFamilies_ {};
        std::vector<QueueFamily> swapchainQueueFamilies_ {};

        std::vector<VkImage>         swapchainImages_ {};
        std::vector<VkImageView>     swapchainImageViews_ {};
        std::vector<VkFramebuffer>   swapchainFramebuffers_ {};
        std::vector<VkShaderModule>  shaderModules_ {};
        std::vector<VkDescriptorSet> descriptorSets_ {};
        std::vector<VkPipeline>      pipelines_ {};
        std::vector<VkCommandBuffer> commandBuffers_ {};

        std::vector<VkSemaphore> imageAcquiredSemaphores_ {};
        std::vector<VkSemaphore> imageRenderedSemaphores_ {};
        std::vector<VkFence>     imageAcquiredFences_ {};
        std::vector<VkFence>     imageRenderedFences_ {};

        size_t framesCount_ {};

        VkInstance            instance_ {};
        VkDevice              device_ {};
        VkSurfaceKHR          surface_ {};
        VkSwapchainKHR        swapchain_ {};
        VkRenderPass          renderPass_ {};
        VkDescriptorPool      descriptorPool_ {};
        VkDescriptorSetLayout descriptorSetLayout_ {};
        VkPipelineLayout      pipelineLayout_ {};
        VkCommandPool         commandPool_ {};
    };

    VulkanContext
    getVulkanContext(const VulkanContextConfigurationExternal& configurationExternal,
                     const VulkanContextInitializers&          initializers,
                     const VulkanContextConfigurations&        configurations);
} // namespace nd::src::graphics::vulkan
