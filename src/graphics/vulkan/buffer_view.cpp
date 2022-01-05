#include "buffer_view.hpp"
#include "tools.hpp"

namespace nd::src::graphics::vulkan
{
    using namespace nd::src::tools;

    VkBufferViewCreateInfo
    getBufferViewCreateInfo(const VkBuffer                buffer,
                            const VkFormat                format,
                            const VkDeviceSize            offset,
                            const VkDeviceSize            range,
                            const VkBufferViewCreateFlags flags,
                            const void*                   next) noexcept
    {
        ND_SET_SCOPE();

        return {
            VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO, // sType;
            next,                                      // pNext;
            flags,                                     // flags;
            buffer,                                    // buffer;
            format,                                    // format;
            offset,                                    // offset;
            range                                      // range;
        };
    }

    VkBufferView
    getBufferViewHandle(const VkBufferViewCreateInfo& createInfo, const VkDevice device)
    {
        ND_SET_SCOPE();

        VkBufferView bufferView;

        ND_ASSERT_EXEC(vkCreateBufferView(device, &createInfo, nullptr, &bufferView) == VK_SUCCESS);

        return bufferView;
    }

    BufferView
    getBufferView(const BufferViewConfiguration& configuration, const VkDevice device)
    {
        ND_SET_SCOPE();

        const auto createInfo = getBufferViewCreateInfo(configuration.buffer,
                                                        configuration.format,
                                                        configuration.offset,
                                                        configuration.range,
                                                        configuration.flags,
                                                        configuration.next);

        return {getBufferViewHandle(createInfo, device)};
    }
} // namespace nd::src::graphics::vulkan
