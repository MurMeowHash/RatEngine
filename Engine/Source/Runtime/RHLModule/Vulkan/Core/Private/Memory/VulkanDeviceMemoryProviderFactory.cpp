#include "../../Public/Memory/VulkanDeviceMemoryProviderFactory.h"
#include "Memory/VulkanDeviceMemoryProvider.h"
#include <stdexcept>
#include "CoreUtils.h"
#include "PlatformInteractors/IPlatformInteractor.h"

VulkanDeviceMemoryProviderFactory::VulkanDeviceMemoryProviderFactory(VulkanAllocationConfiguration* vulkanAllocationConfiguration,
    IPlatformInteractor *platformInteractor)
: m_vulkanAllocationConfiguration(vulkanAllocationConfiguration), m_platformInteractor(platformInteractor) {
}

IVulkanDeviceMemoryProvider* VulkanDeviceMemoryProviderFactory::CreateVulkanDeviceMemoryProvider(VulkanMemoryProviderType memoryProviderType,
    vk::raii::Device &device, vk::raii::PhysicalDevice &physicalDevice) {
    switch (memoryProviderType) {
        case VulkanMemoryProviderType::Default:
            {
                VulkanAllocationPresetDefinition vulkanAllocationPresetDefinition;
                bool retrievedAllocationPreset = m_vulkanAllocationConfiguration->TryGetAllocationPresetDefinition(
                    m_platformInteractor->GetPlatformRuntimeData().m_platformCategory, vulkanAllocationPresetDefinition);
                assert(retrievedAllocationPreset);
                return new VulkanDeviceMemoryProvider(device, physicalDevice, vulkanAllocationPresetDefinition);
            }
        default:
            throw std::invalid_argument(StringFormatter("Memory provider with type ", static_cast<uint32_t>(memoryProviderType), " does not exist"));
    }
}