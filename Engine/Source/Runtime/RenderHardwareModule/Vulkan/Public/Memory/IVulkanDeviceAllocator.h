#pragma once

#include "VulkanDeviceMemory.h"

class IVulkanDeviceAllocator {
public:
    [[nodiscard]] virtual VulkanDeviceMemory AllocateMemory(vk::DeviceSize memorySize, vk::DeviceSize alignment) = 0;
    virtual void FreeMemory(const VulkanDeviceMemory& memory) = 0;
    virtual void InvalidateAllMemory() = 0;
    virtual void FreeAllMemory() = 0;
    virtual ~IVulkanDeviceAllocator() = default;
};
