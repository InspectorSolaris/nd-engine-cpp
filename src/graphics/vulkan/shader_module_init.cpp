#include "shader_module_init.hpp"
#include "tools_runtime.hpp"

namespace nd::src::graphics::vulkan
{
    using namespace nd::src::tools;

    vec<char>
    getShaderModuleCode(const str& path) noexcept(ND_ASSERT_NOTHROW)
    {
        ND_SET_SCOPE();

        ND_ASSERT(std::filesystem::exists(path));

        auto file = std::ifstream(path, std::ios::ate | std::ios::binary);

        ND_ASSERT(file);

        auto size = static_cast<u64>(file.tellg());
        auto code = vec<char>(size);

        file.seekg(0);
        file.read(code.data(), size);

        return code;
    }

    ShaderModule
    createShaderModule(opt<const ShaderModuleCfg>::ref cfg, const VkDevice device) noexcept(ND_VK_ASSERT_NOTHROW)
    {
        ND_SET_SCOPE();

        const auto code = getShaderModuleCode(cfg.path);

        const auto createInfo = VkShaderModuleCreateInfo {.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
                                                          .pNext    = cfg.next,
                                                          .flags    = cfg.flags,
                                                          .codeSize = static_cast<u32>(code.size()),
                                                          .pCode    = reinterpret_cast<const u32*>(code.data())};

        VkShaderModule shaderModule;

        ND_VK_ASSERT(vkCreateShaderModule(device, &createInfo, ND_VK_ALLOCATION_CALLBACKS, &shaderModule));

        return {.stage = cfg.stage, .handle = shaderModule};
    }

    vec<ShaderModule>
    createShaderModules(const vec<ShaderModuleCfg>& cfg, const VkDevice device) noexcept(ND_VK_ASSERT_NOTHROW)
    {
        ND_SET_SCOPE();

        return getMapped<ShaderModuleCfg, ShaderModule>(cfg,
                                                        [device](const auto& cfg, const auto index)
                                                        {
                                                            return createShaderModule(cfg, device);
                                                        });
    }
} // namespace nd::src::graphics::vulkan
