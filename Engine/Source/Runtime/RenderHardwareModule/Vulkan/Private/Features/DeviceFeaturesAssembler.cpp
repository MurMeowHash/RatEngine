#include "Features/DeviceFeaturesAssembler.h"

#define ADD_FEATURE(features, featuresInfo, assembleData, featureType, vulkanFeatureType, required) \
assembleData.m_queryResult.emplace(featureType, DeviceFeature(featureType, required));              \
assembleData.m_queryResult[featureType].MarkEnabled(featuresInfo.vulkanFeatureType);                \
if(required)                                                                                        \
    features.vulkanFeatureType = vk::True;                                                          \
else                                                                                                \
    features.vulkanFeatureType = featuresInfo.vulkanFeatureType;

DeviceFeaturesAssembleData DeviceFeaturesAssembler::AssembleDeviceFeatures(const vk::raii::PhysicalDevice &physicalDevice, uint32_t apiVersion) {
    auto deviceFeaturesInfo = physicalDevice.getFeatures2<vk::PhysicalDeviceFeatures2,
                                                                            vk::PhysicalDeviceVulkan11Features,
                                                                            vk::PhysicalDeviceVulkan12Features,
                                                                            vk::PhysicalDeviceVulkan13Features,
                                                                            vk::PhysicalDeviceVulkan14Features>();

    DeviceFeaturesAssembleData assembleData;
    void** featureChainEnd = &assembleData.m_featuresChain.pNext;

    if(apiVersion >= vk::ApiVersion11) {
        vk::PhysicalDeviceVulkan11Features features11Info = deviceFeaturesInfo.get<vk::PhysicalDeviceVulkan11Features>();

        ADD_FEATURE(assembleData.m_features11, features11Info, assembleData, DeviceFeatureType::ShaderDrawParameters, shaderDrawParameters, true)

        *featureChainEnd = &assembleData.m_features11;
        featureChainEnd = &assembleData.m_features11.pNext;
    }

    if(apiVersion >= vk::ApiVersion13) {
        vk::PhysicalDeviceVulkan13Features features13Info = deviceFeaturesInfo.get<vk::PhysicalDeviceVulkan13Features>();

        ADD_FEATURE(assembleData.m_features13, features13Info, assembleData, DeviceFeatureType::DynamicRendering, dynamicRendering, false)
        ADD_FEATURE(assembleData.m_features13, features13Info, assembleData, DeviceFeatureType::Synchronization2, synchronization2, false)

        *featureChainEnd = &assembleData.m_features13;
        featureChainEnd = &assembleData.m_features13.pNext;
    }

    return assembleData;
}
