#pragma once

#include "Configurations/Extensions/VulkanExtensionsConfiguration.h"

struct MockVulkanExtensionsConfiguration : public VulkanExtensionsConfiguration {
    explicit MockVulkanExtensionsConfiguration() : VulkanExtensionsConfiguration() { }
};