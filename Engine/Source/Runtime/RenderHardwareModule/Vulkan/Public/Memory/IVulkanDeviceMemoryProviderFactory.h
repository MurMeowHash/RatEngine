#pragma once

#include "IVulkanDeviceMemoryProvider.h"
#include "VulkanAllocationConfiguration.h"
#include "VulkanMemoryProviderType.h"

class IVulkanDeviceMemoryProviderFactory {
public:
    virtual IVulkanDeviceMemoryProvider* CreateVulkanDeviceMemoryProvider(VulkanMemoryProviderType memoryProviderType,
        vk::raii::Device &device, vk::raii::PhysicalDevice &physicalDevice, const VulkanAllocationConfiguration &vulkanAllocationConfiguration) = 0;
    virtual ~IVulkanDeviceMemoryProviderFactory() = default;
};
