#pragma once

#include "RatVulkanMapper.h"
#include "Mapping/RatMapperInitializerBase.h"

class RatVulkanMapperInitializer : public RatMapperInitializerBase {
public:
    explicit RatVulkanMapperInitializer(RatVulkanMapper* ratVulkanMapper);
    void CreateMapping() override;
};
