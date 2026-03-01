#pragma once

#include <cstdint>
#include "DeviceFeature.h"
#include <vulkan/vulkan_raii.hpp>
#include <unordered_map>

struct DeviceFeaturesAssembleData {
    vk::PhysicalDeviceFeatures2 m_featuresChain;
    std::unordered_map<DeviceFeatureType, DeviceFeature> m_queryResult;

    vk::PhysicalDeviceVulkan11Features m_features11;
    vk::PhysicalDeviceVulkan13Features m_features13;
};

class IDeviceFeaturesAssembler {
public:
    [[nodiscard]] virtual DeviceFeaturesAssembleData AssembleDeviceFeatures(const vk::raii::PhysicalDevice& physicalDevice, uint32_t apiVersion) = 0;
    virtual ~IDeviceFeaturesAssembler() = default;
};