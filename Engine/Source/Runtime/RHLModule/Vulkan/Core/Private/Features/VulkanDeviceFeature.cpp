#include "Features/VulkanDeviceFeature.h"

VulkanDeviceFeature::VulkanDeviceFeature(VulkanDeviceFeatureType featureType)
: m_featureType(featureType) { }

void VulkanDeviceFeature::MarkEnabled(bool enabled) {
    m_enabled = enabled;
}

bool VulkanDeviceFeature::IsEnabled() const {
    return m_enabled;
}

VulkanDeviceFeatureType VulkanDeviceFeature::GetFeatureType() const {
    return m_featureType;
}