#pragma once

#include "IVulkanPlatformExtensionsProvider.h"

class VulkanWindowsExtensionsProvider : public IVulkanPlatformExtensionsProvider {
public:
    std::vector<const char *> GetRequiredInstanceExtensions() override;
};