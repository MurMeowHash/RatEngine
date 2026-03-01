#pragma once

#include "IVulkanDevice.h"

class IVulkanDeviceFactory {
public:
    virtual IVulkanDevice* CreateVulkanDevice(const vk::raii::PhysicalDevice& physicalDevice, vk::QueueFlags requestedQueues,
                                              bool* initializationSucceeded) = 0;
    virtual ~IVulkanDeviceFactory() = default;
};