#pragma once

#include "MemoryRange.h"
#include "VulkanDeviceMemory.h"
#include <vector>

using VulkanMemoryRange = MemoryRange<vk::DeviceSize>;
using VulkanRangeIteratorOffset = std::iter_difference_t<std::vector<VulkanMemoryRange>::iterator>;

struct VulkanMemoryRangeComparator {
    bool operator()(const VulkanMemoryRange& lhs, const VulkanMemoryRange& rhs) const {
        return lhs.GetBegin() < rhs.GetBegin();
    }
};

class VulkanMemoryPage {
public:
    explicit VulkanMemoryPage(const VulkanDeviceMemory& memory);

    [[nodiscard]] bool TryAllocateFromRange(vk::DeviceSize requiredMemorySize, vk::DeviceSize alignment, VulkanDeviceMemory& allocatedMemory);
    void ReturnMemory(const VulkanDeviceMemory& memory);
    [[nodiscard]] VulkanDeviceMemory GetPageMemory() const;
    void InvalidateMemory();

private:
    VulkanDeviceMemory m_memory;
    std::vector<VulkanMemoryRange> m_freeRanges;

    void MergeRangesForward(std::vector<VulkanMemoryRange>::iterator currentRange, VulkanRangeIteratorOffset neighborOffset);
    void MergeRangesBackward(std::vector<VulkanMemoryRange>::iterator currentRange, VulkanRangeIteratorOffset neighborOffset);
};
