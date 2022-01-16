#include "command_pool.hpp"
#include "tools.hpp"

namespace nd::src::graphics::vulkan
{
    using namespace nd::src::tools;

    VkCommandPoolCreateInfo
    getCommandPoolCreateInfo(const uint32_t queueFamilyIndex, const VkCommandPoolCreateFlags flags, const void* next) noexcept
    {
        ND_SET_SCOPE();

        return {
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, // sType;
            next,                                       // pNext;
            flags,                                      // flags;
            queueFamilyIndex                            // queueFamilyIndex;
        };
    }

    VkCommandPool
    getCommandPoolHandle(const VkCommandPoolCreateInfo& createInfo, const VkDevice device)
    {
        ND_SET_SCOPE();

        VkCommandPool commandPool;

        ND_ASSERT_EXEC(vkCreateCommandPool(device, &createInfo, nullptr, &commandPool) == VK_SUCCESS);

        return commandPool;
    }

    CommandPool
    getCommandPool(const CommandPoolConfiguration& configuration, const VkDevice device)
    {
        ND_SET_SCOPE();

        const auto createInfo = getCommandPoolCreateInfo(configuration.queueFamilyIndex, configuration.flags, configuration.next);

        return {configuration.queueFamilyIndex, configuration.queueCount, configuration.queueFlags, getCommandPoolHandle(createInfo, device)};
    }

    std::vector<CommandPool>
    getCommandPools(const std::vector<CommandPoolConfiguration>& configurations, const VkDevice device)
    {
        ND_SET_SCOPE();

        return getMapped<CommandPoolConfiguration, CommandPool>(configurations,
                                                                [device](const auto& configuration, const auto index)
                                                                {
                                                                    return getCommandPool(configuration, device);
                                                                });
    }
} // namespace nd::src::graphics::vulkan
