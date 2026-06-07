#include "../../Public/Memory/VulkanDeviceMemoryProviderFactory.h"
#include "Memory/VulkanDeviceMemoryProvider.h"
#include <stdexcept>
#include "CoreUtils.h"

IVulkanDeviceMemoryProvider* VulkanDeviceMemoryProviderFactory::CreateVulkanDeviceMemoryProvider(VulkanMemoryProviderType memoryProviderType,
    vk::raii::Device &device, vk::raii::PhysicalDevice &physicalDevice, const VulkanAllocationConfiguration &vulkanAllocationConfiguration) {
    switch (memoryProviderType) {
        case VulkanMemoryProviderType::Default:
            return new VulkanDeviceMemoryProvider(device, physicalDevice, vulkanAllocationConfiguration);
        default:
            throw new std::invalid_argument(StringFormatter("Memory provider with type ", static_cast<uint32_t>(memoryProviderType), " does not exist"));
    }
}
