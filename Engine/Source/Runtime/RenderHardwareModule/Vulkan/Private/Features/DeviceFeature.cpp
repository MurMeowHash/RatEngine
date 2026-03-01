#include "Features/DeviceFeature.h"

DeviceFeature::DeviceFeature(DeviceFeatureType featureType, bool required)
: m_featureType(featureType), m_required(required) { }

void DeviceFeature::MarkEnabled(bool enabled) {
    m_enabled = enabled;
}

bool DeviceFeature::IsEnabled() const {
    return m_enabled;
}

bool DeviceFeature::IsRequired() const {
    return m_required;
}

DeviceFeatureType DeviceFeature::GetFeatureType() const {
    return m_featureType;
}