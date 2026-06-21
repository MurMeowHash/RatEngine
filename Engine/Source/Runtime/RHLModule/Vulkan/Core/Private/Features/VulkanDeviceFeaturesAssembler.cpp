#include "Features/VulkanDeviceFeaturesAssembler.h"
#include <stdexcept>
#include "CoreUtils.h"

#define QUERY_FEATURE_SUPPORT_SAFE(featureType, featureName, deviceFeatureInfo, deviceApiVersion, featuresApiVersion)   \
    deviceApiVersion < featuresApiVersion ? vk::False : deviceFeatureInfo.get<featureType>().featureName

#define ADD_FEATURE_TO_CHAIN_SAFE(featureChainEnd, features, deviceApiVersion, featuresApiVersion)                      \
    if(deviceApiVersion >= featuresApiVersion) {                                                                        \
        *featureChainEnd = &features;                                                                                   \
        featureChainEnd = &features.pNext;                                                                              \
    }

VulkanDeviceFeaturesAssembleData VulkanDeviceFeaturesAssembler::AssembleDeviceFeatures(const vk::raii::PhysicalDevice& physicalDevice,
        const std::vector<VulkanDeviceFeature>& requestedFeatures) {
    auto deviceFeaturesInfo = physicalDevice.getFeatures2<vk::PhysicalDeviceFeatures2,
                                                                            vk::PhysicalDeviceVulkan11Features,
                                                                            vk::PhysicalDeviceVulkan12Features,
                                                                            vk::PhysicalDeviceVulkan13Features,
                                                                            vk::PhysicalDeviceVulkan14Features>();

    uint32_t deviceApiVersion = physicalDevice.getProperties().apiVersion;
    VulkanDeviceFeaturesAssembleData featuresAssembleData;

    for (const VulkanDeviceFeature& feature : requestedFeatures) {
        VulkanFeatureNative vulkanFeature = ResolveFeature(feature.GetFeatureType(), deviceFeaturesInfo, deviceApiVersion, featuresAssembleData);
        vulkanFeature.m_featureEnabledRef = vulkanFeature.m_isSupported;
        auto featureIterator = featuresAssembleData.m_queryResult.emplace(feature.GetFeatureType(), feature);
        featureIterator.first->second.MarkEnabled(vulkanFeature.m_isSupported);
    }
    void** featureChainEnd = &featuresAssembleData.m_featuresChain.pNext;
    ADD_FEATURE_TO_CHAIN_SAFE(featureChainEnd, featuresAssembleData.m_features11, deviceApiVersion, vk::ApiVersion11)
    ADD_FEATURE_TO_CHAIN_SAFE(featureChainEnd, featuresAssembleData.m_features12, deviceApiVersion, vk::ApiVersion12)
    ADD_FEATURE_TO_CHAIN_SAFE(featureChainEnd, featuresAssembleData.m_features13, deviceApiVersion, vk::ApiVersion13)
    ADD_FEATURE_TO_CHAIN_SAFE(featureChainEnd, featuresAssembleData.m_features14, deviceApiVersion, vk::ApiVersion14)

    return featuresAssembleData;
}

VulkanFeatureNative VulkanDeviceFeaturesAssembler::ResolveFeature(VulkanDeviceFeatureType featureType,
    const vk::StructureChain<vk::PhysicalDeviceFeatures2, vk::PhysicalDeviceVulkan11Features,
                vk::PhysicalDeviceVulkan12Features, vk::PhysicalDeviceVulkan13Features,
                vk::PhysicalDeviceVulkan14Features>& deviceFeaturesInfo, uint32_t deviceApiVersion,
                VulkanDeviceFeaturesAssembleData& assembleData) {

    switch (featureType) {
        case VulkanDeviceFeatureType::ShaderDrawParameters:
            return VulkanFeatureNative(assembleData.m_features11.shaderDrawParameters,
                QUERY_FEATURE_SUPPORT_SAFE(vk::PhysicalDeviceVulkan11Features, shaderDrawParameters,
                    deviceFeaturesInfo, deviceApiVersion, vk::ApiVersion11));
        case VulkanDeviceFeatureType::DynamicRendering:
            return VulkanFeatureNative(assembleData.m_features13.dynamicRendering,
                QUERY_FEATURE_SUPPORT_SAFE(vk::PhysicalDeviceVulkan13Features, dynamicRendering,
                    deviceFeaturesInfo, deviceApiVersion, vk::ApiVersion13));
        case VulkanDeviceFeatureType::Synchronization2:
            return VulkanFeatureNative(assembleData.m_features13.synchronization2,
                QUERY_FEATURE_SUPPORT_SAFE(vk::PhysicalDeviceVulkan13Features, synchronization2,
                    deviceFeaturesInfo, deviceApiVersion, vk::ApiVersion13));
        default:
            throw std::invalid_argument(StringFormatter("Unable to resolve feature of type ", static_cast<uint32_t>(featureType)));
    }
}