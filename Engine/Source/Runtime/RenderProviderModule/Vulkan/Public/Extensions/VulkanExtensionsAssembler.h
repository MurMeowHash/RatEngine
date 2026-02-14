#pragma once

#include "IVulkanExtensionsAssembler.h"
#include "Extensions/IVulkanPlatformExtensionsProvider.h"

class VulkanExtensionsAssembler : public IVulkanExtensionsAssembler {
public:
    explicit VulkanExtensionsAssembler(IVulkanPlatformExtensionsProvider* vulkanPlatformExtensionsProvider);
    [[nodiscard]] std::vector<const char *> GetRequestedInstanceExtensions(Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags flags) const override;
    [[nodiscard]] std::vector<const char *> GetAvailableInstanceExtensions(const vk::raii::Context &vulkanContext,
                                                                           Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags flags) const override;
private:
    IVulkanPlatformExtensionsProvider* m_vulkanPlatformExtensionsProvider;
};