#pragma once

#include "IVulkanDeviceAllocator.h"
#include "VulkanDevice.h"
#include "VulkanMemoryPage.h"
#include "VulkanAllocationConfiguration.h"

class DefaultVulkanDeviceAllocator : public IVulkanDeviceAllocator {
public:
    DefaultVulkanDeviceAllocator(VulkanDevice* vulkanDevice, const VulkanAllocationConfiguration& allocationConfiguration, uint32_t memoryTypeIndex);

    VulkanDeviceMemory AllocateMemory(vk::DeviceSize memorySize, vk::DeviceSize alignment) override;
    void FreeMemory(const VulkanDeviceMemory& memory) override;
    void InvalidateAllMemory() override;
    void FreeAllMemory() override;

private:
    VulkanDevice* m_vulkanDevice;
    uint32_t m_memoryTypeIndex;
    VulkanAllocationConfiguration m_allocationConfiguration;
    std::vector<std::vector<VulkanMemoryPage>> m_memoryPool;

    void InitializeMemoryTiers();
    [[nodiscard]] bool TryFindAllocationTier(vk::DeviceSize memorySize, size_t& tierIndex) const;
};