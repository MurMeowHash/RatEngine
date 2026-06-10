#pragma once

#include "VulkanDeviceFeature.h"
#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>
#include <unordered_map>

struct VulkanDeviceFeaturesAssembleData {
    vk::PhysicalDeviceFeatures2 m_featuresChain;
    std::unordered_map<VulkanDeviceFeatureType, VulkanDeviceFeature> m_queryResult;

    vk::PhysicalDeviceVulkan11Features m_features11;
    vk::PhysicalDeviceVulkan12Features m_features12;
    vk::PhysicalDeviceVulkan13Features m_features13;
    vk::PhysicalDeviceVulkan14Features m_features14;
};

class IVulkanDeviceFeaturesAssembler {
public:
    [[nodiscard]] virtual VulkanDeviceFeaturesAssembleData AssembleDeviceFeatures(const vk::raii::PhysicalDevice& physicalDevice,
        const std::vector<VulkanDeviceFeature>& requestedFeatures) = 0;
    virtual ~IVulkanDeviceFeaturesAssembler() = default;
};