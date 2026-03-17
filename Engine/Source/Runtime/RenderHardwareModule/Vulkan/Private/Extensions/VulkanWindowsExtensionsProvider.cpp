#include "../../Public/Extensions/VulkanWindowsExtensionsProvider.h"
#include <windows.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

std::vector<const char *> VulkanWindowsExtensionsProvider::GetRequiredInstanceExtensions() {
    return std::vector<const char *> { VK_KHR_WIN32_SURFACE_EXTENSION_NAME };
}
