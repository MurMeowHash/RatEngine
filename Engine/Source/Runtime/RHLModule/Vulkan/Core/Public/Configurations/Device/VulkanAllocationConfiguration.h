#pragma once

#include <unordered_map>
#include "VulkanAllocationPreset.h"
#include "PlatformInteractors/PlatformRuntimeData.h"

struct VulkanAllocationConfiguration {
    explicit VulkanAllocationConfiguration() {
        m_allocationPresets = {
            {PlatformCategory::Desktop, DesktopVulkanAllocationPresetDefinition()}
        };
    }

    [[nodiscard]] bool TryGetAllocationPresetDefinition(PlatformCategory platformCategory, VulkanAllocationPresetDefinition& vulkanAllocationPresetDefinition) const {
        auto allocationPresetIterator = m_allocationPresets.find(platformCategory);
        if (allocationPresetIterator == m_allocationPresets.end())
            return false;

        vulkanAllocationPresetDefinition = allocationPresetIterator->second;
        return true;
    }

    std::unordered_map<PlatformCategory, VulkanAllocationPresetDefinition> m_allocationPresets;
};