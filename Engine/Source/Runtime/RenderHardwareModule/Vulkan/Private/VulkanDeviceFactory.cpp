#include "VulkanDeviceFactory.h"
#include "DiContainer.h"
#include "VulkanDevice.h"

VulkanDeviceFactory::VulkanDeviceFactory(IVulkanExtensionsAssembler* vulkanExtensionsAssembler, IDeviceFeaturesAssembler* deviceFeaturesAssembler,
                                         const DiContainer* diContainer)
: m_vulkanExtensionsAssembler(vulkanExtensionsAssembler), m_deviceFeaturesAssembler(deviceFeaturesAssembler), m_diContainer(diContainer) { }

IVulkanDevice *VulkanDeviceFactory::CreateVulkanDevice(const vk::raii::PhysicalDevice &physicalDevice, vk::QueueFlags requestedQueues,
                                                       bool* initializationSucceeded) {
    IVulkanDevice* vulkanDevice = new VulkanDevice(m_deviceFeaturesAssembler);
    bool initialized = vulkanDevice->Initialize(physicalDevice, requestedQueues, m_vulkanExtensionsAssembler->GetDefaultDeviceExtensions());
    if(initializationSucceeded != nullptr)
        *initializationSucceeded = initialized;

    return vulkanDevice;
}
