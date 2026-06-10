#include "../Public/VulkanRHLProvider.h"
#include "BuildSettings/BuildSettings.h"
#include "CoreUtils.h"
#include "VulkanDevice.h"

using Rat::Core::Flags::operator|=;

VulkanRHLProvider::VulkanRHLProvider(IVulkanInstanceFactory* vulkanInstanceFactory, IVulkanDeviceFactory* vulkanDeviceFactory,
    IVulkanDeviceProvider* vulkanDeviceProvider, BuildSettings *buildSettings)
: m_vulkanInstanceFactory(vulkanInstanceFactory), m_vulkanDeviceFactory(vulkanDeviceFactory), m_vulkanDeviceProvider(vulkanDeviceProvider),
m_buildSettings(buildSettings) { }

bool VulkanRHLProvider::Initialize() {
    bool instanceInitialized = CreateVulkanInstance();
    if (!instanceInitialized)
        return false;

    bool deviceInitialized = CreateVulkanDevice();
    return deviceInitialized;
}

void VulkanRHLProvider::Shutdown() {
    delete m_vulkanDevice;
    delete m_vulkanInstance;
}

bool VulkanRHLProvider::CreateVulkanInstance() {
    InstanceCreationFlags instanceCreationFlags = InstanceCreationFlags::None;
    if (m_buildSettings->GetIsDevelopmentBuild())
        instanceCreationFlags |= InstanceCreationFlags::UseDebug;

    bool instanceInitializationSucceeded;
    m_vulkanInstance = m_vulkanInstanceFactory->CreateVulkanInstance(instanceCreationFlags, &instanceInitializationSucceeded);
    return instanceInitializationSucceeded;
}

bool VulkanRHLProvider::CreateVulkanDevice() {
    using Rat::Core::Flags::operator|;

    vk::raii::PhysicalDevice physicalDevice = nullptr;
    if(!m_vulkanDeviceProvider->TryFindVulkanDevice(m_vulkanInstance->GetHandle(), 0,
        DeviceSearchFlags::RenderingOnly | DeviceSearchFlags::AllowNonGpu, &physicalDevice))
        return false;

    bool deviceInitialized;
    m_vulkanDevice = m_vulkanDeviceFactory->CreateVulkanDevice(physicalDevice, vk::QueueFlagBits::eGraphics,
        VulkanMemoryProviderType::Default, &deviceInitialized);

    return deviceInitialized;
}