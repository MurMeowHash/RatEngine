#pragma once

#include "IVulkanPlatformExtensionsProvider.h"

class VulkanMockExtensionsProvider : public IVulkanPlatformExtensionsProvider {
public:
    std::vector<const char *> GetRequiredInstanceExtensions() override {
        return std::vector<const char*>();
    }
};