#include "../../Public/Mapping/RatVulkanMapperInitializer.h"
#include "Mapping/ResourceMapping.h"
#include "LinearAllocator.h"

RatVulkanMapperInitializer::RatVulkanMapperInitializer(RatVulkanMapper *ratVulkanMapper)
: RatMapperInitializerBase(ratVulkanMapper, 1024) { }

void RatVulkanMapperInitializer::CreateMapping() {
    AddMapping<VulkanResourceTilingType, vk::ImageTiling, RatToVulkanImageTilingSubMapper>();
}