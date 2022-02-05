#pragma once

#include "pch.hpp"
#include "tools.hpp"

#include "objects_cfg.hpp"

namespace nd::src::graphics::vulkan
{
    class VulkanObjectsCfgBuilder final
    {
    public:
        using Type    = VulkanObjectsCfg;
        using Builder = VulkanObjectsCfgBuilder;

        static Builder
        getDefault() noexcept(ND_ASSERT_NOTHROW)
        {
            return Builder {} << getInstanceCfg << getPhysicalDeviceCfg << getDeviceCfg << getSwapchainCfg << getRenderPassCfg
                              << getSwapchainImageViewCfg << getSwapchainFramebufferCfg << getShaderModuleCfgs << getDescriptorPoolCfg
                              << getDescriptorSetLayoutObjectsCfg << getPipelineCacheCfg << getPipelineLayoutObjectsCfg << getPipelineObjectsCfg;
        }

        operator Type() const noexcept(ND_ASSERT_NOTHROW)
        {
            return get();
        }

        Type
        get() const noexcept(ND_ASSERT_NOTHROW);

        ND_DEFINE_BUILDER_SET(instance);
        ND_DEFINE_BUILDER_SET(physicalDevice);
        ND_DEFINE_BUILDER_SET(device);
        ND_DEFINE_BUILDER_SET(swapchain);
        ND_DEFINE_BUILDER_SET(renderPass);
        ND_DEFINE_BUILDER_SET(swapchainImageView);
        ND_DEFINE_BUILDER_SET(swapchainFramebuffer);
        ND_DEFINE_BUILDER_SET(shaderModules);
        ND_DEFINE_BUILDER_SET(descriptorPool);
        ND_DEFINE_BUILDER_SET(descriptorSetLayoutObjects);
        ND_DEFINE_BUILDER_SET(pipelineCache);
        ND_DEFINE_BUILDER_SET(pipelineLayoutObjects);
        ND_DEFINE_BUILDER_SET(pipelineObjects);

        ND_DEFINE_BUILDER_OPERATOR(instance);
        ND_DEFINE_BUILDER_OPERATOR(physicalDevice);
        ND_DEFINE_BUILDER_OPERATOR(device);
        ND_DEFINE_BUILDER_OPERATOR(swapchain);
        ND_DEFINE_BUILDER_OPERATOR(renderPass);
        ND_DEFINE_BUILDER_OPERATOR(swapchainImageView);
        ND_DEFINE_BUILDER_OPERATOR(swapchainFramebuffer);
        ND_DEFINE_BUILDER_OPERATOR(shaderModules);
        ND_DEFINE_BUILDER_OPERATOR(descriptorPool);
        ND_DEFINE_BUILDER_OPERATOR(descriptorSetLayoutObjects);
        ND_DEFINE_BUILDER_OPERATOR(pipelineCache);
        ND_DEFINE_BUILDER_OPERATOR(pipelineLayoutObjects);
        ND_DEFINE_BUILDER_OPERATOR(pipelineObjects);

    private:
        ND_DECLARE_BUILDER_FIELD(instance);
        ND_DECLARE_BUILDER_FIELD(physicalDevice);
        ND_DECLARE_BUILDER_FIELD(device);
        ND_DECLARE_BUILDER_FIELD(swapchain);
        ND_DECLARE_BUILDER_FIELD(renderPass);
        ND_DECLARE_BUILDER_FIELD(swapchainImageView);
        ND_DECLARE_BUILDER_FIELD(swapchainFramebuffer);
        ND_DECLARE_BUILDER_FIELD(shaderModules);
        ND_DECLARE_BUILDER_FIELD(descriptorPool);
        ND_DECLARE_BUILDER_FIELD(descriptorSetLayoutObjects);
        ND_DECLARE_BUILDER_FIELD(pipelineCache);
        ND_DECLARE_BUILDER_FIELD(pipelineLayoutObjects);
        ND_DECLARE_BUILDER_FIELD(pipelineObjects);
    };
} // namespace nd::src::graphics::vulkan