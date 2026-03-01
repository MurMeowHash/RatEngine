#pragma once

#include <vector>
#include "VulkanGlobals.h"
#include <vulkan/vulkan_raii.hpp>
#include "VulkanExtension.h"

class IVulkanExtensionsAssembler {
public:
    [[nodiscard]] virtual std::vector<const char*> GetRequestedInstanceExtensions(Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags flags) const = 0;
    [[nodiscard]] virtual std::vector<const char*> GetAvailableInstanceExtensions(const vk::raii::Context &vulkanContext,
                                                                                  Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags flags) const = 0;
    [[nodiscard]] virtual std::vector<VulkanExtension> GetDefaultDeviceExtensions() = 0;
    virtual ~IVulkanExtensionsAssembler() = default;
};