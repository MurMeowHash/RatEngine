#pragma once

#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>
#include "Extensions/VulkanExtension.h"
#include "Features/IVulkanDeviceFeaturesAssembler.h"
#include "Memory/IVulkanDeviceMemoryProvider.h"
#include "Configurations/Device/VulkanAllocationPreset.h"
#include "Memory/VulkanMemoryProviderType.h"

struct VulkanQueueData {
    uint32_t m_queueIndex;
    vk::raii::Queue m_queue = nullptr;
};

struct VulkanDeviceInitializationInfo {
    vk::raii::PhysicalDevice& m_physicalDevice;
    vk::QueueFlags m_requestedQueues;
    std::vector<VulkanExtension> m_requestedExtensions;
    std::vector<VulkanDeviceFeature> m_requestedFeatures;
    VulkanMemoryProviderType m_memoryProviderType = VulkanMemoryProviderType::Default;
};

class IVulkanDevice {
public:
    [[nodiscard]] virtual bool Initialize(const VulkanDeviceInitializationInfo& initializationInfo) = 0;
    [[nodiscard]] virtual vk::raii::Device& GetHandle() = 0;
    [[nodiscard]] virtual IVulkanDeviceMemoryProvider* GetMemoryProvider() = 0;
    [[nodiscard]] virtual std::vector<VulkanQueueData> GetOperatingQueues() const = 0;
    [[nodiscard]] virtual bool TryGetQueue(vk::QueueFlagBits queueFlagBits, VulkanQueueData& outQueueData) const = 0;
    virtual ~IVulkanDevice() = default;
};
