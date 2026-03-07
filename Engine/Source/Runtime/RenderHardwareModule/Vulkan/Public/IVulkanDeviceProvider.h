#pragma once

#include "VulkanGlobals.h"
#include <vulkan/vulkan_raii.hpp>

using DeviceSearchFlags = Rat::RenderProviderModule::Vulkan::DeviceSearchFlags;

class IVulkanDeviceProvider {
public:
    [[nodiscard]] virtual bool TryFindVulkanDevice(const vk::raii::Instance &vkInstance, uint64_t predefinedDeviceId,
                                                   DeviceSearchFlags flags, vk::raii::PhysicalDevice *physicalDevice) const = 0;
    [[nodiscard]] virtual uint64_t GetDeviceIdByName(const vk::raii::Instance &vkInstance, const char* physicalDeviceName) const = 0;
    virtual ~IVulkanDeviceProvider() = default;
};