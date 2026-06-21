#pragma once

#include "Configurations/Extensions/VulkanExtensionsConfiguration.h"
#include <windows.h>
#include <vulkan/vulkan_win32.h>

struct WindowsVulkanExtensionsConfiguration : public VulkanExtensionsConfiguration {
    explicit WindowsVulkanExtensionsConfiguration() : VulkanExtensionsConfiguration() {
        m_instanceExtensions.emplace_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
    }
};