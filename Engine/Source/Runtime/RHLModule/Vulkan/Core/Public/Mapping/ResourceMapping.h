#pragma once

#include "Mapping/RatSubMapper.h"
#include "../Memory/VulkanResourceTilingType.h"
#include <vulkan/vulkan.hpp>
#include <CoreUtils.h>
#include <stdexcept>
#include <cstdint>

struct RatToVulkanImageTilingSubMapper : public IRatSubMapper<VulkanResourceTilingType, vk::ImageTiling> {
    vk::ImageTiling Resolve(VulkanResourceTilingType value) override {
        switch (value) {
            case VulkanResourceTilingType::Linear:
                return vk::ImageTiling::eLinear;
            case VulkanResourceTilingType::NonLinear:
                return vk::ImageTiling::eOptimal;
            default:
                throw std::invalid_argument(StringFormatter("Unable to resolve rat to image tiling vulkan for value ", static_cast<uint32_t>(value)));
        }
    }
};
