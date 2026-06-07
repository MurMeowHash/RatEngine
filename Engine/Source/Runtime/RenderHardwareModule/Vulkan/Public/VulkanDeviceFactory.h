#pragma once

#include "IVulkanDeviceFactory.h"
#include "Extensions/IVulkanExtensionsAssembler.h"

class DiContainer;

class VulkanDeviceFactory : public IVulkanDeviceFactory {
public:
    VulkanDeviceFactory(IVulkanExtensionsAssembler* vulkanExtensionsAssembler, DiContainer* diContainer);
    IVulkanDevice* CreateVulkanDevice(const vk::raii::PhysicalDevice &physicalDevice, vk::QueueFlags requestedQueues,
                                      bool* initializationSucceeded) override;
private:
    IVulkanExtensionsAssembler* m_vulkanExtensionsAssembler;
    DiContainer* m_diContainer;
};