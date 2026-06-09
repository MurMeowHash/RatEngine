#pragma once
#include "VulkanInstance.h"

class IVulkanInstanceFactory {
public:
    virtual VulkanInstance* CreateVulkanInstance(const VulkanInstanceInitializationInfo& initializationInfo,
        bool* initializationSucceeded) = 0;
    virtual VulkanInstance* CreateVulkanInstance(InstanceCreationFlags creationFlags, bool* initializationSucceeded) = 0;
    virtual ~IVulkanInstanceFactory() = default;
};
