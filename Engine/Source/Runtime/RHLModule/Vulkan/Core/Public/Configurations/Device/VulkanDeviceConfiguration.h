#pragma once

#include <vector>
#include "../../Features/VulkanDeviceFeature.h"

struct VulkanDeviceConfiguration {
    explicit VulkanDeviceConfiguration() {
        m_requestedFeatures = {
            VulkanDeviceFeature(VulkanDeviceFeatureType::ShaderDrawParameters),
            VulkanDeviceFeature(VulkanDeviceFeatureType::DynamicRendering),
            VulkanDeviceFeature(VulkanDeviceFeatureType::Synchronization2)
        };
    }

    std::vector<VulkanDeviceFeature> m_requestedFeatures;
};