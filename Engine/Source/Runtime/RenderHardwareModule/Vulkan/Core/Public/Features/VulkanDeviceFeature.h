#pragma once

#include "VulkanDeviceFeatureType.h"

class VulkanDeviceFeature {
public:
    explicit VulkanDeviceFeature(VulkanDeviceFeatureType featureType);
    explicit VulkanDeviceFeature() = default;
    void MarkEnabled(bool enabled);
    [[nodiscard]] bool IsEnabled() const;

    [[nodiscard]] VulkanDeviceFeatureType GetFeatureType() const;
private:
    VulkanDeviceFeatureType m_featureType = VulkanDeviceFeatureType::None;
    bool m_enabled = false;
};