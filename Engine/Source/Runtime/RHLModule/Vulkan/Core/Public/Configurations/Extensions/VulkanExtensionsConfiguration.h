#pragma once

#include <vector>
#include "../../Extensions/VulkanExtension.h"
#include <vulkan/vulkan.hpp>

struct VulkanExtensionsConfiguration {
    VulkanExtensionsConfiguration() {
        m_deviceExtensions = {
            VulkanExtension(vk::KHRSwapchainExtensionName),
            VulkanExtension(vk::KHRSpirv14ExtensionName),
            VulkanExtension(vk::KHRCreateRenderpass2ExtensionName),
            VulkanExtension(vk::KHRSynchronization2ExtensionName),
            VulkanExtension(vk::KHRDynamicRenderingExtensionName)
        };
        
        m_instanceExtensions = {
            VulkanExtension(vk::KHRSurfaceExtensionName),
            VulkanExtension(vk::EXTDebugUtilsExtensionName),
        };
    }

    std::vector<VulkanExtension> m_deviceExtensions;
    std::vector<VulkanExtension> m_instanceExtensions;
};