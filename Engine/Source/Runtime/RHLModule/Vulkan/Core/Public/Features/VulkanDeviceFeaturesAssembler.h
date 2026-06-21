#pragma once

#include "IVulkanDeviceFeaturesAssembler.h"
#include <cstdint>

struct VulkanFeatureNative {
    vk::Bool32& m_featureEnabledRef;
    vk::Bool32 m_isSupported;
};

class VulkanDeviceFeaturesAssembler : public IVulkanDeviceFeaturesAssembler {
public:
    VulkanDeviceFeaturesAssembleData AssembleDeviceFeatures(const vk::raii::PhysicalDevice& physicalDevice,
        const std::vector<VulkanDeviceFeature>& requestedFeatures) override;

private:
    VulkanFeatureNative ResolveFeature(VulkanDeviceFeatureType featureType,
        const vk::StructureChain<vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan11Features,
                vk::PhysicalDeviceVulkan12Features, vk::PhysicalDeviceVulkan13Features,
                vk::PhysicalDeviceVulkan14Features>& deviceFeaturesInfo, uint32_t deviceApiVersion,
                VulkanDeviceFeaturesAssembleData& assembleData);
};