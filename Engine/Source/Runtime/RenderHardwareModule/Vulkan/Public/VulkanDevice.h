#pragma once

#include "IVulkanDevice.h"
#include <unordered_map>
#include <string_view>
#include "Features/IDeviceFeaturesAssembler.h"
#include "Memory/IVulkanDeviceMemoryProvider.h"
#include "Memory/IVulkanDeviceMemoryProviderFactory.h"

struct VulkanQueueData {
    uint32_t m_queueIndex;
    vk::raii::Queue m_queue = nullptr;
};

struct QueueFlagBitsHash {
    std::size_t operator()(vk::QueueFlagBits bit) const noexcept {
        using Underlying = std::underlying_type_t<vk::QueueFlagBits>;
        return std::hash<Underlying>{}(static_cast<Underlying>(bit));
    }
};

class VulkanDevice : public IVulkanDevice {
public:
    VulkanDevice(IDeviceFeaturesAssembler* deviceFeaturesAssembler, IVulkanDeviceMemoryProviderFactory* vulkanDeviceMemoryProviderFactory);
    bool Initialize(const vk::raii::PhysicalDevice& physicalDevice, vk::QueueFlags requestedQueues,
        const std::vector<VulkanExtension> &requestedExtensions, const VulkanAllocationConfiguration& memoryAllocationConfiguration) override;

    std::vector<const char *> GetRequiredOrSupportedExtensionNames() const override;
    bool IsExtensionSupported(const char *extensionName) const override;
    bool IsExtensionSupported(VulkanExtension::EncodingType extensionEncoding) const override;
    uint32_t GetApiVersion() const override;
    [[nodiscard]] vk::raii::Device& GetInternalDevice() override;

private:
    IDeviceFeaturesAssembler* m_deviceFeaturesAssembler = nullptr;
    IVulkanDeviceMemoryProviderFactory* m_vulkanDeviceMemoryProviderFactory = nullptr;

    vk::raii::PhysicalDevice m_physicalDevice = nullptr;
    vk::raii::Device m_device = nullptr;

    std::unordered_map<vk::QueueFlagBits, VulkanQueueData, QueueFlagBitsHash> m_deviceQueues;
    std::unordered_map<VulkanExtension::EncodingType, VulkanExtension> m_extensions;
    std::unordered_map<DeviceFeatureType, DeviceFeature> m_features;

    IVulkanDeviceMemoryProvider* m_memoryProvider = nullptr;

    uint32_t m_apiVersion = 0;

    std::vector<vk::DeviceQueueCreateInfo> InitializeDeviceQueues(vk::QueueFlags requestedQueues);
    void FilterExtensions(const std::vector<VulkanExtension> &requestedExtensions);
    DeviceFeaturesAssembleData InitializeDeviceFeatures();
    void ObtainQueues();
    void InitializeMemoryProvider(const VulkanAllocationConfiguration& memoryAllocationConfiguration);
};