#pragma once

#define VULKAN_HPP_NO_EXCEPTIONS
#include <vulkan/vulkan_raii.hpp>
#include "Extensions/VulkanExtension.h"
#include "VulkanGlobals.h"

using Rat::RenderHardwareProviderModule::Vulkan::VulkanApiVersion;

enum class InstanceCreationFlags : uint32_t {
    None = 0,
    AllowDropLayers = 1,
    UseDebug = 2,
    AllowDropDebug = 3,
};

struct VulkanInstanceInitializationInfo {
    std::vector<VulkanExtension> m_requestedExtensions;
    std::vector<const char*> m_requestedLayers;
    VulkanApiVersion m_minVulkanVersion;
    InstanceCreationFlags m_creationFlags = InstanceCreationFlags::None;
};

class IVulkanInstance {
public:
    [[nodiscard]] virtual bool Initialize(const VulkanInstanceInitializationInfo& initializationInfo) = 0;
    [[nodiscard]] virtual vk::raii::Instance& GetHandle() = 0;
    virtual ~IVulkanInstance() = default;
};