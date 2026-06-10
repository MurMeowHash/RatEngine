#pragma once

#include "IVulkanDeviceMemoryProviderFactory.h"
#include "../Configurations/Device/VulkanAllocationConfiguration.h"

class IPlatformInteractor;

class VulkanDeviceMemoryProviderFactory : public IVulkanDeviceMemoryProviderFactory {
public:
    VulkanDeviceMemoryProviderFactory(VulkanAllocationConfiguration* vulkanAllocationConfiguration, IPlatformInteractor* platformInteractor);
    IVulkanDeviceMemoryProvider* CreateVulkanDeviceMemoryProvider(VulkanMemoryProviderType memoryProviderType,
        vk::raii::Device &device, vk::raii::PhysicalDevice &physicalDevice) override;

private:
    VulkanAllocationConfiguration* m_vulkanAllocationConfiguration;
    IPlatformInteractor* m_platformInteractor;
};
