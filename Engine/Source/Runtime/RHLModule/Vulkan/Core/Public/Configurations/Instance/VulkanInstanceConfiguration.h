#pragma once

#include <vector>
#include "VulkanGlobals.h"

using Rat::RHLProviderModule::Vulkan::VulkanApiVersion;

struct VulkanInstanceConfiguration {
    explicit VulkanInstanceConfiguration() {
        m_minVulkanVersion = VulkanApiVersion(0, 1, 2, 0);
        m_validationLayersNames = {"VK_LAYER_KHRONOS_validation"};
    }

    VulkanApiVersion m_minVulkanVersion;
    std::vector<const char*> m_validationLayersNames;
};
