#pragma once

#include "IVulkanDevice.h"
#include <unordered_map>
#include <string_view>
#include "Entity/VulkanEntity.h"
#include "Memory/IVulkanDeviceMemoryProvider.h"
#include "Memory/IVulkanDeviceMemoryProviderFactory.h"

struct QueueFlagBitsHash {
    std::size_t operator()(vk::QueueFlagBits bit) const noexcept {
        using Underlying = std::underlying_type_t<vk::QueueFlagBits>;
        return std::hash<Underlying>{}(static_cast<Underlying>(bit));
    }
};

class VulkanDevice : public VulkanEntity, public IVulkanDevice {
public:
    [[nodiscard]] bool TryGetAvailableExtensions(std::vector<vk::ExtensionProperties> &availableExtensions) const override;
public:
    VulkanDevice(IVulkanExtensionsValidator* vulkanExtensionsValidator, IVulkanDeviceFeaturesAssembler* vulkanDeviceFeaturesAssembler,
        IVulkanDeviceMemoryProviderFactory* vulkanDeviceMemoryProviderFactory);
    ~VulkanDevice() override;
    [[nodiscard]] bool Initialize(const VulkanDeviceInitializationInfo& initializationInfo) override;

    [[nodiscard]] vk::raii::Device& GetHandle() override;
    [[nodiscard]] IVulkanDeviceMemoryProvider* GetMemoryProvider() override;
    [[nodiscard]] std::vector<VulkanQueueData> GetOperatingQueues() const override;
    [[nodiscard]] bool TryGetQueue(vk::QueueFlagBits queueFlagBits, VulkanQueueData& outQueueData) const override;

private:
    IVulkanDeviceFeaturesAssembler* m_vulkanDeviceFeaturesAssembler;
    IVulkanDeviceMemoryProviderFactory* m_vulkanDeviceMemoryProviderFactory;

    vk::raii::PhysicalDevice m_physicalDevice = nullptr;
    vk::raii::Device m_device = nullptr;

    std::unordered_map<vk::QueueFlagBits, VulkanQueueData, QueueFlagBitsHash> m_deviceQueues;
    std::unordered_map<VulkanDeviceFeatureType, VulkanDeviceFeature> m_features;

    IVulkanDeviceMemoryProvider* m_memoryProvider = nullptr;

    std::vector<vk::DeviceQueueCreateInfo> InitializeDeviceQueues(vk::QueueFlags requestedQueues);
    void ObtainQueues();
    void InitializeMemoryProvider(VulkanMemoryProviderType memoryProviderType);
};