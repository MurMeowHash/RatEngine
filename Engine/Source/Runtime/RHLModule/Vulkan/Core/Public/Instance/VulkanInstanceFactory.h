#pragma once

#include "IVulkanInstanceFactory.h"
#include "Configurations/Extensions/VulkanExtensionsConfiguration.h"
#include "Configurations/Instance/VulkanInstanceConfiguration.h"

class DiContainer;

class VulkanInstanceFactory : public IVulkanInstanceFactory {
public:
    VulkanInstanceFactory(DiContainer* diContainer, VulkanInstanceConfiguration* vulkanInstanceConfiguration,
        VulkanExtensionsConfiguration* vulkanExtensionsConfiguration);
    VulkanInstance* CreateVulkanInstance(const VulkanInstanceInitializationInfo &initializationInfo,
        bool* initializationSucceeded) override;
    VulkanInstance* CreateVulkanInstance(InstanceCreationFlags creationFlags, bool* initializationSucceeded) override;
private:
    DiContainer* m_diContainer;
    VulkanInstanceConfiguration* m_vulkanInstanceConfiguration;
    VulkanExtensionsConfiguration* m_vulkanExtensionsConfiguration;
};
