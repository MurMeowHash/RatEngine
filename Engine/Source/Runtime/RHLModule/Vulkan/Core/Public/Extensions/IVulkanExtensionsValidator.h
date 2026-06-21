#pragma once

#include <vector>
#include "VulkanExtension.h"
#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>
#include "IVulkanExtensible.h"

class IVulkanExtensionsValidator {
public:
    virtual void ValidateInstanceExtensions(const vk::raii::Context& context, std::vector<VulkanExtension>& requestedExtension) = 0;
    virtual void ValidateDeviceExtensions(const vk::raii::PhysicalDevice& physicalDevice, std::vector<VulkanExtension>& requestedExtension) = 0;
    virtual void ValidateExtensions(IVulkanExtensible* vulkanExtensible, std::vector<VulkanExtension>& requestedExtension) = 0;
    virtual ~IVulkanExtensionsValidator() = default;
};
