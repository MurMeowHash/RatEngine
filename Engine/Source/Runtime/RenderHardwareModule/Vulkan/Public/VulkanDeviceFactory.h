#pragma once

#include "IVulkanDeviceFactory.h"
#include "Extensions/IVulkanExtensionsAssembler.h"
#include "Features/IDeviceFeaturesAssembler.h"

class DiContainer;

class VulkanDeviceFactory : public IVulkanDeviceFactory {
public:
    VulkanDeviceFactory(IVulkanExtensionsAssembler* vulkanExtensionsAssembler, IDeviceFeaturesAssembler* deviceFeaturesAssembler,
                        const DiContainer* diContainer);
    IVulkanDevice* CreateVulkanDevice(const vk::raii::PhysicalDevice &physicalDevice, vk::QueueFlags requestedQueues,
                                      bool* initializationSucceeded) override;
private:
    IVulkanExtensionsAssembler* m_vulkanExtensionsAssembler;
    IDeviceFeaturesAssembler* m_deviceFeaturesAssembler;
    const DiContainer* m_diContainer;
};