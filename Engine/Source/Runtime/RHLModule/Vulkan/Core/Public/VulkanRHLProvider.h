#pragma once

#include "IRHLProvider.h"
#include "IVulkanDeviceProvider.h"
#include "IVulkanDeviceFactory.h"
#include "Instance/IVulkanInstanceFactory.h"
#include "Instance/VulkanInstance.h"

class BuildSettings;

class VulkanRHLProvider : public IRHLProvider {
public:
    VulkanRHLProvider(IVulkanInstanceFactory* vulkanInstanceFactory, IVulkanDeviceFactory* vulkanDeviceFactory,
        IVulkanDeviceProvider* vulkanDeviceProvider, BuildSettings* buildSettings);
    [[nodiscard]] bool Initialize() override;
    void Shutdown() override;
private:
    IVulkanInstanceFactory* m_vulkanInstanceFactory;
    IVulkanDeviceFactory* m_vulkanDeviceFactory;
    IVulkanDeviceProvider* m_vulkanDeviceProvider;
    BuildSettings* m_buildSettings;

    VulkanInstance* m_vulkanInstance = nullptr;
    VulkanDevice* m_vulkanDevice = nullptr;

    [[nodiscard]] bool CreateVulkanInstance();
    [[nodiscard]] bool CreateVulkanDevice();
};