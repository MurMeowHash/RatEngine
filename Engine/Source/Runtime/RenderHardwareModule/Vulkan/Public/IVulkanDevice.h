#pragma once

#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>
#include "Extensions/VulkanExtension.h"

class IVulkanDevice {
public:
    [[nodiscard]] virtual bool Initialize(const vk::raii::PhysicalDevice& physicalDevice, vk::QueueFlags requestedQueues,
                            const std::vector<VulkanExtension> &requestedExtensions) = 0;
    [[nodiscard]] virtual std::vector<const char*> GetRequiredOrSupportedExtensionNames() const = 0;
    [[nodiscard]] virtual bool IsExtensionSupported(const char* extensionName) const = 0;
    [[nodiscard]] virtual bool IsExtensionSupported(VulkanExtension::EncodingType extensionEncoding) const = 0;
    [[nodiscard]] virtual uint32_t GetApiVersion() const = 0;
    [[nodiscard]] virtual vk::PhysicalDeviceMemoryProperties GetDeviceMemoryProperties() const = 0;
    [[nodiscard]] virtual vk::raii::Device& GetInternalDevice() = 0;
    virtual ~IVulkanDevice() = default;
};