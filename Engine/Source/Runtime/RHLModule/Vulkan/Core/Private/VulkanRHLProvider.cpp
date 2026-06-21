#include "../Public/VulkanRHLProvider.h"
#include "BuildSettings/BuildSettings.h"
#include "CoreUtils.h"
#include "VulkanDevice.h"
#include "Resources/VulkanRHLTexture.h"

using Rat::Core::Flags::operator|=;

VulkanRHLProvider::VulkanRHLProvider(IVulkanInstanceFactory* vulkanInstanceFactory, IVulkanDeviceFactory* vulkanDeviceFactory,
    IVulkanDeviceProvider* vulkanDeviceProvider, BuildSettings *buildSettings, RatVulkanMapperInitializer* ratVulkanMapperInitializer)
: m_vulkanInstanceFactory(vulkanInstanceFactory), m_vulkanDeviceFactory(vulkanDeviceFactory), m_vulkanDeviceProvider(vulkanDeviceProvider),
m_buildSettings(buildSettings), m_ratVulkanMapperInitializer(ratVulkanMapperInitializer) { }

bool VulkanRHLProvider::Initialize() {
    m_ratVulkanMapperInitializer->CreateMapping();

    bool instanceInitialized = CreateVulkanInstance();
    if (!instanceInitialized)
        return false;

    bool deviceInitialized = CreateVulkanDevice();
    return deviceInitialized;
}

void VulkanRHLProvider::Shutdown() {
    m_ratVulkanMapperInitializer->DestroyMapping();
    delete m_vulkanDevice;
    delete m_vulkanInstance;
}

IRHLTexture* VulkanRHLProvider::CreateTexture(const RHLTextureCreateInfo &createInfo) {

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