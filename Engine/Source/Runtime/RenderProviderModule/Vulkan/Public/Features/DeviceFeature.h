#pragma once

#include "DeviceFeatureType.h"

class DeviceFeature {
public:
    DeviceFeature(DeviceFeatureType featureType, bool required);
    explicit DeviceFeature() = default;
    void MarkEnabled(bool enabled);
    [[nodiscard]] bool IsEnabled() const;
    [[nodiscard]] bool IsRequired() const;

    [[nodiscard]] DeviceFeatureType GetFeatureType() const;
private:
    DeviceFeatureType m_featureType = DeviceFeatureType::None;
    bool m_enabled = false;
    bool m_required = false;
};