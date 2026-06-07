#pragma once

#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>
#include "VulkanDeviceMemory.h"

class IVulkanDedicatedDeviceAllocator {
public:
    virtual VulkanDeviceMemory AllocateImageMemory(const vk::raii::Image& image) = 0;
    virtual VulkanDeviceMemory AllocateBufferMemory(const vk::raii::Buffer& buffer) = 0;
    virtual void FreeMemory(VulkanDeviceMemory& memory);
    virtual void FreeAllMemory();
    virtual ~IVulkanDedicatedDeviceAllocator() = default;
};
