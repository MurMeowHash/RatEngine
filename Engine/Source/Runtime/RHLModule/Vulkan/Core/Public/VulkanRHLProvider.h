#pragma once

#include "IRHLProvider.h"
#include "IVulkanDeviceProvider.h"
#include "IVulkanDeviceFactory.h"
#include "Instance/IVulkanInstanceFactory.h"
#include "Instance/VulkanInstance.h"
#include "Mapping/RatVulkanMapperInitializer.h"
#include "Resources/IVulkanRHLTexture.h"

class BuildSettings;

class VulkanRHLProvider : public IRHLProvider {
public:
    VulkanRHLProvider(IVulkanInstanceFactory* vulkanInstanceFactory, IVulkanDeviceFactory* vulkanDeviceFactory,
                      IVulkanDeviceProvider* vulkanDeviceProvider, BuildSettings* buildSettings,
                      RatVulkanMapperInitializer* ratVulkanMapperInitializer);
    [[nodiscard]] bool Initialize() override;
    void Shutdown() override;
    IRHLTexture* CreateTexture(const RHLTextureCreateInfo &createInfo) override;
private:
    IVulkanInstanceFactory* m_vulkanInstanceFactory;
    IVulkanDeviceFactory* m_vulkanDeviceFactory;
    IVulkanDeviceProvider* m_vulkanDeviceProvider;
    BuildSettings* m_buildSettings;
    RatVulkanMapperInitializer* m_ratVulkanMapperInitializer;

    VulkanInstance* m_vulkanInstance = nullptr;
    VulkanDevice* m_vulkanDevice = nullptr;

    [[nodiscard]] bool CreateVulkanInstance();
    [[nodiscard]] bool CreateVulkanDevice();
};