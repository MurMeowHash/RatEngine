#pragma once

#include "IVulkanRHLTexture.h"
#include "Configurations/Resources/VulkanResourcesConfiguration.h"
#include "Mapping/RatVulkanMapper.h"

class VulkanRHLTexture : public IVulkanRHLTexture {
public:
    VulkanRHLTexture(VulkanResourcesConfiguration* vulkanResourcesConfiguration, RatVulkanMapper* ratVulkanMapper);

    [[nodiscard]] bool Initialize(const VulkanRHLTextureInitializationInfo& initializationInfo) override;
private:
    VulkanResourcesConfiguration* m_vulkanResourcesConfiguration;
    RatVulkanMapper* m_ratVulkanMapper;

    vk::raii::Image m_imageHandle = nullptr;

    [[nodiscard]] vk::ImageCreateInfo AssembleImageCreateInfo(const VulkanRHLTextureInitializationInfo& initializationInfo) const;
    static std::vector<uint32_t> RetrieveIndicesFromQueues(const std::vector<VulkanQueueData>& deviceQueues);
    [[nodiscard]] vk::Result InitializeImageMemory(const VulkanRHLTextureInitializationInfo& initializationInfo) const;
};
