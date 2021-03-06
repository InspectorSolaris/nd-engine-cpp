#include "image_init.hpp"
#include "tools_runtime.hpp"

namespace nd::src::graphics::vulkan
{
    using namespace nd::src::tools;

    ImageView
    createImageView(opt<const ImageViewCfg>::ref cfg, const VkDevice device, const VkImage image) noexcept(ND_VK_ASSERT_NOTHROW)
    {
        ND_SET_SCOPE();

        const auto createInfo = VkImageViewCreateInfo {.sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                                                       .pNext            = cfg.next,
                                                       .flags            = cfg.flags,
                                                       .image            = image,
                                                       .viewType         = cfg.type,
                                                       .format           = cfg.format,
                                                       .components       = cfg.components,
                                                       .subresourceRange = cfg.subresourceRange};

        VkImageView imageView;

        ND_VK_ASSERT(vkCreateImageView(device, &createInfo, ND_VK_ALLOCATION_CALLBACKS, &imageView));

        return imageView;
    }

    Framebuffer
    createFramebuffer(opt<const FramebufferCfg>::ref cfg, const VkDevice device, const vec<VkImageView>& imageViews) noexcept(ND_VK_ASSERT_NOTHROW)
    {
        ND_SET_SCOPE();

        const auto createInfo = VkFramebufferCreateInfo {.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                                                         .pNext           = cfg.next,
                                                         .flags           = cfg.flags,
                                                         .renderPass      = cfg.renderPass,
                                                         .attachmentCount = static_cast<u32>(imageViews.size()),
                                                         .pAttachments    = imageViews.data(),
                                                         .width           = static_cast<u32>(cfg.width),
                                                         .height          = static_cast<u32>(cfg.height),
                                                         .layers          = static_cast<u32>(cfg.layers)};

        VkFramebuffer framebuffer;

        ND_VK_ASSERT(vkCreateFramebuffer(device, &createInfo, ND_VK_ALLOCATION_CALLBACKS, &framebuffer));

        return framebuffer;
    }
} // namespace nd::src::graphics::vulkan
