#pragma once

#include <vector>

class IVulkanPlatformExtensionsProvider {
public:
    [[nodiscard]] virtual std::vector<const char*> GetRequiredInstanceExtensions() = 0;
    virtual ~IVulkanPlatformExtensionsProvider() = default;
};