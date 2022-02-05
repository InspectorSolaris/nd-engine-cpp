#pragma once

#include "pch.hpp"
#include "tools.hpp"

#include "objects.hpp"

namespace nd::src::graphics::vulkan
{
    struct Dependency final
    {
        str applicationName;
        str engineName;

        vec<str> layers;
        vec<str> extensions;

        u16 width;
        u16 height;
    };

    struct InstanceCfg final
    {
        str applicationName;
        str engineName;

        vec<str> layers;
        vec<str> extensions;

        u32 applicationVersion;
        u32 engineVersion;
        u32 apiVersion;

        void*                 instanceNext    = {};
        void*                 applicationNext = {};
        VkInstanceCreateFlags flags           = {};
    };

    struct PhysicalDeviceCfg final
    {
        VkPhysicalDeviceFeatures features;

        func<u64(const VkPhysicalDeviceFeatures&, const VkPhysicalDeviceProperties&)> priority;

        vec<str> extensions;

        VkQueueFlags queueFlags;
    };

    struct DeviceMemoryCfg final
    {
        VkDeviceSize          size;
        VkMemoryPropertyFlags propertyFlags;
        VkMemoryPropertyFlags propertyFlagsNot;

        void* next = {};
    };

    struct QueueFamilyCfg final
    {
        VkQueueFlags queueFlags;
        VkQueueFlags queueFlagsNot;
    };

    struct DeviceMemoryPoolCfg final
    {
        DeviceMemoryCfg device;
        DeviceMemoryCfg host;
    };

    struct QueueFamilyPoolCfg final
    {
        QueueFamilyCfg graphics;
        QueueFamilyCfg transfer;
        QueueFamilyCfg compute;
    };

    struct DeviceCfg final
    {
        VkPhysicalDeviceFeatures features;

        DeviceMemoryPoolCfg memoryPool;
        QueueFamilyPoolCfg  queueFamilyPool;

        vec<str> extensions;

        VkQueueFlags queueFlags;

        void*               next  = {};
        VkDeviceCreateFlags flags = {};
    };

    struct SwapchainCfg final
    {
        const QueueFamilyPool& queueFamilyPool;

        VkPhysicalDevice physicalDevice;
        VkSurfaceKHR     surface;

        VkExtent2D imageExtent;

        u32               imageCount;
        u32               imageArrayLayers;
        VkFormat          imageFormat;
        VkColorSpaceKHR   imageColorSpace;
        VkImageUsageFlags imageUsage;
        VkSharingMode     imageSharingMode;

        VkSurfaceTransformFlagBitsKHR transform;
        VkCompositeAlphaFlagBitsKHR   compositeAlpha;
        VkPresentModeKHR              presentMode;

        bool clipped;

        void*                     next  = {};
        VkSwapchainCreateFlagsKHR flags = {};
    };

    using AttachmentDescription = VkAttachmentDescription;
    using SubpassDependency     = VkSubpassDependency;

    struct SubpassDescription final
    {
        vec<VkAttachmentReference> inputAttachments;
        vec<VkAttachmentReference> colorAttachments;
        vec<VkAttachmentReference> resolveAttachments;
        vec<VkAttachmentReference> depthStencilAttachments;

        vec<u32> preserveAttachments;

        VkPipelineBindPoint       pipelineBindPoint;
        VkSubpassDescriptionFlags flags;
    };

    struct RenderPassCfg final
    {
        vec<AttachmentDescription> attachmentDescriptions;
        vec<SubpassDescription>    subpassDescriptions;
        vec<SubpassDependency>     subpassDependencies;

        void*                   next  = {};
        VkRenderPassCreateFlags flags = {};
    };

    struct ImageCfg final
    {
    };

    struct ImageViewCfg final
    {
        VkImageSubresourceRange subresourceRange;
        VkComponentMapping      components;
        VkImageViewType         type;
        VkFormat                format;

        void*                  next  = {};
        VkImageViewCreateFlags flags = {};
    };

    struct FramebufferCfg final
    {
        VkRenderPass renderPass;

        u16 width;
        u16 height;
        u16 layers;

        void*                    next  = {};
        VkFramebufferCreateFlags flags = {};
    };

    struct ShaderModuleCfg final
    {
        str path;

        VkShaderStageFlagBits stage;

        void*                     next  = {};
        VkShaderModuleCreateFlags flags = {};
    };

    struct DescriptorSetLayoutCfg final
    {
        void*                            next  = {};
        VkDescriptorSetLayoutCreateFlags flags = {};
    };

    struct DescriptorSetLayoutPoolCfg final
    {
        DescriptorSetLayoutCfg mesh;
    };

    struct PipelineCacheCfg final
    {
        void*                      next  = {};
        VkPipelineCacheCreateFlags flags = {};
    };

    struct PipelineLayoutCfg final
    {
        vec<VkDescriptorSetLayout> descriptorSetLayouts;
        vec<VkPushConstantRange>   pushConstantRanges;

        void*                       next  = {};
        VkPipelineLayoutCreateFlags flags = {};
    };

    struct PipelineLayoutPoolCfg final
    {
        PipelineLayoutCfg mesh;
    };

    struct PipelineVertexInputStateCreateInfo final
    {
        vec<VkVertexInputBindingDescription>   bindings;
        vec<VkVertexInputAttributeDescription> attributes;

        void*                                 next  = {};
        VkPipelineVertexInputStateCreateFlags flags = {};
    };

    struct PipelineViewportStateCreateInfo final
    {
        vec<VkViewport> viewports;
        vec<VkRect2D>   scissors;

        void*                              next  = {};
        VkPipelineViewportStateCreateFlags flags = {};
    };

    struct PipelineColorBlendStateCreateInfo final
    {
        vec<VkPipelineColorBlendAttachmentState> attachments;
        arr<f32, 4>                              blendConstants;

        VkBool32  logicOpEnable;
        VkLogicOp logicOp;

        void*                                next  = {};
        VkPipelineColorBlendStateCreateFlags flags = {};
    };

    struct PipelineDynamicStateCreateInfo final
    {
        vec<VkDynamicState> dynamicStates;

        void*                             next  = {};
        VkPipelineDynamicStateCreateFlags flags = {};
    };

    using PipelineInputAssemblyStateCreateInfo = VkPipelineInputAssemblyStateCreateInfo;
    using PipelineTessellationStateCreateInfo  = VkPipelineTessellationStateCreateInfo;
    using PipelineRasterizationStateCreateInfo = VkPipelineRasterizationStateCreateInfo;
    using PipelineMultisampleStateCreateInfo   = VkPipelineMultisampleStateCreateInfo;
    using PipelineDepthStencilStateCreateInfo  = VkPipelineDepthStencilStateCreateInfo;

    struct GraphicsPipelineCfg final
    {
        PipelineDepthStencilStateCreateInfo  depthStencil;
        PipelineVertexInputStateCreateInfo   vertexInput;
        PipelineViewportStateCreateInfo      viewport;
        PipelineRasterizationStateCreateInfo rasterization;
        PipelineColorBlendStateCreateInfo    colorBlend;
        PipelineMultisampleStateCreateInfo   multisample;
        PipelineDynamicStateCreateInfo       dynamicState;
        PipelineInputAssemblyStateCreateInfo inputAssembly;
        PipelineTessellationStateCreateInfo  tessellation;

        vec<VkPipelineShaderStageCreateInfo> stages;

        VkPipelineLayout layout;
        VkRenderPass     renderPass;

        u32 subpass;

        void*                 next  = {};
        VkPipelineCreateFlags flags = {};
    };

    struct PipelinePoolCfg final
    {
        GraphicsPipelineCfg mesh;
    };

    InstanceCfg getInstanceCfg(opt<const Dependency>::ref) noexcept(ND_ASSERT_NOTHROW);

    PhysicalDeviceCfg
    getPhysicalDeviceCfg() noexcept(ND_ASSERT_NOTHROW);

    DeviceCfg getDeviceCfg(opt<const PhysicalDeviceCfg>::ref) noexcept(ND_ASSERT_NOTHROW);

    SwapchainCfg getSwapchainCfg(opt<const Dependency>::ref,
                                 opt<const PhysicalDevice>::ref,
                                 opt<const Device>::ref,
                                 opt<const Surface>::ref) noexcept(ND_ASSERT_NOTHROW);

    RenderPassCfg getRenderPassCfg(opt<const SwapchainCfg>::ref) noexcept(ND_ASSERT_NOTHROW);

    ImageViewCfg getSwapchainImageViewCfg(opt<const SwapchainCfg>::ref) noexcept(ND_ASSERT_NOTHROW);

    FramebufferCfg getSwapchainFramebufferCfg(opt<const SwapchainCfg>::ref, opt<const RenderPass>::ref) noexcept(ND_ASSERT_NOTHROW);

    vec<ShaderModuleCfg>
    getShaderModuleCfgs() noexcept(ND_ASSERT_NOTHROW);

    DescriptorSetLayoutPoolCfg
    getDescriptorSetLayoutPoolCfg() noexcept(ND_ASSERT_NOTHROW);

    PipelineCacheCfg
    getPipelineCacheCfg() noexcept(ND_ASSERT_NOTHROW);

    PipelineLayoutPoolCfg getPipelineLayoutPoolCfg(opt<const DescriptorSetLayoutPool>::ref) noexcept(ND_ASSERT_NOTHROW);

    PipelinePoolCfg getPipelinePoolCfg(opt<const RenderPass>::ref, opt<const PipelineLayoutPool>::ref) noexcept(ND_ASSERT_NOTHROW);

    struct VulkanObjectsCfg final
    {
        using InstanceCfgInit             = rm_noexcept<decltype(getInstanceCfg)>;
        using PhysicalDeviceCfgInit       = rm_noexcept<decltype(getPhysicalDeviceCfg)>;
        using DeviceCfgInit               = rm_noexcept<decltype(getDeviceCfg)>;
        using SwapchainCfgInit            = rm_noexcept<decltype(getSwapchainCfg)>;
        using RenderPassCfgInit           = rm_noexcept<decltype(getRenderPassCfg)>;
        using SwapchainImageViewCfgInit   = rm_noexcept<decltype(getSwapchainImageViewCfg)>;
        using SwapchainFramebufferCfgInit = rm_noexcept<decltype(getSwapchainFramebufferCfg)>;
        using ShaderModuleCfgsInit        = rm_noexcept<decltype(getShaderModuleCfgs)>;
        using PipelineCacheCfgInit        = rm_noexcept<decltype(getPipelineCacheCfg)>;

        func<InstanceCfgInit>             instance;
        func<PhysicalDeviceCfgInit>       physicalDevice;
        func<DeviceCfgInit>               device;
        func<SwapchainCfgInit>            swapchain;
        func<RenderPassCfgInit>           renderPass;
        func<SwapchainImageViewCfgInit>   swapchainImageView;
        func<SwapchainFramebufferCfgInit> swapchainFramebuffer;
        func<ShaderModuleCfgsInit>        shaderModules;
        func<PipelineCacheCfgInit>        pipelineCache;
    };
} // namespace nd::src::graphics::vulkan
