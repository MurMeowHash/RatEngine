#pragma once

#include "Resources/IRHLTexture.h"
#include "IVulkanDevice.h"

struct VulkanRHLTextureInitializationInfo {
    IVulkanDevice *m_vulkanDevice;
    vk::ImageCreateFlags m_imageCreateFlags;
    vk::ImageType m_imageType;
    vk::Format m_imageFormat;
    vk::Extent3D m_imageExtent;
    uint32_t m_mipLevels;
    uint32_t m_arrayLayers;
    vk::SampleCountFlagBits m_sampleCount;
    VulkanResourceTilingType m_tilingType;
    vk::ImageUsageFlags m_usage;
    vk::MemoryPropertyFlags m_memoryPropertyFlags;
    DedicatedMemoryRequirementsFlags m_dedicatedMemoryRequirementsFlags;
};

class IVulkanRHLTexture : public IRHLTexture {
public:
    [[nodiscard]] virtual bool Initialize(const VulkanRHLTextureInitializationInfo& initializationInfo) = 0;
};