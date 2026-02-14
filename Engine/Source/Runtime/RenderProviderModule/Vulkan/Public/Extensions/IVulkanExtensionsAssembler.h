#pragma once

#include <vector>
#include "ExtensionAssembleFlags.h"

namespace vk::raii {
    class Context;
}

class IVulkanExtensionsAssembler {
public:
    [[nodiscard]] virtual std::vector<const char*> GetRequestedInstanceExtensions(Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags flags) const = 0;
    [[nodiscard]] virtual std::vector<const char*> GetAvailableInstanceExtensions(const vk::raii::Context &vulkanContext,
                                                                                  Rat::RenderProviderModule::Vulkan::ExtensionAssembleFlags flags) const = 0;
    virtual ~IVulkanExtensionsAssembler() = default;
};