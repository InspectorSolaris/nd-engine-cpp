#pragma once

#include "pch.hpp"
#include "tools.hpp"

#include "objects_cfg.hpp"

namespace nd::src::graphics::vulkan
{
    class ObjectsCfgBuilder final
    {
    public:
        using Type    = ObjectsCfg;
        using Builder = ObjectsCfgBuilder;

        static Builder
        getDefault() noexcept(ND_ASSERT_NOTHROW)
        {
            return Builder {} << getInstanceCfg << getPhysicalDeviceCfg << getDeviceCfg << getBufferObjectsCfg << getSwapchainCfg << getRenderPassCfg
                              << getSwapchainImageViewCfg << getSwapchainFramebufferCfg << getDescriptorPoolCfg << getDescriptorSetLayoutObjectsCfg
                              << getShaderModulesCfg << getPipelineCacheCfg << getPipelineLayoutObjectsCfg << getPipelineObjectsCfg
                              << getCommandPoolObjectsCfg;
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
        ND_DEFINE_BUILDER_SET(buffer);
        ND_DEFINE_BUILDER_SET(swapchain);
        ND_DEFINE_BUILDER_SET(renderPass);
        ND_DEFINE_BUILDER_SET(swapchainImageView);
        ND_DEFINE_BUILDER_SET(swapchainFramebuffer);
        ND_DEFINE_BUILDER_SET(descriptorPool);
        ND_DEFINE_BUILDER_SET(descriptorSetLayout);
        ND_DEFINE_BUILDER_SET(shaderModules);
        ND_DEFINE_BUILDER_SET(pipelineCache);
        ND_DEFINE_BUILDER_SET(pipelineLayout);
        ND_DEFINE_BUILDER_SET(pipeline);
        ND_DEFINE_BUILDER_SET(commandPool);

        ND_DEFINE_BUILDER_OPERATOR(instance);
        ND_DEFINE_BUILDER_OPERATOR(physicalDevice);
        ND_DEFINE_BUILDER_OPERATOR(device);
        ND_DEFINE_BUILDER_OPERATOR(buffer);
        ND_DEFINE_BUILDER_OPERATOR(swapchain);
        ND_DEFINE_BUILDER_OPERATOR(renderPass);
        ND_DEFINE_BUILDER_OPERATOR(swapchainImageView);
        ND_DEFINE_BUILDER_OPERATOR(swapchainFramebuffer);
        ND_DEFINE_BUILDER_OPERATOR(descriptorPool);
        ND_DEFINE_BUILDER_OPERATOR(descriptorSetLayout);
        ND_DEFINE_BUILDER_OPERATOR(shaderModules);
        ND_DEFINE_BUILDER_OPERATOR(pipelineCache);
        ND_DEFINE_BUILDER_OPERATOR(pipelineLayout);
        ND_DEFINE_BUILDER_OPERATOR(pipeline);
        ND_DEFINE_BUILDER_OPERATOR(commandPool);

    private:
        ND_DECLARE_BUILDER_FIELD(instance);
        ND_DECLARE_BUILDER_FIELD(physicalDevice);
        ND_DECLARE_BUILDER_FIELD(device);
        ND_DECLARE_BUILDER_FIELD(buffer);
        ND_DECLARE_BUILDER_FIELD(swapchain);
        ND_DECLARE_BUILDER_FIELD(renderPass);
        ND_DECLARE_BUILDER_FIELD(swapchainImageView);
        ND_DECLARE_BUILDER_FIELD(swapchainFramebuffer);
        ND_DECLARE_BUILDER_FIELD(descriptorPool);
        ND_DECLARE_BUILDER_FIELD(descriptorSetLayout);
        ND_DECLARE_BUILDER_FIELD(shaderModules);
        ND_DECLARE_BUILDER_FIELD(pipelineCache);
        ND_DECLARE_BUILDER_FIELD(pipelineLayout);
        ND_DECLARE_BUILDER_FIELD(pipeline);
        ND_DECLARE_BUILDER_FIELD(commandPool);
    };
} // namespace nd::src::graphics::vulkan
