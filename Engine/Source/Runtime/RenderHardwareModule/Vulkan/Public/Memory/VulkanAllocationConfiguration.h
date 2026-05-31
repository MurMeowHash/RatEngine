#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <algorithm>

struct VulkanAllocationTier {
    vk::DeviceSize m_pageSize;
    vk::DeviceSize m_maxAllowedAllocation;
};

struct VulkanAllocationTierComparator {
    bool operator ()(const VulkanAllocationTier& lhs, const VulkanAllocationTier& rhs) const {
        return lhs.m_maxAllowedAllocation < rhs.m_maxAllowedAllocation;
    }
};

struct VulkanAllocationConfiguration {
    void OrderTiers() {
        std::ranges::sort(m_allocationTiers, VulkanAllocationTierComparator());
    }

    std::vector<VulkanAllocationTier> m_allocationTiers;
};