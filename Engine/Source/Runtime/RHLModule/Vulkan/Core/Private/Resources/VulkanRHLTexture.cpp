#include "../../Public/Resources/VulkanRHLTexture.h"
#include "Memory/VulkanMemoryCommon.h"

VulkanRHLTexture::VulkanRHLTexture(VulkanResourcesConfiguration *vulkanResourcesConfiguration, RatVulkanMapper* ratVulkanMapper)
: m_vulkanResourcesConfiguration(vulkanResourcesConfiguration), m_ratVulkanMapper(ratVulkanMapper) { }

bool VulkanRHLTexture::Initialize(const VulkanRHLTextureInitializationInfo &initializationInfo) {
    vk::ImageCreateInfo imageCreateInfo = AssembleImageCreateInfo(initializationInfo);
    vk::raii::Device& deviceHandle = initializationInfo.m_vulkanDevice->GetHandle();
    vk::ResultValue<vk::raii::Image> imageResult = deviceHandle.createImage(imageCreateInfo);
    if (imageResult.result != vk::Result::eSuccess)
        return false;

    m_imageHandle = std::move(imageResult.value);
    vk::Result memoryInitResult = InitializeImageMemory(initializationInfo);
    if (memoryInitResult != vk::Result::eSuccess)
        return false;


}

vk::ImageCreateInfo VulkanRHLTexture::AssembleImageCreateInfo(const VulkanRHLTextureInitializationInfo &initializationInfo) const {
    vk::ImageCreateInfo imageCreateInfo;
    imageCreateInfo.flags = initializationInfo.m_imageCreateFlags;
    imageCreateInfo.imageType = initializationInfo.m_imageType;
    imageCreateInfo.format = initializationInfo.m_imageFormat;
    imageCreateInfo.extent = initializationInfo.m_imageExtent;
    imageCreateInfo.mipLevels = initializationInfo.m_mipLevels;
    imageCreateInfo.arrayLayers = initializationInfo.m_arrayLayers;
    imageCreateInfo.samples = initializationInfo.m_sampleCount;
    imageCreateInfo.tiling = m_ratVulkanMapper->ResolveMapping<VulkanResourceTilingType, vk::ImageTiling>(initializationInfo.m_tilingType);
    imageCreateInfo.usage = initializationInfo.m_usage;

    bool allowImageConcurrentAccess;
    if (!m_vulkanResourcesConfiguration->TryGetAllowConcurrentAccess(VulkanResourceType::Image, allowImageConcurrentAccess))
        allowImageConcurrentAccess = false;

    std::vector<VulkanQueueData> deviceQueues = initializationInfo.m_vulkanDevice->GetOperatingQueues();
    bool useConcurrentAccess = allowImageConcurrentAccess && deviceQueues.size() > 1;

    if (useConcurrentAccess) {
        imageCreateInfo.sharingMode = vk::SharingMode::eConcurrent;
        std::vector<uint32_t> operatingQueueIndices ; RetrieveIndicesFromQueues(deviceQueues);
        imageCreateInfo.queueFamilyIndexCount = operatingQueueIndices.size();
        imageCreateInfo.pQueueFamilyIndices = operatingQueueIndices.data();
    } else {
        imageCreateInfo.sharingMode = vk::SharingMode::eExclusive;
    }

    imageCreateInfo.initialLayout = vk::ImageLayout::eUndefined;
    return imageCreateInfo;
}

std::vector<uint32_t> VulkanRHLTexture::RetrieveIndicesFromQueues(const std::vector<VulkanQueueData> &deviceQueues) {
    std::vector<uint32_t> queueIndices;
    queueIndices.reserve(deviceQueues.size());

    for (const VulkanQueueData& queue : deviceQueues) {
        queueIndices.emplace_back(queue.m_queueIndex);
    }

    return queueIndices;
}

vk::Result VulkanRHLTexture::InitializeImageMemory(const VulkanRHLTextureInitializationInfo& initializationInfo) const {
    IVulkanDevice* vulkanDevice = initializationInfo.m_vulkanDevice;
    VulkanDeviceMemory imageMemory = vulkanDevice->GetMemoryProvider()->AllocateImageMemory(m_imageHandle,
        initializationInfo.m_memoryPropertyFlags, initializationInfo.m_dedicatedMemoryRequirementsFlags, initializationInfo.m_tilingType);

    return Rat::VulkanMemoryCommon::BindImageMemory(vulkanDevice->GetHandle(), imageMemory, m_imageHandle);
}