#pragma once

#include "IVulkanDedicatedDeviceAllocator.h"
#include "VulkanDevice.h"
#include "VulkanMemoryPage.h"

class DefaultVulkanDedicatedDeviceAllocator : public IVulkanDedicatedDeviceAllocator {
public:
    DefaultVulkanDedicatedDeviceAllocator(VulkanDevice* vulkanDevice, uint32_t memoryTypeIndex);

    VulkanDeviceMemory AllocateImageMemory(const vk::raii::Image& image) override;
    VulkanDeviceMemory AllocateBufferMemory(const vk::raii::Buffer& buffer) override;
    void FreeMemory(const VulkanDeviceMemory &memory) override;
    void FreeAllMemory() override;

private:
    VulkanDevice* m_vulkanDevice;
    uint32_t m_memoryTypeIndex;
    std::vector<VulkanMemoryPage> m_memoryPool;

    VulkanDeviceMemory TryAddPageForMemory(const VulkanDeviceMemory& memory);
};
