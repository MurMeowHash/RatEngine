#pragma once

#include <vector>
#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>

class IVulkanLayersValidator {
public:
    [[nodiscard]] virtual std::vector<const char*> ValidateLayers(const vk::raii::Context &vulkanContext,
        std::vector<const char*> requestedLayers, uint32_t& droppedLayersCount) = 0;
    virtual ~IVulkanLayersValidator() = default;
};