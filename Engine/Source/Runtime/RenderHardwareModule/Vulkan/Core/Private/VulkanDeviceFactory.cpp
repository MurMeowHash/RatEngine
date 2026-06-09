#include "VulkanDeviceFactory.h"
#include "VulkanDevice.h"
#include "DiContainer.h"

VulkanDeviceFactory::VulkanDeviceFactory(DiContainer *diContainer, VulkanDeviceConfiguration* vulkanDeviceConfiguration,
        VulkanExtensionsConfiguration* vulkanExtensionsConfiguration)
: m_diContainer(diContainer), m_vulkanDeviceConfiguration(vulkanDeviceConfiguration),
m_vulkanExtensionsConfiguration(vulkanExtensionsConfiguration) { }

VulkanDevice* VulkanDeviceFactory::CreateVulkanDevice(const VulkanDeviceInitializationInfo &deviceInitializationInfo,
    bool* initializationSucceeded) {
    VulkanDevice* vulkanDevice = m_diContainer->Instantiate<VulkanDevice>().WithArguments<IVulkanExtensionsValidator,
        IVulkanDeviceFeaturesAssembler, IVulkanDeviceMemoryProviderFactory>();
    bool initialized = vulkanDevice->Initialize(deviceInitializationInfo);
    if(initializationSucceeded != nullptr)
        *initializationSucceeded = initialized;

    return vulkanDevice;
}

VulkanDevice* VulkanDeviceFactory::CreateVulkanDevice(vk::raii::PhysicalDevice& physicalDevice, vk::QueueFlags requestedQueues,
        VulkanMemoryProviderType memoryProviderType, bool *initializationSucceeded) {
    VulkanDeviceInitializationInfo initializationInfo(physicalDevice);
    initializationInfo.m_requestedQueues = requestedQueues;
    initializationInfo.m_requestedExtensions = m_vulkanExtensionsConfiguration->m_deviceExtensions;
    initializationInfo.m_requestedFeatures = m_vulkanDeviceConfiguration->m_requestedFeatures;
    initializationInfo.m_memoryProviderType = memoryProviderType;

    return CreateVulkanDevice(initializationInfo, initializationSucceeded);
}
