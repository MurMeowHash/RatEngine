#pragma once

#include "../../Resources/VulkanResourceType.h"
#include <unordered_map>

struct VulkanResourcesConfiguration {
    explicit VulkanResourcesConfiguration() {
        m_allowConcurrentAccessMap = {
            {VulkanResourceType::Image, true}
        };
    }

    [[nodiscard]] bool TryGetAllowConcurrentAccess(VulkanResourceType resourceType, bool& outAllowConcurrentAccess) {
        auto accessIterator = m_allowConcurrentAccessMap.find(resourceType);
        if (accessIterator == m_allowConcurrentAccessMap.end())
            return false;

        outAllowConcurrentAccess = accessIterator->second;
        return true;
    }

    std::unordered_map<VulkanResourceType, bool> m_allowConcurrentAccessMap;
};