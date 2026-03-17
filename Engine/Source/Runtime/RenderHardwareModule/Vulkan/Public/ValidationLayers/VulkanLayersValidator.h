#pragma once

#include "IVulkanLayersValidator.h"

class VulkanLayersValidator : public IVulkanLayersValidator {
public:
    std::vector<const char *> ValidateLayers(const vk::raii::Context &vulkanContext, std::vector<const char *> requestedLayers) override;
};