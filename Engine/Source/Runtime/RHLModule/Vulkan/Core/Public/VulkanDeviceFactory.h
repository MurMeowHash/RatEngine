#pragma once

#include "IVulkanDeviceFactory.h"
#include "Configurations/Device/VulkanDeviceConfiguration.h"
#include "Configurations/Extensions/VulkanExtensionsConfiguration.h"

class DiContainer;

class VulkanDeviceFactory : public IVulkanDeviceFactory {
public:
    VulkanDeviceFactory(DiContainer* diContainer, VulkanDeviceConfiguration* vulkanDeviceConfiguration,
        VulkanExtensionsConfiguration* vulkanExtensionsConfiguration);
    VulkanDevice* CreateVulkanDevice(const VulkanDeviceInitializationInfo &deviceInitializationInfo,
        bool* initializationSucceeded) override;
    VulkanDevice* CreateVulkanDevice(vk::raii::PhysicalDevice& physicalDevice, vk::QueueFlags requestedQueues,
        VulkanMemoryProviderType memoryProviderType, bool *initializationSucceeded) override;
private:
    DiContainer* m_diContainer;
    VulkanDeviceConfiguration* m_vulkanDeviceConfiguration;
    VulkanExtensionsConfiguration* m_vulkanExtensionsConfiguration;
};