#pragma once

#include "VulkanExtension.h"
#include <vector>
#include <vulkan/vulkan.hpp>

class IVulkanExtensible {
public:
    [[nodiscard]] virtual bool IsExtensionSupported(const char* extensionName) const = 0;
    [[nodiscard]] virtual bool IsExtensionSupported(VulkanExtension::EncodingType extensionEncoding) const = 0;
    [[nodiscard]] virtual bool TryGetAvailableExtensions(std::vector<vk::ExtensionProperties>& availableExtensions) const = 0;
    [[nodiscard]] virtual std::vector<const char *> GetSupportedExtensionNames() const = 0;
    virtual ~IVulkanExtensible() = default;
};