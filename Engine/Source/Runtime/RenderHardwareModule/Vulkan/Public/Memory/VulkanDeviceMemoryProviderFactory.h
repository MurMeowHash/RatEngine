#pragma once

#include "IVulkanDeviceMemoryProviderFactory.h"

class VulkanDeviceMemoryProviderFactory : public IVulkanDeviceMemoryProviderFactory {
public:
    IVulkanDeviceMemoryProvider* CreateVulkanDeviceMemoryProvider(VulkanMemoryProviderType memoryProviderType,
        vk::raii::Device &device, vk::raii::PhysicalDevice &physicalDevice, const VulkanAllocationConfiguration &vulkanAllocationConfiguration) override;
};