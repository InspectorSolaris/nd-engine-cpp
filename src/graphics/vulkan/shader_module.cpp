#include "shader_module.hpp"
#include "tools.hpp"

namespace nd::src::graphics::vulkan
{
    ShaderModule::ShaderModule() noexcept
    {
        ND_SET_SCOPE_LOW();
    }

    ShaderModule::ShaderModule(const VkDevice device, const VkShaderStageFlagBits stage, const CreateInfo& createInfo)
        : device_(device)
        , stage_(stage)
    {
        ND_SET_SCOPE_LOW();

        ND_ASSERT(vkCreateShaderModule(device_, &createInfo, nullptr, &shaderModule_) == VK_SUCCESS);
    }

    ShaderModule::ShaderModule(ShaderModule&& shaderModule) noexcept
        : device_(std::move(shaderModule.device_))
        , shaderModule_(std::move(shaderModule.shaderModule_))
        , stage_(std::move(shaderModule.stage_))
    {
        ND_SET_SCOPE_LOW();

        shaderModule.shaderModule_ = VK_NULL_HANDLE;
    }

    ShaderModule&
    ShaderModule::operator=(ShaderModule&& shaderModule) noexcept
    {
        ND_SET_SCOPE_LOW();

        if(&shaderModule == this)
        {
            return *this;
        }

        device_       = std::move(shaderModule.device_);
        shaderModule_ = std::move(shaderModule.shaderModule_);
        stage_        = std::move(shaderModule.stage_);

        shaderModule.shaderModule_ = VK_NULL_HANDLE;

        return *this;
    }

    ShaderModule::~ShaderModule()
    {
        ND_SET_SCOPE_LOW();

        vkDestroyShaderModule(device_, shaderModule_, nullptr);
    }

    ShaderModule::Code
    getShaderCode(const std::string& path)
    {
        ND_SET_SCOPE_LOW();

        ND_ASSERT(std::filesystem::exists(path));

        auto file = std::ifstream(path, std::ios::ate | std::ios::binary);

        ND_ASSERT(file);

        auto size = static_cast<size_t>(file.tellg());
        auto code = ShaderModule::Code(size);

        file.seekg(0);
        file.read(code.data(), size);

        return code;
    }

    ShaderModule::CreateInfo
    getShaderModuleCreateInfo(const size_t codeSize, const uint32_t* code) noexcept
    {
        ND_SET_SCOPE_LOW();

        return {
            VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, // sType;
            nullptr,                                     // pNext;
            0,                                           // flags;
            codeSize,                                    // codeSize;
            code                                         // pCode;
        };
    }

    ShaderModules
    getShaderModules(const ShaderModule::Configurations& configurations, const VkDevice device)
    {
        ND_SET_SCOPE_LOW();

        auto shaderModules = ShaderModules {};

        shaderModules.reserve(configurations.size());

        for(const auto configuration: configurations)
        {
            const auto code = getShaderCode(configuration.path);

            shaderModules.emplace_back(
                device,
                configuration.stage,
                getShaderModuleCreateInfo(code.size(), reinterpret_cast<const uint32_t*>(code.data())));
        }

        return shaderModules;
    }
} // namespace nd::src::graphics::vulkan
