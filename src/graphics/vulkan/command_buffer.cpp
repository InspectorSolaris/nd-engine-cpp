#include "command_buffer.hpp"
#include "tools.hpp"

namespace nd::src::graphics::vulkan
{
    VkCommandBufferBeginInfo
    getCommandBufferBeginInfo(const VkCommandBufferInheritanceInfo* inheritanceInfo,
                              const VkCommandBufferUsageFlags       flags,
                              const void*                           next) noexcept
    {
        ND_SET_SCOPE();

        return {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, // sType;
            next,                                        // pNext;
            flags,                                       // flags;
            inheritanceInfo                              // pInheritanceInfo;
        };
    }

    VkCommandBufferAllocateInfo
    getCommandBufferAllocateInfo(const VkCommandPool        commandPool,
                                 const VkCommandBufferLevel level,
                                 const uint32_t             commandBufferCount,
                                 const void*                next) noexcept
    {
        ND_SET_SCOPE();

        return {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, // sType;
            next,                                           // pNext;
            commandPool,                                    // commandPool;
            level,                                          // level;
            commandBufferCount                              // commandBufferCount;
        };
    }

    std::vector<VkCommandBuffer>
    getCommandBuffer(const VkCommandBufferAllocateInfo& allocateInfo, const VkDevice device)
    {
        ND_SET_SCOPE();

        auto commandBuffers = std::vector<VkCommandBuffer>(allocateInfo.commandBufferCount);

        ND_ASSERT(vkAllocateCommandBuffers(device, &allocateInfo, commandBuffers.data()) == VK_SUCCESS);

        return commandBuffers;
    }

    std::vector<VkCommandBuffer>
    getCommandBuffer(const CommandBufferConfiguration& configuration, const VkDevice device)
    {
        ND_SET_SCOPE();

        const auto allocateInfo =
            getCommandBufferAllocateInfo(configuration.commandPool, configuration.level, configuration.count);

        return getCommandBuffer(allocateInfo, device);
    }
} // namespace nd::src::graphics::vulkan
