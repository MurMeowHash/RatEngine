#pragma once

#include <vector>

namespace vk::raii {
    class Context;
}

class IVulkanExtensionsAssembler {
public:
    [[nodiscard]] virtual std::vector<const char*> GetRequestedInstanceExtensions() const = 0;
    [[nodiscard]] virtual std::vector<const char*> GetAvailableInstanceExtensions(const vk::raii::Context &vulkanContext) const = 0;
    virtual ~IVulkanExtensionsAssembler() = default;
};