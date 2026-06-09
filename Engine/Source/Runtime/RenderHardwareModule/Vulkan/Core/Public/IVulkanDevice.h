#pragma once

#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>
#include "Extensions/VulkanExtension.h"
#include "Features/IVulkanDeviceFeaturesAssembler.h"
#include "Memory/IVulkanDeviceMemoryProvider.h"
#include "Configurations/Device/VulkanAllocationPreset.h"
#include "Memory/VulkanMemoryProviderType.h"

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
    [[nodiscard]] virtual vk::raii::Device& GetInternalDevice() = 0;
    [[nodiscard]] virtual IVulkanDeviceMemoryProvider* GetMemoryProvider() = 0;
    virtual ~IVulkanDevice() = default;
};
