#include "../../Public/Memory/DefaultVulkanDeviceAllocator.h"

#include "Memory/VulkanMemoryCommon.h"

DefaultVulkanDeviceAllocator::DefaultVulkanDeviceAllocator(VulkanDevice* vulkanDevice,
                                                           const VulkanAllocationConfiguration& allocationConfiguration, uint32_t memoryTypeIndex)
: m_vulkanDevice(vulkanDevice), m_memoryTypeIndex(memoryTypeIndex), m_allocationConfiguration(allocationConfiguration) {
    InitializeMemoryTiers();
}

VulkanDeviceMemory DefaultVulkanDeviceAllocator::AllocateMemory(vk::DeviceSize memorySize, vk::DeviceSize alignment) {
    size_t allocationTierIndex = 0;
    VulkanDeviceMemory allocatedMemory;
    if (!TryFindAllocationTier(memorySize, allocationTierIndex))
        return allocatedMemory;

    for (VulkanMemoryPage& tierMemoryPage: m_memoryPool[allocationTierIndex]) {
        if (tierMemoryPage.TryAllocateFromRange(memorySize, alignment, allocatedMemory))
            return allocatedMemory;
    }

    VulkanAllocationTier allocationTier = m_allocationConfiguration.m_allocationTiers[allocationTierIndex];
    VulkanDeviceMemory allocatedPageMemory = Rat::VulkanMemoryCommon::AllocateDeviceMemory(m_vulkanDevice->GetInternalDevice(),
        allocationTier.m_pageSize, m_memoryTypeIndex);

    if (!allocatedPageMemory.IsValid())
        return allocatedMemory;

    VulkanMemoryPage& allocatedPage = m_memoryPool[allocationTierIndex].emplace_back(allocatedPageMemory);
    allocatedPage.TryAllocateFromRange(memorySize, alignment, allocatedPageMemory);
    return allocatedPageMemory;
}

void DefaultVulkanDeviceAllocator::FreeMemory(const VulkanDeviceMemory& memory) {
    if (memory.GetMemoryTypeIndex() != m_memoryTypeIndex)
        return;

    size_t allocationTierIndex = 0;
    if (!TryFindAllocationTier(memory.GetAllocationSize(), allocationTierIndex))
        return;

    auto pageToReturnMemory = std::ranges::find_if(m_memoryPool[allocationTierIndex],
        [&memory](const VulkanMemoryPage& memoryPage) {
            return memoryPage.GetPageMemory().GetHandle() == memory.GetHandle();
    });

    if (pageToReturnMemory == m_memoryPool[allocationTierIndex].end())
        return;

    pageToReturnMemory->ReturnMemory(memory);
}

void DefaultVulkanDeviceAllocator::InvalidateAllMemory() {
    for (std::vector<VulkanMemoryPage>& memoryPages : m_memoryPool) {
        for (VulkanMemoryPage& page: memoryPages) {
            page.InvalidateMemory();
        }
    }
}

void DefaultVulkanDeviceAllocator::FreeAllMemory() {
    for (std::vector<VulkanMemoryPage>& memoryPages : m_memoryPool) {
        for (const VulkanMemoryPage& page: memoryPages) {
            Rat::VulkanMemoryCommon::FreeDeviceMemory(m_vulkanDevice->GetInternalDevice(), page.GetPageMemory());
        }

        memoryPages.clear();
    }
}

void DefaultVulkanDeviceAllocator::InitializeMemoryTiers() {
    m_allocationConfiguration.OrderTiers();
    m_memoryPool.resize(m_allocationConfiguration.m_allocationTiers.size());
}

bool DefaultVulkanDeviceAllocator::TryFindAllocationTier(vk::DeviceSize memorySize, size_t &tierIndex) const {
    for (size_t i = 0; i < m_allocationConfiguration.m_allocationTiers.size(); i++) {
        if (memorySize <= m_allocationConfiguration.m_allocationTiers[i].m_maxAllowedAllocation) {
            tierIndex = i;
            return true;
        }
    }

    return false;
}