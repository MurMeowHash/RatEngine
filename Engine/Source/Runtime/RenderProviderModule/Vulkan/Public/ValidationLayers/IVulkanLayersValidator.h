#pragma once

#include <vector>

namespace vk::raii {
    class Context;
}

class IVulkanLayersValidator {
public:
    [[nodiscard]] virtual std::vector<const char*> ValidateLayers(const vk::raii::Context &vulkanContext, std::vector<const char*> requestedLayers) = 0;
    virtual ~IVulkanLayersValidator() = default;
};