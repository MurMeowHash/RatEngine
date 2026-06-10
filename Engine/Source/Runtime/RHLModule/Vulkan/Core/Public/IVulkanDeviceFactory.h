#pragma once

#include "VulkanDevice.h"

class IVulkanDeviceFactory {
public:
    virtual VulkanDevice* CreateVulkanDevice(const VulkanDeviceInitializationInfo &deviceInitializationInfo,
        bool* initializationSucceeded) = 0;
    virtual VulkanDevice* CreateVulkanDevice(vk::raii::PhysicalDevice& physicalDevice, vk::QueueFlags requestedQueues,
        VulkanMemoryProviderType m_memoryProviderType, bool* initializationSucceeded) = 0;
    virtual ~IVulkanDeviceFactory() = default;
};
