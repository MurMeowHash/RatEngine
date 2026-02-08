#pragma once

#include "IVulkanExtensionsAssembler.h"
#include "Extensions/IVulkanPlatformExtensionsProvider.h"

class BuildSettings;

class VulkanExtensionsAssembler : public IVulkanExtensionsAssembler {
public:
    VulkanExtensionsAssembler(IVulkanPlatformExtensionsProvider* vulkanPlatformExtensionsProvider, BuildSettings* buildSettings);
    [[nodiscard]] std::vector<const char *> GetRequestedInstanceExtensions() const override;
    [[nodiscard]] std::vector<const char *> GetAvailableInstanceExtensions(const vk::raii::Context &vulkanContext) const override;
private:
    IVulkanPlatformExtensionsProvider* m_vulkanPlatformExtensionsProvider;
    BuildSettings* m_buildSettings;
};