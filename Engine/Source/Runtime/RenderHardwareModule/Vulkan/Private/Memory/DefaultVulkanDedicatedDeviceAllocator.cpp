#include "../../Public/Memory/DefaultVulkanDedicatedDeviceAllocator.h"
#include "Memory/VulkanMemoryCommon.h"

DefaultVulkanDedicatedDeviceAllocator::DefaultVulkanDedicatedDeviceAllocator(VulkanDevice *vulkanDevice, uint32_t memoryTypeIndex)
: m_vulkanDevice(vulkanDevice), m_memoryTypeIndex(memoryTypeIndex) { }

VulkanDeviceMemory DefaultVulkanDedicatedDeviceAllocator::AllocateImageMemory(const vk::raii::Image &image) {
    VulkanDeviceMemory allocatedMemory = Rat::VulkanMemoryCommon::AllocateDedicatedImageMemory(m_vulkanDevice->GetInternalDevice(), image, m_memoryTypeIndex);
    return TryAddPageForMemory(allocatedMemory);
}

VulkanDeviceMemory DefaultVulkanDedicatedDeviceAllocator::AllocateBufferMemory(const vk::raii::Buffer &buffer) {
    VulkanDeviceMemory allocatedMemory = Rat::VulkanMemoryCommon::AllocateDedicatedBufferMemory(m_vulkanDevice->GetInternalDevice(), buffer, m_memoryTypeIndex);
    return TryAddPageForMemory(allocatedMemory);
}

void DefaultVulkanDedicatedDeviceAllocator::FreeMemory(const VulkanDeviceMemory &memory) {
    std::erase_if(m_memoryPool, [&memory](const VulkanMemoryPage& memoryPage) {
        return memoryPage.GetPageMemory().GetHandle() == memory.GetHandle();
    });

    Rat::VulkanMemoryCommon::FreeDeviceMemory(m_vulkanDevice->GetInternalDevice(), memory);
}

void DefaultVulkanDedicatedDeviceAllocator::FreeAllMemory() {
    for (const VulkanMemoryPage& memoryPage: m_memoryPool) {
        Rat::VulkanMemoryCommon::FreeDeviceMemory(m_vulkanDevice->GetInternalDevice(), memoryPage.GetPageMemory());
    }

    m_memoryPool.clear();
}

VulkanDeviceMemory DefaultVulkanDedicatedDeviceAllocator::TryAddPageForMemory(const VulkanDeviceMemory &memory) {
    if (!memory.IsValid())
        return memory;

    VulkanMemoryPage& dedicatedMemoryPage = m_memoryPool.emplace_back(memory);
    return dedicatedMemoryPage.GetPageMemory();
}
